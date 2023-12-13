#!/usr/bin/python

import yaml
import argparse
import os
import re
from jinja2 import Environment, FileSystemLoader
from host_py_rm_studio_internal import RM_Factory

TEMPLATE_PATH = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'templates')

MACROS = {'SET': {'Action': 'OR'},
          'CLEAR': {'Action': 'AND', 'isNotArg': True},
          'REGALL': {'Action': 'SKIPCOND_REGALL'},
          'REGANY': {'Action': 'SKIPCOND_REGANY'},
          'REGNEGALL': {'Action': 'SKIPCOND_REGNEGALL'},
          'REGNEGANY': {'Action': 'SKIPCOND_REGNEGANY'},
          'SIGALL': {'Action': 'SKIPCOND_SIGALL'},
          'SIGANY': {'Action': 'SKIPCOND_SIGANY'},
          'SIGNEGALL': {'Action': 'SKIPCOND_SIGNEGALL'},
          'SIGNEGANY': {'Action': 'SKIPCOND_SIGNEGANY'},
          'MACRO_WRITE': {'Action': 'WRITE', 'arg': [{'RAC_SCRATCH0': 0xABADCAFE}]}  # example of macro
          }

# Depending on the action, the synthax can change. For example, a simple WRITE can be seen as writing that <value> to
# <destination>, where <value> can be a register, mask, shift, etc. or an integer.
# But for 'MOV' action, it is moving a <value at a given address> to a <destination>.
ACTION_USING_REG_ADDR = [
    'MOVBLOCK', 'MOV', 'SAVE_AND_RESTORE'
]


class Action(object):
    def __init__(self, actionName, arg, baseAddrConfig, contWrPos, isNotArg=False):
        """
        :opCode: The action ID
        :data: A dictionary containing the offset and the value to write for each baseAddrId.
            The dict should be defined as:
                data = {baseAddrId: {offset: value, offset1: value, etc.}}
            offset: Register address LSB depending on CNTWRPOS in sequence YAML file.
            value: The argument unchanged (str or integer depending on the input)
        :inst: A dictionary containing the instruction and the list of continuous <data>
            The dict should be defined as:
                dict = {instruction: [self.data]}
        """
        self.name = actionName
        self.baseAddrConfig = baseAddrConfig['BaseAddr']
        self.basePos = baseAddrConfig['BasePos']
        self.contWrPos = contWrPos
        # isContWrReserved indicates whether an opcode uses LENGTH field as an indicator for a special action
        # that is not compliant with continuous writes (such as DELAY, SKIPCOND, etc.)
        self._opCode, self.isContWrReserved = self.getOpCode()
        self.data = {}
        self.inst = {}
        self.isNotArg = isNotArg
        self.isSimpleArg = False
        self.encodeAction(arg)

    def getOpCode(self):
        WRITE = 0
        AND = 1 << 28
        XOR = 2 << 28
        OR = 3 << 28
        DELAY = 4 << 28
        DELAYABS = (4 << 28) | (1 << self.contWrPos)
        MOV = 5 << 28
        MOVNOINC = 6 << 28
        WAITFORREG_ALL = 7 << 28
        WAITFORREG_ANY = (7 << 28) | (1 << self.contWrPos)
        WAITFORREG_NEGALL = (7 << 28) | (2 << self.contWrPos)
        WAITFORREG_NEGANY = (7 << 28) | (3 << self.contWrPos)
        WAITFORSIG_ALL = 8 << 28
        WAITFORSIG_ANY = (8 << 28) | (1 << self.contWrPos)
        WAITFORSIG_NEGALL = (8 << 28) | (2 << self.contWrPos)
        WAITFORSIG_NEGANY = (8 << 28) | (3 << self.contWrPos)
        WRITENOINC = 9 << 28
        JUMP = 10 << 28
        JUMPABS = (10 << 28) | (1 << self.contWrPos)
        SETTRIG = 11 << 28
        SETTRIG_SET = (11 << 28) | (1 << self.contWrPos)
        SETTRIG_CLR = (11 << 28) | (2 << self.contWrPos)
        SETTRIG_TOG = (11 << 28) | (3 << self.contWrPos)
        MOVBLOCK = (12 << 28)
        SKIPCOND_REGALL = 13 << 28
        SKIPCOND_REGANY = (13 << 28) | (1 << self.contWrPos)
        SKIPCOND_REGNEGALL = (13 << 28) | (2 << self.contWrPos)
        SKIPCOND_REGNEGANY = (13 << 28) | (3 << self.contWrPos)
        SKIPCOND_SIGALL = (13 << 28) | (4 << self.contWrPos)
        SKIPCOND_SIGANY = (13 << 28) | (5 << self.contWrPos)
        SKIPCOND_SIGNEGALL = (13 << 28) | (6 << self.contWrPos)
        SKIPCOND_SIGNEGANY = (13 << 28) | (7 << self.contWrPos)
        NOP = 15 << 28
        ENDSEQ = 0xFFFFFFFF

        # Actions that do use continuous write field for such purpose and not as an action indicator (like difference
        # between DELAY and DELAYABS).
        actionContWrFree = ['WRITE', 'AND', 'XOR', 'OR', 'MOV', 'MOVNOINC', 'WRITENOINC', 'MOVBLOCK']

        isContWrReserved = True if self.name not in actionContWrFree else False
        return eval(self.name), isContWrReserved

    @staticmethod
    def parser(register):
        regInfo = re.split("[(_ )]+", register)
        regInfo = list(filter(lambda x: (x != '' and x != ' '), regInfo))  # remove empty str ''
        #      block,      reg
        return regInfo[0], regInfo[1]

    def computeVal(self):
        """
        Used internally for Design team since they don't have mask and shift values.
        """
        for baseAddr, dictData in self.data.items():
            for offset, value in dictData.items():
                valueToCompute = value
                if type(value) is dict:
                    valueToCompute = value['VALUE']

                if type(valueToCompute) is str and self.name != 'JUMP':
                    computeRegAddr = False
                    if self.name in ACTION_USING_REG_ADDR:
                        computeRegAddr = True

                    compute = 0
                    maskList = list(filter(None, re.split("[|]+", valueToCompute)))

                    for element in maskList:
                        if '<<' in element:
                            block, reg = self.parser(re.split("<<", element)[-1])
                        else:
                            block, reg = self.parser(element)
                        mask = list(filter(None, re.split("[(_ )]+", element)))

                        if computeRegAddr is False:
                            regIndex = mask.index(reg)
                            try:
                                field = mask[regIndex + 1] if mask[regIndex + 1] != 'MASK' else ''
                            except IndexError:
                                # No field is used here, only block_reg
                                field = ''

                            if 'SHIFT' in mask:
                                valToShift = int(mask[mask.index('<<') - 1].replace('U', ''))
                                bitOffset = eval('rm.' + block + '.' + reg + '.' + field + '.bitOffset')
                                bitMask = eval('rm.' + block + '.' + reg + '.' + field + '.mask')
                                compute |= (valToShift << bitOffset) & bitMask
                            elif field == '':
                                compute |= eval('rm.' + block + '.' + reg + '.resetMask')
                            else:
                                compute |= eval('rm.' + block + '.' + reg + '.' + field + '.mask')
                        else:
                            compute |= eval('rm.' + block + '.' + reg + '.address')

                    # Replace value in data
                    self.data[baseAddr][offset] = compute

    def getLength(self):
        """ Return the number of words contained in the action """
        length = 0
        for inst, val in self.inst.items():
            # When there is no argument, val is None: remove those since they're not printed
            filteredVal = list(filter(lambda x: x[1] is not None, val))
            length += 1 + len(filteredVal)
        return length

    def reverseMask(self):
        for baseAddrId, value in self.data.items():
            for offset in value:
                if type(value[offset]) is dict:
                    valueToConvert = value[offset]['VALUE']
                else:
                    valueToConvert = value[offset]

                if type(valueToConvert) is str:
                    valueToConvert = '~(' + valueToConvert + ')'
                else:
                    valueToConvert = (~valueToConvert) & 0xFFFFFFFF

                if type(value[offset]) is dict:
                    value[offset]['VALUE'] = valueToConvert
                else:
                    value[offset] = valueToConvert

    @staticmethod
    def findRegAddress(block_register):
        regInfo = re.split("[(_ )]+", block_register)
        regInfo = list(filter(lambda x: (x != '' and x != ' '), regInfo))  # remove empty str ''

        try:
            address = eval('rm.' + regInfo[0] + '.' + regInfo[1] + '.address')
        except IndexError:
            raise Exception("Failed to parse register. Double check syntax: (-> is forbidden, use _ instead) "
                            "ex: RAC_IF rather than RAC->IF")

        if 'SET' in regInfo:
            offset = 'setOffset'
        elif 'CLR' in regInfo:
            offset = 'clrOffset'
        elif 'TGL' in regInfo:
            offset = 'tglOffset'
        else:
            offset = None

        if offset is not None:
            address += eval('rm.' + regInfo[0] + '.' + regInfo[1] + '.' + offset)

        return address

    def findRegBase(self, address):
        minDelta = 0xFFFFFFFF
        minBaseAddr = 0
        for baseAddr in self.baseAddrConfig.keys():
            delta = address - baseAddr
            if 0 <= delta < minDelta:
                minDelta = delta
                minBaseAddr = baseAddr
        return minBaseAddr, self.baseAddrConfig[minBaseAddr]

    def store(self, baseAddrId, offset, value):
        if type(value) is list:
            for i, el in enumerate(value):
                self.data.setdefault(baseAddrId, {})[offset + i * 4] = el
        else:
            if offset in self.data.setdefault(baseAddrId, {}):
                if type(self.data[baseAddrId][offset]) is dict:
                    regValue = self.data[baseAddrId][offset]['VALUE']
                else:
                    regValue = self.data[baseAddrId][offset]

                if type(value) is dict:
                    value = value['VALUE']

                if type(value) is str:
                    regValue += ' | ' + value
                else:
                    regValue |= value

                # store result
                if type(self.data[baseAddrId][offset]) is dict:
                    self.data[baseAddrId][offset]['VALUE'] = regValue
                else:
                    self.data[baseAddrId][offset] = regValue
            else:
                self.data[baseAddrId][offset] = value

    def encodeAction(self, arg):
        """
        For every action, get the register base address and offset and store it into data.
        Values defined at same offset are ORed
        """
        if type(arg) is list:
            for regInstr in arg:
                if type(regInstr) is dict:
                    for block_register, val in regInstr.items():
                        # Get the destination address: it can either be a register or a direct address
                        if type(block_register) is str:
                            # Parse the register
                            address = self.findRegAddress(block_register)
                        else:
                            address = block_register  # It is already an address

                        # Extract the closest base address from register address and the index
                        regBase, regBaseId = self.findRegBase(address)
                        regOffset = address - regBase

                        # Check offset width
                        if regOffset > (2 ** self.contWrPos) - 1:
                            raise Exception(
                                "Offset 0x{0:08X} doesn't fit with CNTWRPOS setting. You must either increase"
                                " it or add a base address in seqacc_regbases.yml".format(regOffset))

                        self.store(regBaseId, regOffset, val)
                else:
                    # Arg is a simple list
                    for i, val in enumerate(arg):
                        self.data.setdefault(0, {})[i*4] = val
        else:
            # Actions having no or one argument that is not a dict end here
            self.isSimpleArg = True  # Mostly used for correct printing
            self.data.setdefault(0xFFFFFFFF, {})[0] = arg

        if args.internal:
            self.computeVal()
        if self.isNotArg is True:
            self.reverseMask()

        self._encode()

    def _encode(self):
        """
         Fill inst list that is used for printing actions with encoded instructions and values.
         Manages the continuous write operation.
         First sort registers in data by offset, then parse these offsets and verify if they are continuous.
         If not, break the data list into continuous sublists.
        """

        # First, sort instructions by registers offsets
        self.data = dict(sorted(self.data.items()))
        for baseAddrId in self.data.keys():
            self.data[baseAddrId] = dict(sorted(self.data[baseAddrId].items()))
            # Convert dict to list for simplicity in next step
            self.data[baseAddrId] = list(self.data[baseAddrId].items())

        # Then check if addresses are continuous
        maxContinuousWr = 2**(self.basePos - self.contWrPos) - 1
        for baseAddrId, value in self.data.items():
            prevOffset = 0xFFFFFFFF
            continuousIndex = 0
            for i, element in enumerate(value):
                offsetContinuous = value[continuousIndex][0]
                # Break the chain of action into subchains if either address are not continuous
                # or the limit of continuous writes has been reached
                if ((element[0] - prevOffset) > 4 and prevOffset != 0xFFFFFFFF) or (i - continuousIndex) == maxContinuousWr:
                    instruction = self._opCode | (baseAddrId << self.basePos) | ((i - continuousIndex) << self.contWrPos) \
                                  | offsetContinuous
                    self.inst[instruction] = [el for el in value[continuousIndex:i]]
                    continuousIndex = i
                prevOffset = element[0]

            if self.isContWrReserved is False:
                try:
                    length = value[0][1]['LENGTH']
                except:
                    length = len(value) - continuousIndex

                continuousWrField = length
                offset = value[continuousIndex][0]
            else:
                baseAddrId = 0 if baseAddrId == 0xFFFFFFFF else baseAddrId
                continuousWrField = 0
                offset = prevOffset

            # Store last element
            instruction = self._opCode | (baseAddrId << self.basePos) | (continuousWrField << self.contWrPos) | offset
            self.inst[instruction] = [el for el in value[continuousIndex:]]


class Sequence(object):
    def __init__(self, seqName, seqData):
        global rm
        self.name = seqName
        self.data = seqData
        #print(seqName)
        #print(seqData)
        #print("regBaseYml: {}".format(regBaseYml))
        #print(self.data['BaseAddrCfg'])
        #print(self.getConfig(regBaseYml, args.part, self.data['BaseAddrCfg'], 'BasePos'))
        self.basePos = (self.getConfig(regBaseYml, args.part, self.data['BaseAddrCfg'], 'BasePos') & 0x1F)
        self.baseAddrConfig = self.getConfig(regBaseYml, args.part, self.data['BaseAddrCfg'])
        self.sequenceCfg = self._encodeCfg()
        self.contWrPos = seqData['SequenceCfg']['CNTWRPOS']
        self.value = []
        self.lengthWord = 0
        self.condition = seqData.get('Condition')
        self.isConst = self.isSequenceConst(self.data['Sequence'])

    @staticmethod
    def getConfig(baseDict, *argv, default=None):
        #print("getConfig...........................")
        returnDict = baseDict
        for arg in argv:
            #print(arg)
            try:
                returnDict = returnDict[arg]
            except KeyError:
                return default
        return returnDict

    @staticmethod
    def isSequenceConst(instructionList):
        isConst = True
        for inst in instructionList:
            for action, actionValue in inst.items():
                if type(actionValue) is list:
                    for el in actionValue:
                        subVal = next(iter(el.values()))
                        if type(subVal) is dict and subVal.get('DEFINE'):
                            # DEFINE found, then the sequence is not const
                            isConst = False
                            break
        return isConst

    @staticmethod
    def conditionLength(conditionValue):
        length = 0
        for subcmd in conditionValue:
            for action, value in subcmd.items():
                if action in ['NOP', 'ENDSEQ']:
                    length += 4  # instruction, no data
                elif type(value) is list:
                    isDefine = False

                    # Check if there is a DEFINE hidden inside this list
                    for el in value:
                        subVal = next(iter(el.values()))
                        if type(subVal) is dict and subVal.get('DEFINE'):
                            # DEFINE found, then the sequence length is instruction + data
                            isDefine = True
                            break
                    if isDefine:
                        length += 8
                    else:
                        length += 4 + 4 * len(value)  # instruction + contWr
                else:
                    length += 8  # instruction + data
        return length

    def _encodeCfg(self):
        config = self.data['SequenceCfg']
        return (config.get('MOVSWAP', 0) << 14) | (config.get('DISABSRST', 0) << 13) | (config.get('HWSTTRIG', 0) << 10)\
                | (config.get('HWSTSEL', 0)) << 5 | config.get('CNTWRPOS', 16)

    def getLength(self):
        length = 0
        for obj in self.value:
            length += obj.getLength()
        self.lengthWord = length
        return length

    def branch(self, instructionList):
        """
        Find and develop branch syntax in the sequence.
        This function translate an If/Else condition using SKIPCOND_ and JUMP instructions.
        """
        for index, command in enumerate(instructionList):
            if command.get('IF') and instructionList[index + 1].get('ELSE'):
                # Recursive search for nested conditions
                indexIf = index
                indexElse = indexIf + 1

                self.branch(command['IF'])
                valueElse = instructionList[indexElse]['ELSE']
                self.branch(valueElse)

                # IF
                conditionInst = instructionList[indexIf]['IF'][0]
                valueIf = instructionList[indexIf]['IF'][1:]
                lenIf = self.conditionLength(valueIf)
                lenElse = self.conditionLength(valueElse)

                # Replace If instruction by SKIPCOND instruction
                # and extract values from If and copy them into the sequence
                instructionList[indexIf] = conditionInst
                for actionIf in valueIf:
                    instructionList.insert(indexElse, actionIf)
                    indexElse += 1
                # Add JUMP to reach end of Else condition
                instructionList.insert(indexElse, {'JUMP': lenElse})
                indexElse += 1
                lenIf += 8  # Add JUMP instruction length

                # ELSE
                # Insert JUMP right after SKIPCOND instruction to reach end of If condition
                instructionList.insert(indexIf + 1, {'JUMP': lenIf})
                indexElse += 1
                # Extract values from Else and copy them into the sequence
                for actionElse in valueElse:
                    instructionList.insert(indexElse, actionElse)
                    indexElse += 1
                # Finally, erase ELSE instruction now that its instructions have been copied
                del instructionList[indexElse]

    def getInstructionIndex(self, seqIdx):
        actionIdx = 0
        instIdx = 0
        lastAction = self.value[-1].inst
        for info in lastAction.values():
            for instruction in info:
                if type(instruction[1]) is dict:
                    define = instruction[1].get('DEFINE')
                    if define is not None:
                        define += ' ' + str(1 + seqIdx + actionIdx + instIdx)
                        # update value
                        instruction[1]['DEFINE'] = define
                instIdx += 1
            actionIdx += 1

    def commandCheck(self, action, value):
        try:
            value = value.get('VALUE')
        except AttributeError:
            pass

        # opcode without arg check
        if action in ['NOP', 'ENDSEQ']:
            assert value is None, "OpCode {} in {} is a single word instruction and shall not have " \
                                  "any value".format(action, self.name)
        # OpCode supporting arg of type int check
        elif action in ['DELAY', 'DELAYABS', 'JUMP']:
            assert type(value) is int, "OpCode {} in {} is a 2 words instruction and must have a unique value" \
                                       " of type int".format(action, self.name)
        # OpCode supporting arg of type int and str check
        elif action in ['JUMPABS']:
            assert type(value) is str or type(value) is int, "OpCode {} in {} is a 2 words instruction and must have " \
                                                             "a unique value either of type str or int".format(action, self.name)
        # OpCode supporting arg of type dictionaries...
        else:
            assert value is not None, "OpCode {} in {} is a 2 words instruction and must have a list of at least " \
                                      "one value".format(action, self.name)

    def sequenceHandler(self):
        seqBaseIdxCount = 0  # Holds the count of the sequences traversed
        self.branch(self.data['Sequence'])

        for seqInstr in self.data['Sequence']:
            for command, value in seqInstr.items():
                # Encode actions and macros
                if command in MACROS:
                    value = self.getConfig(MACROS, command, 'arg', default=value)
                    isNotArg = self.getConfig(MACROS, command, 'isNotArg', default=False)
                    action = self.getConfig(MACROS, command, 'Action')
                else:
                    action = command
                    isNotArg = False

                # Safety check
                self.commandCheck(action, value)

                # Store action into instruction list
                self.value.append(Action(action, value, self.baseAddrConfig, self.contWrPos, isNotArg=isNotArg))

                # Manage defines and indexes
                self.getInstructionIndex(seqBaseIdxCount)
                seqBaseIdxCount = self.getLength()
        self.getLength()


class SequenceGenerator(object):
    def __init__(self, fileName):
        self.source = open(os.path.join(destination, fileName + '.c'), "w+")
        self.header = open(os.path.join(destination, fileName + '.h'), "w+")
        self.env = Environment(loader=FileSystemLoader(TEMPLATE_PATH))
        print("Output code files: {}, \n{}".format(os.path.join(destination, fileName + ".c"),
                                                   os.path.join(destination, fileName + ".h")))

        self.env.filters['getAddrFromInst'] = self.getAddrFromInst
        self.env.filters['printAction'] = self.printAction

        if args.template:
            self.template_source = self.env.get_template("{}.c.j2".format(args.template))
            self.template_header = self.env.get_template("{}.h.j2".format(args.template))
        else:
            self.template_source = self.env.get_template("seqacc_default.c.j2")
            self.template_header = self.env.get_template("seqacc_default.h.j2")

    def render(self, context):
        source_output = self.template_source.render(context)
        header_output = self.template_header.render(context)
        self.source.write(source_output)
        self.header.write(header_output)

        self.source.close()
        self.header.close()

    # Filter definition
    @staticmethod
    def getAddrFromInst(action, instruction):
        offsetMask = 2**action.contWrPos - 1
        offset = instruction & offsetMask
        baseAddrMask = 2**(28 - action.basePos) - 1  # 28: opCode bit position
        baseAddrId = (instruction >> action.basePos) & baseAddrMask

        if action.isSimpleArg:
            return " /* {} */".format(action.name)
        else:
            baseAddr = [addr for addr, Id in action.baseAddrConfig.items() if Id == baseAddrId][0]
            baseAddr += offset
            return " /* {0} at 0x{1:08X} */".format(action.name, baseAddr)

    @staticmethod
    def printAction(action, value):
        if type(value) is dict:
            value = value['VALUE']

        if type(value) is int:
            return " 0x{0:08X}UL,".format(value)
        elif value is not None:
            printValue = ' {},'.format(value)
            if action.isSimpleArg and action.name == 'JUMPABS':
                printValue = " (uint32_t)" + printValue
            return printValue
        else:
            return ''


if __name__ == "__main__":
    """
    For more details on how to use this tool, please read the documention
    at https://confluence.silabs.com/display/RFSW/Sequence+Compiler
    """

    parser = argparse.ArgumentParser(description='Run SEQACC sequence compiler')
    parser.add_argument('--source',
                         help='YAML source script to process. Usually stored in rail_lib/chip/efr32/seq_s3/.',
                         type=str,
                         required=True)
    parser.add_argument('--destination',
                         help='Destination folder for the output C header file. Default points to same source directory',
                         type=str)
    parser.add_argument('--regbase',
                        help='YAML regBases source to process.'
                             'Default is seqacc_regbases.yml located alongside the compiler.',
                        type=str,
                        default=os.path.join(os.path.dirname(os.path.realpath(__file__)), 'seqacc_regbases.yml'))
    parser.add_argument('--part',
                         help='The part\'s code name that will execute the sequence.',
                         type=str,
                         default='rainier')
    parser.add_argument('--template',
                        help='Override default template file',
                        type=str,
                        required=False)
    parser.add_argument('--internal',
                         help='Compute the register addresses and other defines',
                         action='store_true')
    args = parser.parse_args()
    #print(args)
    if args.destination is None:
        destination = os.path.join(os.path.dirname(args.source))
    else:
        destination = args.destination

    print('YAML regBase source path: {}', format(args.regbase))
    regBaseYml = yaml.safe_load(open(args.regbase))
    print('YAML sequence source path: {}', format(args.source))
    ymlData = yaml.safe_load(open(args.source))

    # Create a proper rm object depending on partFamily
    rm_factory = RM_Factory(args.part.upper())
    rm = rm_factory()

    YmlInfo = {'Sequences': {}, 'RegBases': {}, 'internal': args.internal}
    for name, data in ymlData['Sequences'].items():
        assert ymlData['Sequences'][name].get('BaseAddrCfg'), "No BaseAddrCfg field found in sequence {}".format(name)
        assert ymlData['Sequences'][name].get('SequenceCfg'), "No SequenceCfg field found in sequence {}".format(name)

        seq = Sequence(name, data)
        seq.sequenceHandler()
        YmlInfo['Sequences'][name] = seq

        if seq.data['BaseAddrCfg'] not in YmlInfo['RegBases']:
            YmlInfo['RegBases'][seq.data['BaseAddrCfg']] = {}
            YmlInfo['RegBases'][seq.data['BaseAddrCfg']]['BaseAddr'] = seq.baseAddrConfig['BaseAddr']
            YmlInfo['RegBases'][seq.data['BaseAddrCfg']]['BasePos'] = seq.basePos << 4

        print("\n{}: {} bytes".format(seq.name, seq.lengthWord * 4))

    generator = SequenceGenerator(ymlData["Name"])
    generator.render(YmlInfo)
