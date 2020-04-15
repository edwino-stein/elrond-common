/*
    Copyright 2019 Edwino A. L. Stein

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#if !defined  _ELROND_HPP
    #define _ELROND_HPP

    // Interfaces
    #include "interface/Runtime.hpp"
    #include "interface/Module.hpp"
    #include "interface/ConfigMap.hpp"
    #include "interface/DebugOut.hpp"
    #include "interface/ChannelManager.hpp"

    // Base modules
    #include "module/BaseModule.hpp"
    #include "module/BaseTransportModule.hpp"
    #include "module/BaseGpioModule.hpp"
    #include "module/BaseInputDriverModule.hpp"

    // Modules
    #include "module/Example.hpp"
    #include "module/Loopback.hpp"
    #include "module/InputToChannel.hpp"
    #include "module/ChannelToChannel.hpp"
    #include "module/DigitalLed.hpp"
    #include "module/AnalogLed.hpp"
    #include "module/Servo.hpp"

    // Gpio
    #include "gpio/BaseGpioPin.hpp"
    #include "gpio/GenericGpioPin.ipp"

    // Channel
    #include "channel/BaseChannelManager.hpp"
    #include "channel/TxChannel.hpp"
    #include "channel/RxChannel.hpp"

    // Input
    #include "input/InputCallback.hpp"

#endif
