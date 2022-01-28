#!/bin/bash

BOOTLOADER=$1
APPLICATION=$2
SERIES=$3
SDK=$4

SIGN_KEY=${SDK}/protocol/z-wave/BootLoader/sample-keys/sample_sign.key
ENCR_KEY=${SDK}/protocol/z-wave/BootLoader/sample-keys/sample_encrypt.key
if [[ "$SERIES" == "1" ]]; then
    COMPRESSION="lz4"
fi

if [[ "$SERIES" == "2" ]]; then
    COMPRESSION="lzma"
fi

echo "Generating gbl file"
commander gbl create ${APPLICATION}.gbl --app ${APPLICATION}.hex --sign ${SIGN_KEY} --encrypt ${ENCR_KEY} --compress ${COMPRESSION}
RET=$?
if [ $RET -ne 0 ]; then
    exit $RET
fi

# Check if make-v255-elf.py exists
if [[ -e "${SDK}/protocol/z-wave/DevTools/make-v255-elf.py" ]]
then
    echo "Making v255 hex and gbl file"
    python ${SDK}/protocol/z-wave/DevTools/make-v255-elf.py ${APPLICATION}.out ${APPLICATION}_v255.out
    RET=$?
    if [ $RET -ne 0 ]; then
        exit $RET
    fi

    ${ARM_GCC_DIR}/bin/arm-none-eabi-objcopy -O ihex ${APPLICATION}_v255.out ${APPLICATION}_v255.hex
    RET=$?
    if [ $RET -ne 0 ]; then
        exit $RET
    fi

    commander gbl create ${APPLICATION}_v255.gbl --app ${APPLICATION}_v255.hex --sign ${SIGN_KEY} --encrypt ${ENCR_KEY} --compress ${COMPRESSION}
    RET=$?
    if [ $RET -ne 0 ]; then
        exit $RET
    fi
fi

# Merge is only done for series 2 devices
if [[ "$SERIES" == "2" ]]; then
    echo "Combining bootloader and application into one file"
    commander convert $BOOTLOADER $APPLICATION.hex --outfile $APPLICATION.hex
    RET=$?
    if [ $RET -ne 0 ]; then
        exit $RET
    fi
fi

# Generate size report
echo "Generating size report"
${ARM_GCC_DIR}/bin/arm-none-eabi-size -A -x ${APPLICATION}.out > ${APPLICATION}_size.txt
RET=$?
if [ $RET -ne 0 ]; then
    exit $RET
fi

python $SDK/protocol/z-wave/DevTools/size_info_gen.py -i ${APPLICATION}_size.txt
RET=$?
if [ $RET -ne 0 ]; then
    exit $RET
fi

exit 0

# EOF
