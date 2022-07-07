# Tensorflow model profiler

This application is designed to profile a Tensorflow Lite Micro model on Silicon
Labs hardware. The model used by the application is provided by a Tensorflow
Lite flatbuffer file called model.tflite in the config/tflite subdirectory. The
profiler will measure the number of CPU clock cycles and elapsed time in each
layer of the model when performing an inference. It will also produce a summary
when inference is done. The input layer of the model is filled with all zeroes
before performing a single inference. Profiling results are transmitted over
VCOM.
