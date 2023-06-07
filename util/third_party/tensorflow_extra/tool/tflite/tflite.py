#!/usr/bin/env python3

import sys
import argparse
from string import Template
import re
from pathlib import Path

# Patch site-packages to find numpy
import jinja2
if sys.platform.startswith("win"):
  site_packages_path = (Path(jinja2.__file__).parent / "../../../ext-site-packages").resolve()
else:
  site_packages_path = (Path(jinja2.__file__).parent / "../../../../ext-site-packages").resolve()
if site_packages_path.exists() and str(site_packages_path) not in sys.path:
    sys.path.insert(0, str(site_packages_path))

# Generation of parameter files requires the tflite_model, tflite_model_parameters
# and tensorflow_lite_support packages. Because these packages are not installed
# in the uc-generation environment where this python script will be run, these
# packages are supplied as source. tflite_model and tflite_model_parameters were
# fetched from internal repos, while the tensorflow_lite_support was fetched from
# https://github.com/tensorflow/tflite-support.
from tflite.Model import Model
from tflite.BuiltinOperator import BuiltinOperator
from tflite_model_parameters import TfliteModelParameters

model_data_h = """// Auto-generated serialization of TFLite flatbuffers in config directory
#ifndef SL_TFLITE_MICRO_MODEL_H
#define SL_TFLITE_MICRO_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern const uint8_t sl_tflite_model_array[];
extern const uint32_t sl_tflite_model_len;

#ifdef __cplusplus
}
#endif

#endif // SL_TFLITE_MICRO_MODEL_H
"""

template_model_data_c = """// Auto-generated serialization of TFLite flatbuffers in config directory

#include "em_device.h"
#include "sl_tflite_micro_model.h"

// Model data generated from "${model_name}.tflite"
const uint8_t sl_tflite_model_array[] __ALIGNED(4) = {
  ${data}
};

const uint32_t sl_tflite_model_len = ${data_len}UL;
"""

template_opcode_resolver_h = """// Auto-generated macro to instanciate and initialize opcode resolver based on TFLite flatbuffers in config directory
#ifndef SL_TFLITE_MICRO_OPCODE_RESOLVER_H
#define SL_TFLITE_MICRO_OPCODE_RESOLVER_H

#define SL_TFLITE_MICRO_OPCODE_RESOLVER(opcode_resolver) \\
static tflite::MicroMutableOpResolver<${data_len}> opcode_resolver; \\
${data}

#endif // SL_TFLITE_MICRO_OPCODE_RESOLVER_H
"""

template_model_parameter_single = """#define SL_TFLITE_MODEL_${config_key} ${config_val}
"""

template_model_parameters_h = """// Auto-generated parameters from TFLite flatbuffers in config directory
#ifndef SL_TFLITE_MICRO_MODEL_PARAMETERS_H
#define SL_TFLITE_MICRO_MODEL_PARAMETERS_H

// Definitions generated from "${model_name}.tflite"'
${data}
#endif // SL_TFLITE_MICRO_MODEL_PARAMETERS_H
"""
"""
The following dictionary has been created using the BuiltinOperator enum defining operatior values, see schema_generated.h, and
function names defined in the MicroMutableOpResolver object, see micro_mutable_op_resolver.h.
"""
opcode_dict = {
    BuiltinOperator.ABS: 'AddAbs',
    BuiltinOperator.ADD: 'AddAdd',
    BuiltinOperator.ADD_N: 'AddAddN',
    BuiltinOperator.ARG_MAX: 'AddArgMax',
    BuiltinOperator.ARG_MIN: 'AddArgMin',
    BuiltinOperator.ASSIGN_VARIABLE: 'AddAssignVariable',
    BuiltinOperator.AVERAGE_POOL_2D: 'AddAveragePool2D',
    BuiltinOperator.BATCH_TO_SPACE_ND: 'AddBatchToSpaceNd',
    BuiltinOperator.BROADCAST_ARGS: 'AddBroadcastArgs',
    BuiltinOperator.BROADCAST_TO: 'AddBroadcastTo',
    BuiltinOperator.CALL_ONCE: 'AddCallOnce',
    BuiltinOperator.CAST: 'AddCast',
    BuiltinOperator.CEIL: 'AddCeil',
#    AddCircularBuffer (custom)
    BuiltinOperator.CONCATENATION: 'AddConcatenation',
    BuiltinOperator.CONV_2D: 'AddConv2D',
    BuiltinOperator.COS: 'AddCos',
    BuiltinOperator.CUMSUM: 'AddCumSum',
    BuiltinOperator.DEPTH_TO_SPACE: 'AddDepthToSpace',
    BuiltinOperator.DEPTHWISE_CONV_2D: 'AddDepthwiseConv2D',
    BuiltinOperator.DEQUANTIZE: 'AddDequantize',
#    AddDetectionPostprocess (custom)
    BuiltinOperator.ELU: 'AddElu',
    BuiltinOperator.EQUAL: 'AddEqual',
#    AddEthosU (custom)
    BuiltinOperator.EXP: 'AddExp',
    BuiltinOperator.EXPAND_DIMS: 'AddExpandDims',
    BuiltinOperator.FILL: 'AddFill',
    BuiltinOperator.FLOOR: 'AddFloor',
    BuiltinOperator.FLOOR_DIV: 'AddFloorDiv',
    BuiltinOperator.FLOOR_MOD: 'AddFloorMod',
    BuiltinOperator.FULLY_CONNECTED: 'AddFullyConnected',
    BuiltinOperator.GATHER: 'AddGather',
    BuiltinOperator.GATHER_ND: 'AddGatherNd',
    BuiltinOperator.GREATER: 'AddGreater',
    BuiltinOperator.GREATER_EQUAL: 'AddGreaterEqual',
    BuiltinOperator.HARD_SWISH: 'AddHardSwish',
    BuiltinOperator.IF: 'AddIf',
    BuiltinOperator.L2_NORMALIZATION: 'AddL2Normalization',
    BuiltinOperator.L2_POOL_2D: 'AddL2Pool2D',
    BuiltinOperator.LEAKY_RELU: 'AddLeakyRelu',
    BuiltinOperator.LESS: 'AddLess',
    BuiltinOperator.LESS_EQUAL: 'AddLessEqual',
    BuiltinOperator.LOG: 'AddLog',
    BuiltinOperator.LOGICAL_AND: 'AddLogicalAnd',
    BuiltinOperator.LOGICAL_NOT: 'AddLogicalNot',
    BuiltinOperator.LOGICAL_OR: 'AddLogicalOr',
    BuiltinOperator.LOGISTIC: 'AddLogistic',
    BuiltinOperator.MAX_POOL_2D: 'AddMaxPool2D',
    BuiltinOperator.MAXIMUM: 'AddMaximum',
    BuiltinOperator.MEAN: 'AddMean',
    BuiltinOperator.MINIMUM: 'AddMinimum',
    BuiltinOperator.MIRROR_PAD: 'AddMirrorPad',
    BuiltinOperator.MUL: 'AddMul',
    BuiltinOperator.NEG: 'AddNeg',
    BuiltinOperator.NOT_EQUAL: 'AddNotEqual',
    BuiltinOperator.PACK: 'AddPack',
    BuiltinOperator.PAD: 'AddPad',
    BuiltinOperator.PADV2: 'AddPadV2',
    BuiltinOperator.PRELU: 'AddPrelu',
    BuiltinOperator.QUANTIZE: 'AddQuantize',
    BuiltinOperator.READ_VARIABLE: 'AddReadVariable',
    BuiltinOperator.REDUCE_MAX: 'AddReduceMax',
    BuiltinOperator.RELU: 'AddRelu',
    BuiltinOperator.RELU6: 'AddRelu6',
    BuiltinOperator.RESHAPE: 'AddReshape',
    BuiltinOperator.RESIZE_BILINEAR: 'AddResizeBilinear',
    BuiltinOperator.RESIZE_NEAREST_NEIGHBOR: 'AddResizeNearestNeighbor',
    BuiltinOperator.ROUND: 'AddRound',
    BuiltinOperator.RSQRT: 'AddRsqrt',
    BuiltinOperator.SHAPE: 'AddShape',
    BuiltinOperator.SIN: 'AddSin',
    BuiltinOperator.SLICE: 'AddSlice',
    BuiltinOperator.SOFTMAX: 'AddSoftmax',
    BuiltinOperator.SPACE_TO_BATCH_ND: 'AddSpaceToBatchNd',
    BuiltinOperator.SPACE_TO_DEPTH: 'AddSpaceToDepth',
    BuiltinOperator.SPLIT: 'AddSplit',
    BuiltinOperator.SPLIT_V: 'AddSplitV',
    BuiltinOperator.SQRT: 'AddSqrt',
    BuiltinOperator.SQUARE: 'AddSquare',
    BuiltinOperator.SQUEEZE: 'AddSqueeze',
    BuiltinOperator.STRIDED_SLICE: 'AddStridedSlice',
    BuiltinOperator.SUB: 'AddSub',
    BuiltinOperator.SVDF: 'AddSvdf',
    BuiltinOperator.TANH: 'AddTanh',
    BuiltinOperator.TRANSPOSE: 'AddTranspose',
    BuiltinOperator.TRANSPOSE_CONV: 'AddTransposeConv',
    BuiltinOperator.UNPACK: 'AddUnpack',
    BuiltinOperator.VAR_HANDLE: 'AddVarHandle',
    BuiltinOperator.WHILE: 'AddWhile',
    BuiltinOperator.ZEROS_LIKE: 'AddZerosLike',
}

def sanitize_filename(name):
  # Strip invalid characters
  name = re.sub(r'[^a-zA-Z0-9_]', '', name)
  # C variables can't start with a number
  name = name.lstrip('0123456789')
  return name


def find_first_tflite_file(input_dir: Path):
  '''
  Return the alphabetically sorted first tflite filename and content
  '''
  candidates = sorted(input_dir.glob("**/*.tflite"))
  if not candidates:
    print("tflite.py INFO: No tflite file found - exiting.")
    sys.exit(0)

  tflite_file = candidates[0]
  if 1 < len(candidates):
    listing = "\n- ".join(str(cand) for cand in candidates)
    print(f"tflite.py WARNING: Multiple tflite files found:\n- {listing}")
    print(f"Defaulting to converting {tflite_file}")

  with open(tflite_file, "rb") as fd:
    data = fd.read()

  return tflite_file.stem, data

def generate_c_array(buf):
  arr = ''
  for i, ch in enumerate(buf):
    if (i % 12) == 0:
      arr += '\n  '
    arr += '0x{:02x}, '.format(ch)

  return arr.lstrip().rstrip(', ')

def opcode_parse_opcode(opcode):
  if opcode.CustomCode() is not None:
    opcode_val = opcode.CustomCode()
  else:
    opcode_val = opcode.DeprecatedBuiltinCode()
    if opcode_val == BuiltinOperator.PLACEHOLDER_FOR_GREATER_OP_CODES:
      opcode_val = opcode.BuiltinCode()

  if opcode_val in opcode_dict.keys():
    opcode_func = opcode_dict[opcode_val]
    opcode_entry = {opcode_val: opcode_func}
  else:
    print(f"tflite.py WARNING: An unknown operator with code value={opcode_val} has been discovered. It will not be automatic initialized.")
    opcode_entry = {-1: "UndefinedOp"}
  return opcode_entry

def opcode_parse_model(model):
  opcodes = {}
  for index in range(model.OperatorCodesLength()):
    opcode = model.OperatorCodes(index)
    opcodes.update(opcode_parse_opcode(opcode))
  return opcodes

def generate_c_type(value):
  if type(value) is list:
        c_list =[]
        for item in value:
          c_list.append(generate_c_type(item))
        value = "{" + ', '.join(c_list) + "}"
  elif type(value) == str:
    value = f'"{value}"'
  elif type(value) == bool:
    value = str(value).lower()
  elif type(value) == float:
    value = str(value) + "f"
  return value

def generate_files(input_dir: Path, output_dir: Path):
  model_name, buf = find_first_tflite_file(input_dir)

  # Generate model data
  props = {
    'model_name': model_name,
    'data': generate_c_array(buf),
    'data_len': len(buf),
  }
  tc = Template(template_model_data_c)
  model_data_c = tc.substitute(**props)

  # Generate OP code resolver
  opcodes = {}
  model = Model.GetRootAsModel(buf)
  opcodes.update(opcode_parse_model(model))
  opcode_len = len(opcodes)
  opcode_str = ''
  for opcode_key in opcodes.keys():
    if opcode_key != BuiltinOperator.CUSTOM:
      opcode_str += f"opcode_resolver.{opcodes[opcode_key]}(); \\\n"
  tm = Template(template_opcode_resolver_h)
  opcode_data = tm.substitute({'data_len':str(opcode_len), 'data':opcode_str})

  # Extract model parameters
  parameter_defines = ''
  try:
    loaded_model_params = TfliteModelParameters.load_from_tflite_flatbuffer(buf)
  except:
    loaded_model_params = {}
  if loaded_model_params:
    param_define_t = Template(template_model_parameter_single)
    for key, value in sorted(loaded_model_params.items()):
      # Ensure valid C code:
      c_value = generate_c_type(value)
      props = {
        'config_key': key.replace('.', '_').upper(),
        'config_val': c_value,
      }
      parameter_defines += param_define_t.substitute(**props)
    parameter_defines += '\n'

  with open(Path(output_dir, 'sl_tflite_micro_model.h'), 'w') as fd:
    fd.write(model_data_h)
  with open(Path(output_dir, 'sl_tflite_micro_model.c'), 'w') as fd:
    fd.write(model_data_c)
  with open(Path(output_dir, 'sl_tflite_micro_opcode_resolver.h'), 'w') as fd:
    fd.write(opcode_data)
  # Only emit this file if model parameters are available
  if parameter_defines:
    tp = Template(template_model_parameters_h)
    with open(Path(output_dir, 'sl_tflite_micro_model_parameters.h'), 'w') as fd:
      fd.write(tp.substitute(data=(parameter_defines), model_name=model_name))



def entry():
  parser = argparse.ArgumentParser(description='TensorFlow Lite flatbuffer to C converter.')
  parser.add_argument('-i', required=True, type=Path, help='Input directory containing .tflite files')
  parser.add_argument('-o', required=True, type=Path, help='Output directory to populate with serialized content.')
  args = parser.parse_args()

  generate_files(args.i, args.o)

if __name__ == "__main__":
  entry()