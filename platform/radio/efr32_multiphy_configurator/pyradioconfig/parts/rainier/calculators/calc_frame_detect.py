from pycalcmodel.core.variable import ModelVariableFormat
from pyradioconfig.parts.bobcat.calculators.calc_frame_detect import Calc_Frame_Detect_Bobcat
from pyradioconfig.calculator_model_framework.Utils.LogMgr import LogMgr


class CalcFrameDetectRainier(Calc_Frame_Detect_Bobcat):

    def buildVariables(self, model):
        """Populates a list of needed variables for this calculator

        Args:
            model (ModelRoot) : Builds the variables specific to this calculator
        """
        super().buildVariables(model)
        self._addModelVariable(model, 'syncword_trisync', bool, ModelVariableFormat.ASCII, desc='Enable tri syncword detection')

    def calc_syncerrors_reg(self, model):
        #This function calulates the SYNCERRORS field

        #Read in model variables
        demod_select = model.vars.demod_select.value
        rtschmode_actual = model.vars.MODEM_REALTIMCFE_RTSCHMODE.value
        directmode_rx = model.vars.directmode_rx.value
        mod_type = model.vars.modulation_type.value

        if directmode_rx != model.vars.directmode_rx.var_enum.DISABLED and mod_type == model.vars.modulation_type.var_enum.FSK2:
            syncerrors = 2
        #Allow 1 sync error if using TRECS and RTSCHMODE = 1 (hard slicing instead of CFE)
        elif demod_select == model.vars.demod_select.var_enum.TRECS_VITERBI or \
                demod_select == model.vars.demod_select.var_enum.TRECS_SLICER:
            if rtschmode_actual == 1:
                syncerrors = 1
            else:
                syncerrors = 0
        else:
            syncerrors = 0

        #Write the register
        self._reg_write(model.vars.MODEM_CTRL1_SYNCERRORS, syncerrors)
        self._reg_write(model.vars.MODEM_SYNCWORDCTRL_SYNC0ERRORS, syncerrors)
        self._reg_write(model.vars.MODEM_SYNCWORDCTRL_SYNC1ERRORS, syncerrors)
        self._reg_write(model.vars.MODEM_SYNCWORDCTRL_SYNC2ERRORS, 0) ##fix me

    def calc_trisync(self, model):
        # FIXME: Need to make a profile input eventually
        # sync2 = model.vars.syncword_2_actual.value
        sync2 = 0

        if sync2 > 0:
            syncword_trisync = True
        else:
            syncword_trisync = False

        model.vars.syncword_trisync.value = syncword_trisync

    def calc_dualsync_reg(self, model):

        demod_sel = model.vars.demod_select.value
        dualsync = model.vars.syncword_dualsync.value
        timingbases = model.vars.timingbases_actual.value
        trisync = model.vars.syncword_trisync.value

        # dualsync is disabled in FDM0 mode (MCUW_RADIO_CFG-1732)
        if dualsync == False:
            reg1_value = 0
        elif dualsync == True and timingbases == 0 and demod_sel == model.vars.demod_select.var_enum.LEGACY:
            LogMgr.Warning("Second syncword is not supported if preamble is shorter than 8 bits and legacy demod is used")
            reg1_value = 0
        else:
            reg1_value = 1

        if trisync == False:
            reg2_value = 0
        else:
            reg1_value = 1
            reg2_value = 1

        self._reg_write(model.vars.MODEM_SYNCWORDCTRL_DUALSYNC, reg1_value)
        self._reg_write(model.vars.MODEM_SYNCWORDCTRL_SYNCDET2TH, reg2_value)

    def calc_syncbits_reg(self, model):
        """
        write sync word length from input to register

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        if model.vars.syncword_length.value < 2:
            LogMgr.Error("Syncword length must be at least 2")

        if model.vars.ber_force_sync.value == True:
            syncword_length = 32
        else:
            syncword_length = model.vars.syncword_length.value

        # FIXME: amtudave: Remove SYNCBITS once tri-sync control added to sync_det
        self._reg_write(model.vars.MODEM_CTRL1_SYNCBITS, syncword_length - 1)
        # self._reg_write(model.vars.MODEM_SYNCWORDCTRL_SYNC0BITS, syncword_length - 1)
        #self._reg_write(model.vars.MODEM_SYNCWORDCTRL_SYNCBITS2TH, syncword_length - 1)

    def calc_syncword_length_actual(self, model):
        """given register read back actual sync word length

        Args:
            model (ModelRoot) : Data model to read and write variables from
        """

        model.vars.syncword_length_actual.value = model.vars.MODEM_CTRL1_SYNCBITS.value + 1

