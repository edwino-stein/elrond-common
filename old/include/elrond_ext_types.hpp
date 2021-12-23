#if !defined  _ELROND_EXTENDED_TYPES_HPP
#define _ELROND_EXTENDED_TYPES_HPP

    #include "elrond.hpp"

    namespace elrond {

        // Modules
        namespace module {
            class BaseExternalModuleHandle;
            class Example;
            class Loopback;
            class InputToChannel;
            class ChannelToChannel;
            class DigitalLed;
            class AnalogLed;
            class Servo;
        }

        // Channel
        namespace channel {
            class BufferWrapper;
            class BaseChannelManager;
        }

        //Internal modules
        using Example = elrond::module::Example;
        using Loopback = elrond::module::Loopback;
        using InputToChannel = elrond::module::InputToChannel;
        using ChannelToChannel = elrond::module::ChannelToChannel;
        using DigitalLed = elrond::module::DigitalLed;
        using AnalogLed = elrond::module::AnalogLed;
        using Servo = elrond::module::Servo;
    }

#endif
