cmake_minimum_required(VERSION 3.13...3.27)
set(PICO_SDK_PATH /home/alex/pico-sdk)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(oled)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(oled
        main.c ssd1306.c
        )

# pull in common dependencies
target_link_libraries(oled pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(oled)
