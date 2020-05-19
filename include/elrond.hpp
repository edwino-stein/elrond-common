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

    // Runtime functions
    #include "runtime/bitwise.hpp"
    #include "runtime/time.hpp"
    #include "runtime/math.ipp"

    // Interfaces
    #include "interface/ConfigMap.hpp"
    #include "interface/DebugOut.hpp"
    #include "interface/Runtime.hpp"
    #include "interface/Module.hpp"
    #include "interface/ChannelManager.hpp"

    // Base modules
    #include "module/BaseModule.hpp"
    #include "module/BaseDataLinkModule.hpp"
    #include "module/BaseGpioModule.hpp"
    #include "module/BaseInputDriverModule.hpp"

    // Gpio
    #include "gpio/BaseGpioPin.hpp"
    #include "gpio/GpioPin.ipp"

    // Channel
    #include "channel/BaseChannel.hpp"
    #include "channel/TxChannel.hpp"
    #include "channel/RxChannel.hpp"

    // Input
    #include "input/InputListener.hpp"

#endif
