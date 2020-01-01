#if !defined  _ELROND_COMMON_TYPES_HPP
#define _ELROND_COMMON_TYPES_HPP

    #include "platform.hpp"

    namespace elrond {

        // Scalar types
        using int16 = ELROND_INT16_TYPE;
        using uInt16 = ELROND_UINT16_TYPE;
        using int32 = ELROND_INT32_TYPE;
        using uInt32 = ELROND_UINT32_TYPE;

        using byte = ELROND_UINT8_TYPE;
        using word = ELROND_UINT16_TYPE;
        using dWord = ELROND_UINT32_TYPE;
        using sizeT = size_t;

        //Enums
        enum class ModuleType {
            GENERIC,
            TRANSPORT,
            GPIO,
            INPUT
        };

        enum class GpioType {
            UNKNOWN,
            DOUT,
            AIN,
            PWM,
            SERVO
        };

        // Structs
        struct ModuleLoopControl {
            bool allow = true;
            bool async = false;
            unsigned int time = 0;
        };

        // Interfaces
        namespace interfaces {
            class RuntimeInterface;
            class ModuleInterface;
            class ConfigMapInterface;
            class DebugOutInterface;
        }

        // Modules
        namespace modules {
            class BaseModule;
            class BaseTransportModule;
            class BaseGpioModule;
            class BaseInputDriverModule;
            class Example;
            class Loopback;
            class InputToChannel;
            class ChannelToChannel;
            class DigitalLed;
            class AnalogLed;
            class Servo;
        }

        // Runtime
        class TaskContext;

        namespace gpio {
            class BaseGpioPin;
            template<class T, elrond::GpioType G> class GenericGpioPin;
            using gpioReadHandleT = elrond::word(*)(elrond::gpio::BaseGpioPin &pin);
            using gpioWriteHandleT = void (*)(elrond::gpio::BaseGpioPin &pin, elrond::word &data);
            using DOutPin = GenericGpioPin<ELROND_GPIO_DIO_TYPE, elrond::GpioType::DOUT>;
            using AinPin = GenericGpioPin<ELROND_GPIO_AIO_TYPE, elrond::GpioType::AIN>;
            using ServoPin = GenericGpioPin<ELROND_GPIO_SERVO_TYPE, elrond::GpioType::SERVO>;
            using PwmPin = GenericGpioPin<ELROND_GPIO_PWM_TYPE, elrond::GpioType::PWM>;
        }

        namespace channel {
            using onReceiveT = void (*)(elrond::word, elrond::TaskContext *);
            class BaseChannelManager;
            class TxChannel;
            class RxChannel;
        }

        namespace input {
            using onInputT = void (*)(elrond::word, elrond::TaskContext *);
            class InputCallback;
        }

        //Singleton instance of runtime application
        extern interfaces::RuntimeInterface *__rtInstance__;
        interfaces::RuntimeInterface &app();
        const interfaces::DebugOutInterface &dout();
        void error(const char *error);
        #if defined INO_PLATFORM
            void error(const __FlashStringHelper *error);
        #endif

        //Internal modules
        using Example = elrond::modules::Example;
        using Loopback = elrond::modules::Loopback;
        using InputToChannel = elrond::modules::InputToChannel;
        using ChannelToChannel = elrond::modules::ChannelToChannel;
        using DigitalLed = elrond::modules::DigitalLed;
        using AnalogLed = elrond::modules::AnalogLed;
        using Servo = elrond::modules::Servo;
    }

#endif
