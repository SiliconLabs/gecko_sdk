# Audio Classifier
This application uses TensorFlow Lite for Microcontrollers to run audio
classification machine learning models to classify words from audio data
recorded from a microphone. The detection is visualized using the LED's on the
board and the classification results are written to the VCOM serialport.

## Behavior
The application is using two LEDs to show detection and activity and it is
printing detection results and debug log output on the VCOM serial port. In the
application configuration file called audio_classifier_config.h the user can
select which LED to use for activity and which LED to use for detection. By
default the detection LED is green/led1 and the activity LED is red/led0.

At a regular interval the application will perform an inference and the result
will be processed to find the average score for each class in the current
window. If the top result score is higher than a detection threshold then a
detection is triggered and the detection LED (green) will light up for about 750
ms.

Once the detection LED turns off the application goes back to responding to the
input data. If the change in model output is greater than a configurable
sensitivity threshold, then the activity LED (red) will blink for about 500 ms.

The activity LED indicates that audio has been detected on the input and the
model output is changing, but no clear classification was made.

In audio classification it is common to have some results that map to silence or
unknown. These results are something that we usually want to ignore. This is
being filtered out in the audio classifier application based on the label text.
By default any labels that start with an underscore are ignored when processing
results. This behavior can be disabled in the application configuration file.

## Model  
The default model used in this application is called "audio_classifier.tflite"
and is able to classify audio into 4 different classes labeled "on", "off",
"_unknown_", "_silence_". The source for the model can be found here: https://github.com/siliconlabs/mltk/blob/master/mltk/models/siliconlabs/keyword_spotting_on_off.py

The application is designed to work with an audio classification model created
using the Silicon Labs Machine Learning Toolkit
([MLTK](https://siliconlabs.github.io/mltk)). Use the MLTK to train a new audio
classifier model and replace the model inside this example with the new audio
classification model. To replace the audio classification model with a new model
created using the MLTK you can rename the new .tflite file to
"audio_classifier.tflite" and copy it into the config/tflite folder of this
project. After a new .tflite file is added to the project Simplicity Studio will
automatically use the [flatbuffer converter tool](https://docs.silabs.com/gecko-platform/latest/machine-learning/tensorflow/flatbuffer-conversion)
to convert a .tflite file into a c file which is added to the project.

In order for the audio classification to work correctly we need to use the same
audio feature generator configuration parameters for inference as is used when
training the model. When using the MLTK to train an audio classification model
the model parameters will be embedded in the metadata section of the .tflite
file. When generating a project this metadata is extracted by tools in the Gecko
SDK and placed in the file called sl_tflite_micro_model_parameters.h inside the
autogen folder of the example.

This example will automatically use the parameters from the .tflite file in
order to configure the audio feature generator to correctly extract features
from input audio data which can be passed to TensorFlow when doing inference.
See the MLTK documentation for more information about the model parameters:
https://siliconlabs.github.io/mltk/docs/model_parameters.html

## References

The example is based on TensorFlow's example called **[micro speech](https://github.com/tensorflow/tflite-micro/tree/main/tensorflow/lite/micro/examples/micro_speech)**
and audio is processed using the **[audio feature generator](https://docs.silabs.com/gecko-platform/latest/machine-learning/api/group-ml-audio-feature-generation)**.

- [Gecko SDK Machine Learning Documentation](https://docs.silabs.com/gecko-platform/latest/machine-learning/tensorflow/getting-started)
- [MLTK Documentation](https://siliconlabs.github.io/mltk)
- [TensorFlow Lite Micro](https://www.tensorflow.org/lite/microcontrollers)
