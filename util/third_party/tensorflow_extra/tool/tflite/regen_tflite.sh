#!/usr/bin/bash

D="$(dirname $0)"
flatc --python ${D}/../../../tflite-micro/tensorflow/lite/schema/schema.fbs
