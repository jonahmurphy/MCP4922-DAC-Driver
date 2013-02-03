MCP4922-DAC-Driver
==================

Driver for the Dual Channel [12-bit MCP4922 SPI DAC] (http://ww1.microchip.com/downloads/en/devicedoc/21897a.pdf) from MicroChip

>The MCP4922 device is a dual channel 12-bit DAC which uses an external voltage reference.
>This device offers high accuracy and low power consumption, and is available in various packages. 
>Communication with the device is accomplished via a simple serial interface using SPI protocols.
>The MCP4922 device is a part of the MCP4902/MCP4912/MCP4922 product family, which are dualchannel 8-bit/10-bit/12-bit DACs which use external voltage reference (VREF).
>These devices provide very high accuracy and low noise performance, and are suitable for consumer and industrial applications, such as set point control,
>offset adjustment and sensor calibration applications.
>The low power consumption and small package options make these devices very attractive for many portable and battery-powered applications.
>If only a single output is needed then the MCP4901/4911/4921 single channel product family can be used.

Platform
--------

The driver was written for the 8051 platform using Keils C51 compiler, in particular testing was done on 
the [Atmel T89C51RD2 MCU](http://www.atmel.com/Images/doc4243.pdf).

Porting
-------

Most platform specific elements are abstracted in the included SPI Driver SPI.c/h.
Porting should be simply a case of replacing SPI.c/h with an SPI.c/h module with same interface.

#### Some non-portable Keil C51 specific elements will need to changed.

**1)**
The chip select pin is defined in `MCP4922_DAC_driver.h` using the non-portable `sbit` type.
`````````````````
/**Chip Select pin definition*/
sbit CS = P2^1;
``````````````````

**2)**
The `void SPI_init(bit, bit, bit, bit, unsigned char)`
function in `SPI.c/h` which in turn is called by `void MCP4922_init()` takes the C51 specific  `bit` type for a number of its arguments.
To make this portable the function needs to be changed so that it takes single char in place of these to pass these config bits.

Todo
----

Remove non-portable Keil C51 types from the `SPI.c/h` interface to make the MCP4922 Driver completly portable.


