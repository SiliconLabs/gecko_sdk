
#include "tensorflow/lite/kernels/internal/reference/mul.h"

#include "Include/arm_nnfunctions.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/mul.h"
#include "tensorflow/lite/kernels/internal/reference/process_broadcast_shapes.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/kernel_util.h"
#include "tensorflow/lite/micro/kernels/mul.h"
#include "tensorflow/lite/micro/memory_helpers.h"
#include "tensorflow/lite/micro/micro_log.h"

#include "sl_mvp_ml_mul.h"

namespace tflite {
namespace sl {
namespace mul {

struct SlOpDataMul {
  tflite::OpDataMul opdata;
  sli_mvp_ml_mul_s8_params_t params;
};

void* MulInit(TfLiteContext* context, const char* buffer, size_t length) {
  TFLITE_DCHECK(context->AllocatePersistentBuffer != nullptr);
  return context->AllocatePersistentBuffer(context, sizeof(SlOpDataMul));
}

TfLiteStatus CalculateMvpParams(TfLiteContext* context, TfLiteNode* node,
                                TfLiteMulParams* params, SlOpDataMul* data) {
  memset(&data->params, 0, sizeof(sli_mvp_ml_mul_s8_params_t));

  MicroContext* micro_context = GetMicroContext(context);

  TfLiteTensor* input1 = micro_context->AllocateTempInputTensor(node, kMulInput1Tensor);
  TfLiteTensor* input2 = micro_context->AllocateTempInputTensor(node, kMulInput2Tensor);
  TfLiteTensor* output = micro_context->AllocateTempOutputTensor(node, kMulOutputTensor);

  // only int8 quantization is supported
  if (output->type == kTfLiteInt8) {
    double real_multiplier = static_cast<double>(input1->params.scale) *
                              static_cast<double>(input2->params.scale) /
                              static_cast<double>(output->params.scale);

    data->params.input1_offset = - input1->params.zero_point;
    data->params.input2_offset = - input2->params.zero_point;
    data->params.output_offset = output->params.zero_point;
    data->params.output_multiplier = static_cast<float>(real_multiplier);
    data->params.activation_min = static_cast<int8_t>(data->opdata.output_activation_min);
    data->params.activation_max = static_cast<int8_t>(data->opdata.output_activation_max);
  }

  micro_context->DeallocateTempTfLiteTensor(input1);
  micro_context->DeallocateTempTfLiteTensor(input2);
  micro_context->DeallocateTempTfLiteTensor(output);
  return kTfLiteOk;
}

TfLiteStatus MulPrepare(TfLiteContext* context, TfLiteNode* node) {
  TFLITE_DCHECK(node->builtin_data != nullptr);
  auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);

  TFLITE_DCHECK(node->user_data != nullptr);
  SlOpDataMul* data = static_cast<SlOpDataMul*>(node->user_data);

  TF_LITE_ENSURE_STATUS(CalculateOpDataMul(context, node, params, &data->opdata));
  TfLiteStatus status = CalculateMvpParams(context, node, params, data);
  return status;
}

TfLiteStatus EvalQuantized(TfLiteContext* context, TfLiteNode* node,
                           const SlOpDataMul* sldata, const TfLiteEvalTensor* input1,
                           const TfLiteEvalTensor* input2, TfLiteEvalTensor* output)
{
  sl_status_t status = SL_STATUS_OK;
  const OpDataMul* data = &sldata->opdata;
  tflite::ArithmeticParams op_params = {};

  op_params.quantized_activation_min = data->output_activation_min;
  op_params.quantized_activation_max = data->output_activation_max;
  op_params.float_activation_max = data->output_activation_max_f32;
  op_params.input1_offset = -data->input1_zero_point;
  op_params.input2_offset = -data->input2_zero_point;
  op_params.output_offset = data->output_zero_point;
  op_params.output_multiplier = data->output_multiplier;
  op_params.output_shift = data->output_shift;

  bool need_broadcast = reference_ops::ProcessBroadcastShapes(
      tflite::micro::GetTensorShape(input1),
      tflite::micro::GetTensorShape(input2), &op_params);

  if (need_broadcast) {
    if (input1->type == kTfLiteInt8) {
      reference_integer_ops::BroadcastMul4DSlow(
          op_params, tflite::micro::GetTensorShape(input1),
          tflite::micro::GetTensorData<int8_t>(input1),
          tflite::micro::GetTensorShape(input2),
          tflite::micro::GetTensorData<int8_t>(input2),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int8_t>(output));
    } else if (input1->type == kTfLiteInt16) {
      reference_integer_ops::BroadcastMul4DSlow(
          op_params, tflite::micro::GetTensorShape(input1),
          tflite::micro::GetTensorData<int16_t>(input1),
          tflite::micro::GetTensorShape(input2),
          tflite::micro::GetTensorData<int16_t>(input2),
          tflite::micro::GetTensorShape(output),
          tflite::micro::GetTensorData<int16_t>(output));
    }

  } else {
    if (input1->type == kTfLiteInt8) {
      sli_mvp_ml_mul_s8_params_t params = sldata->params;
      params.input1 = tflite::micro::GetTensorData<int8_t>(input1);
      params.input2 = tflite::micro::GetTensorData<int8_t>(input2);
      params.output = tflite::micro::GetTensorData<int8_t>(output);
      params.length = MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                               tflite::micro::GetTensorShape(input2),
                               tflite::micro::GetTensorShape(output));
      status = sli_mvp_ml_mul_s8(&params);
    } else if (input1->type == kTfLiteInt16) {
      arm_elementwise_mul_s16(
          tflite::micro::GetTensorData<int16_t>(input1),
          tflite::micro::GetTensorData<int16_t>(input2),
          op_params.input1_offset, op_params.input2_offset,
          tflite::micro::GetTensorData<int16_t>(output),
          op_params.output_offset, op_params.output_multiplier,
          op_params.output_shift, op_params.quantized_activation_min,
          op_params.quantized_activation_max,
          MatchingElementsSize(tflite::micro::GetTensorShape(input1),
                               tflite::micro::GetTensorShape(input2),
                               tflite::micro::GetTensorShape(output)));
    }
  }
  return status == SL_STATUS_OK ? kTfLiteOk : kTfLiteError;
}

TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node)
{
  TfLiteStatus status = kTfLiteOk;
  TFLITE_DCHECK(node->builtin_data != nullptr);
  auto* params = reinterpret_cast<TfLiteMulParams*>(node->builtin_data);

  TFLITE_DCHECK(node->user_data != nullptr);
  const SlOpDataMul* data = static_cast<const SlOpDataMul*>(node->user_data);

  const TfLiteEvalTensor* input1 =
      tflite::micro::GetEvalInput(context, node, kMulInput1Tensor);
  const TfLiteEvalTensor* input2 =
      tflite::micro::GetEvalInput(context, node, kMulInput2Tensor);
  TfLiteEvalTensor* output =
      tflite::micro::GetEvalOutput(context, node, kMulOutputTensor);

  switch (input1->type) {
    case kTfLiteInt8:
    case kTfLiteInt16:
      status = EvalQuantized(context, node, data, input1, input2, output);
      break;
    case kTfLiteInt32:
      EvalMulQuantizedReference(context, node, &data->opdata, input1, input2, output);
      break;
    case kTfLiteFloat32:
      EvalMulFloatReference(context, node, params, &data->opdata, input1, input2, output);
      break;
    default:
      TF_LITE_KERNEL_LOG(context, "Type %s (%d) not supported.",
                  TfLiteTypeGetName(input1->type), input1->type);
      return kTfLiteError;
  }

  return status;
}

} // namespace mul
} // namespace sl

TFLMRegistration Register_MUL() {
  return tflite::micro::RegisterOp(sl::mul::MulInit, sl::mul::MulPrepare, sl::mul::Eval);
}

}  // namespace tflite
