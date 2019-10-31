# Elrond Common Library

Open source framework for remotely controlled models and things, focusing on modularization and easy configuration with a declarative syntax.

The **Elrond Common Library** is the core of the Elrond Project. The **ECL** provides a API and an abstraction layer for Elrond Modules works on differents platforms without code modifications.

## Compatibility

The **Elrond Common Library** is currently compatible with these platforms:

 - Linux PCs and based boards (Raspberry Pi);
 - Arduino AVR boards (Nano, Uno, Mega);
 - ESP32 (with Arduino IDE);

## Library files
 - **build/libelrond.a**: Static library used to build the runtime application;
 - **build/libelrond.pic.o**: Bundle with all PIC (Position Independent Code) objects files (**.pic.o**) used to build Shared Objects (.so)  for linux compatible modules;
 - **dist/**: Output directory to base structure of Arduino library;

## Internal modules
The **Elrond Common Library**  includes some modules to general proposes.

### elrond::AnalogLed
This module maps a receiver channel to a PWM pin output. The module configuration are:
 - **channel** (int): number of receiver channel for input data;
 - **pin** (int): number of PWM pin to output;
 - **inverted** (bool)[default = false]: inverts the data signal. Eg. *HIGH* to *LOW* value and vice versa;
 - **chm** (int)[default = 0]: number of receive channel manager;

### elrond::DigitalLed
This module maps a receiver channel to a digital pin output. The module configuration are:
 - **channel** (int): number of receiver channel for input data;
 - **pin** (int): number of digital pin to output;
 - **inverted** (bool)[default = false]: inverts the data signal. Eg. *HIGH* to *LOW* value and vice versa;
 - **chm** (int)[default = 0]: number of receive channel manager;

### elrond::Servo
This module maps a receiver channel to a PWM servo mode pin output. The module configuration are:
 - **channel** (int): number of receiver channel for input data;
 - **pin** (int): number of PWM pin to output;
 - **inverted** (bool)[default = false]: inverts the data signal. Eg. *HIGH* to *LOW* value and vice versa;
 - **chm** (int)[default = 0]: number of receive channel manager;

### elrond::InputToChannel
This module maps an input key from an Input Driver Module to a transmitter channel. The module configuration are:
 - **channel** (int): number of transmitter channel for output data;
 - **input** (int): number of input key from Input Driver Module for input data;
 - **inverted** (bool)[default = false]: inverts the data signal. Eg. *HIGH* to *LOW* value and vice versa;
 - **chm** (int)[default = 0]: number of transmitter channel manager;
 - **ins** (int)[default = 0]: number of Input Driver Module;

### elrond::ChannelToChannel
This module maps a receiver channel to a transmitter channel. The module configuration are:
 - **txCh** (int): number of transmitter channel for output data;
 - **txChm** (int): number of transmitter channel manager;
 - **rxCh** (int): number of receiver channel for output data;
 - **rxChm** (int): number of receiver channel manager;
 - **inverted** (bool)[default = false]: inverts the data signal. Eg. *HIGH* to *LOW* value and vice versa;

### elrond::Loopback
This module just put back the transmit data as receive data. The module not require configuration.

### elrond::Example
This module is a simple example that just prints the life cycle. The module configuration are:
 - **allowLoop** (bool)[default = false]: enable or disable the module loop;
 - **asyncLoop** (bool)[default = false]: if compatible, enable or disable the module loop in a separate thread (Linux only)
 - **timeLoop** (int)[default = 100]: time interval in milliseconds between of the module loop executions;
