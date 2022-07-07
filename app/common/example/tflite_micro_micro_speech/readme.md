# TensorFlow Lite Micro - Micro Speech

This application demonstrates a model trained to recognize the words "yes" and
"no" from speech data recorded from the microphone. The detected keywords are
transmitted over VCOM. LED 0 is toggled every time model inference is performed
to give an indication of the processing speed of the model.

This application is a port of TensorFlow's micro speech application. For details 
about the application or information on how to train your own model, visit 
TensorFlow Lite Micro's [GitHub page](https://github.com/tensorflow/tflite-micro/tree/3e190e5389be49c94475e509452bdae245bd4fa6/tensorflow/lite/micro/examples/micro_speech).
