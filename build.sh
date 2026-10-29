!#/bin/bash

cp "randombytes.h" "randombytes.c" "openthread/third_party/mbedtls/repo/3rdparty/mlkem/mlkem-native/mlkem/src"
./script/build nrf52840 USB_trans -DOT_BOOTLOADER=USB -DOT_COMMISSIONER=ON -DOT_JOINER=ON
arm-none-eabi-objcopy -O ihex build/bin/ot-cli-ftd ot-cli-ftd.hex
nrfutil nrf5sdk-tools pkg generate --hw-version 52 --sd-req 0x00 --application-version 1 --application ot-cli-ftd.hex app_dfu.zip
