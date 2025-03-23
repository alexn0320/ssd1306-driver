* A basic driver for SSD1306 based monochrome OLEDs of various sizes, supporting for now only the RP2040 chip from the Raspiberry Pi Pico. 
* Communication is done using I2C, in this case using the Pico SDK that implements the necessary I2C functions.
* A debug system was implemented using UART.

[Pico SDK](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)\
[SSD1306 datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)

## Usage
* You need the Pico SDK to be installed on the system.
* Modify the CMakeLists.txt `set(PICO_SDK_PATH {PATH})` line so that `{PATH}` is the Pico SDK path.  

```
https://github.com/alexn0320/ssd1306-driver
cd ssd1306-driver
mkdir build
cd build
cmake ..
make
```
