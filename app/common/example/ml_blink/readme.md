# Machine Learning - Blink

This application is meant to be a starting point when creating a machine
learning application. It demonstrates how to deploy and run inference on a
Tensorflow Lite model, which involves the following steps:

 * Converting the .tflite model data to a C header (this is done automatically
   upon project generation, and when you drag a model into a Simplicity Studio
   project)
 * Automatically initialize a TFLM (Tensorflow Lite for Microcontrollers) model
   interpreter, and allocate memory buffer based on an arena size configuration
   value from the project
 * Fetch input data and load this into the model interpreter input tensor
 * Run inference by invoking the model interpreter
 * Fetch output data from the model interpreter output tensor
 * Use the model output for program flow

The model used in the application is a regression model, trained to replicate a
sine function. Input and output is a single floating point value represented as
a quantized 8 bit value as we are using an integer only quantized model. The
model is continuously fed with values ranging from 0 to 2pi, and the output of
the model is used to control the intensity of an LED. Inference results are also
printed over VCOM.

This model used is based on TensorFlow's hello world application. For details
about the original application or information on how to train your own model,
visit the TensorFlow 
**[GitHub page](https://github.com/tensorflow/tflite-micro/tree/main/tensorflow/lite/micro/examples/hello_world)**.
