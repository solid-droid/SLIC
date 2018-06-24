# SLIC (Single Line Independent Communication Protocol)

__Reasons to build:__
- unavailability of single wire based communication for general microcontrollers.
- unavailability of purely software based communication protocols. i.e, with just GPIO pins and no dedicated hardware.

SLIC is a communication protocol.

__Features:__
- Single line/wire
  - The protocol uses just 1 GPIO port for both transmission and reception.
- Hardware independent
  - The protocol is purely software based. Therefore you only need a GPIO port.
- Half duplex
  - The same GPIO pin is used for transmission and reception.
- Multiple Nodes
  - The single wire can be used to interface multiple devices like an I2C.
  - ( if current output is not satisfactory just use an external signal amplifier)
  - __The current library version doesent have this as an inbuilt function__

__Basic Setup Instructions__
- Interconnect the configured pin from both the microcontrollers.
- Use a PULLDOWN resister.

__Supported Hardware__
- The library is for Arduino IDE, hence any device which can be programed using the IDE is theoratically functional.
- Arduino UNO(16MHZ) - Arduino UNO(16MHZ) _Success_
- Arduino UNO(16MHZ) - Arduino NANO(16MHZ) _Success_ 


__Possible Uses__
- Communication protocol for cheep microcontrollers with no hardware communication support.
- Communication protocol for microcontrollers with limited number of available GPIO ports.
- IOT based applications where many wired connections are required.

