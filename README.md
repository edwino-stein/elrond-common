# Elrond Common Library (outdated/working in progress)

<p align="right" >
 <a href="https://github.com/edwino-stein/elrond-common/releases">
   <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/edwino-stein/elrond-common?include_prereleases">
 </a>
 <img src="https://github.com/edwino-stein/elrond-common/workflows/Build%20and%20test/badge.svg" />

</p>

Open source framework for remotely controlled models, focusing on modularization and easy configuration with a declarative syntax.

The **Elrond Common Library** is the core of the Elrond Project. The **ECL** provides an API and an abstraction layer for Elrond Modules that work on differents platforms without code modifications.

## Modularization

An application based on **Elrond** will be constitued by module instances. Every instance must work in a single task, like blinking a simple LED, or even transferring data between the peers using a complex network protocol. Instances do not interact with each other directly, and can be one of following base types:


 - `elrond::module::BaseModule`: Generic type to general proposes. Does not impose rules be used, or methods to be implemented;
 - `elrond::module::BaseGpioModule`: Specifies the implementation of the GPIO abstraction layer, therefore, every platform must have its own implementation of this class if the other modules are to have access to the GPIO header;
 - `elrond::module::BaseInputDriverModule`: Base to implement a input driver, responsible for read input data from a periferal, like a joystick;
 - `elrond::module::BaseTransportModule`: This base must be used to implement a transport module that abstracts for a network protocol, that during runtime, will be used by a channel manager to transmit and receive data;

The **ECL** provides some internal modules, see [internal modules](#internal-modules) section.

## Channels based model

Like typical electronic radio controllers, the communication between the **Elrond**-based peers is mapped into channels. A channel is basically a control signal that performs an action in another peer. The main advantage of **Elrond** is that the data link must be at least half-duplex, and can technically handle a lot more channels, and can be flexible because of software processing. Another advantage is that it is not limited by radio technologies – basically, it can be implemented on any half-duplex or full-duplex digital data stream tecnology.

The channels are managed by a **channel manager**, and they can be of the transmitter type (**tx channel**) or receiver type (**rx channel**). The data sent by a transmitter channel will be received by an equivalent receiver channel in another peer. A channel can be triggered by or listened to many module instances, and a module instance can trigger or listen to many channels. An application can have many channel managers, each one with its own transport module.

## Compatibility

The **Elrond Common Library** is currently compatible with these platforms:

 - Linux PCs and based boards (eg. Raspberry Pi);


## Library files

 - `build/libelrond.a`: Static library that contains elrond's common classes to runtime environment and test environment on linux platform;
 - `build/libelrond_ext.a`: Static library that contains elrond's extended classes to runtime environment and test environment on linux platform;
 - `dist/elrond.hpp`: Header only library with common classes and basic code to external modules implementation. No library linkage required;
 - `dist/elrond_ext.hpp`: Extended library that contains elrond's extended classes headers. Must be combined with `elrond_test.hpp` and linked with `libelrond_ext.a` to testing and validating external modules;
 - `dist/elrond_test.hpp`: Test library that contains `elrond::test` classes headers. Must be linked with `libelrond_ext.a`;

## Internal modules
The **Elrond Common Library** includes some general proposes modules.

> The pattern of parameter list is: **`<name>`**[`<type>`, `<default>`]: `<description>`.<br/>
> If `<default>` is missing, the parameter value is required.

### `elrond::AnalogLed`
This module maps a **receiver channel** to a **PWM pin** output. The module parameters are:

 - **`channel`** [`int`]: number of **receiver channel** for input data;
 - **`pin`** [`int`]: number of **PWM pin** to output;
 - **`inverted`** [`bool`, `false`]: inverts the data signal. Eg. `HIGH` to `LOW` value and vice versa;
 - **`chm`** [`int`, `0`]: number of receiver **channel manager**;

### `elrond::DigitalLed`
This module maps a **receiver channel** to a **digital pin** output. The module parameters are:

 - **`channel`** [`int`]: number of **receiver channel** for input data;
 - **`pin`** [`int`]: number of **digital pin** to output;
 - **`inverted`** [`bool`, `false`]: inverts the data signal. Eg. `HIGH` to `LOW` value and vice versa;
 - **`chm`** [`int`, `0`]: number of receiver **channel manager**;

### `elrond::Servo`
This module maps a **receiver channel** to a **PWM pin** output setted in **servo mode**. The module parameters are:

 - **`channel`** [`int`]: number of **receiver channel** for input data;
 - **`pin`** [`int`]: number of **servo pin** to output;
 - **`inverted`** [`bool`, `false`]: inverts the data signal. Eg. `HIGH` to `LOW` value and vice versa;
 - **`chm`** [`int`, `0`]: number of receiver **channel manager**;

### `elrond::InputToChannel`
This module maps an input key from an **Input Driver Module** to a **transmitter channel**. The module parameters are:

 - **`channel`** [`int`]: number of **transmitter channel** for output data;
 - **`input`** [`int`]: number of input key from **Input Driver Module** for input data;
 - **`inverted`** [`bool`, `false`]: inverts the data signal. Eg. `HIGH` to `LOW` value and vice versa;
 - **`chm`** [`int`, `0`]: number of transmitter **channel manager**;
 - **`ins`** [`int`, `0`]: number of **Input Driver Module**;

### `elrond::ChannelToChannel`
This module maps a **receiver channel** to a **transmitter channel**. The module parameters are:

 - **`txCh`** [`int`]: number of **transmitter channel** for output data;
 - **`txChm`** [`int`]: number of transmitter **channel manager**;
 - **`rxCh`** [`int`]: number of **receiver channel** for output data;
 - **`rxChm`** [`int`]: number of receiver **channel manager**;
 - **`inverted`** [`bool`, `false`]: inverts the data signal. Eg. `HIGH` to `LOW` value and vice versa;

### `elrond::Loopback`
This is a simple transport module, that sends the data back to the local **channel manager** as received data. No parameters required.

### `elrond::Example`
This module is a simple example module that just prints the life cycle hooks. The module parameters are:

 - **`loop`** [`bool`, `false`]: enable or disable the module's loop;
 - **`thread`** [`bool`, `false`]: if compatible, enable or disable the module's loop invocations into a separate thread;
 - **`interval`** [`int`, `100`]: time interval in milliseconds between module's loop invocations;
