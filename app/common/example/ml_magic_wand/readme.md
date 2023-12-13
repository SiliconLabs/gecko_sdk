# Magic Wand
This application demonstrates a model trained to recognize various hand gestures
with an accelerometer. The detected gestures are printed to the serial port.

With the board facing up, and the USB cable pointed towards you, you should be
able to perform one of the three gestures: Wing (*W*), Ring (*O*), or Slope
(*L*) and have them correctly detected and output to the serial port. The LEDs
light up to indicate a detected gesture.

When the application is running the IMU sensor is sampled at 25 Hz to read out
x,y,z acceleration values. The samples are buffered and the application
periodically performs inference using a TensorFlow Lite Micro model with the
90 latest samples. The machine learning model is a CNN that treats the
accelerometer data as a picture and recognizes patterns. Use Netron or similar
tools to see the full model architecture.
