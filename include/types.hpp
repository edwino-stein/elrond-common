#if !defined  _ELROND_COMMON_TYPES_HPP
#define _ELROND_COMMON_TYPES_HPP

    #include "platform.hpp"

    namespace elrond {

        // Scalar types
        using int8 = ELROND_INT8_TYPE;
        using uInt8 = ELROND_UINT8_TYPE;
        using int16 = ELROND_INT16_TYPE;
        using uInt16 = ELROND_UINT16_TYPE;
        using int32 = ELROND_INT32_TYPE;
        using uInt32 = ELROND_UINT32_TYPE;

        using sizeT = ELROND_SIZE_TYPE;
        using timeT = ELROND_TIME_TYPE;

        using byte = ELROND_UINT8_TYPE;
        using word = ELROND_UINT16_TYPE;
        using dWord = ELROND_UINT32_TYPE;

        #ifdef ELROND_WITH_STR_TYPE
            using String = ELROND_STR_TYPE;
        #endif

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
        namespace interface {
            class Runtime;
            class Module;
            class ConfigMap;
            class DebugOut;
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

        // Others
        class TaskContext;

        namespace gpio {
            class BaseGpioPin;
            using ReadHandleT = ELROND_LAMBDA_FUNC(elrond::word, elrond::gpio::BaseGpioPin&);
            using WriteHandleT = ELROND_LAMBDA_FUNC(void, elrond::gpio::BaseGpioPin&, const elrond::word);
            template <class T, elrond::GpioType G> class GenericGpioPin;
            using DOutPin = GenericGpioPin<ELROND_GPIO_DIO_TYPE, elrond::GpioType::DOUT>;
            using AInPin = GenericGpioPin<ELROND_GPIO_AIO_TYPE, elrond::GpioType::AIN>;
            using ServoPin = GenericGpioPin<ELROND_GPIO_SERVO_TYPE, elrond::GpioType::SERVO>;
            using PwmPin = GenericGpioPin<ELROND_GPIO_PWM_TYPE, elrond::GpioType::PWM>;
        }

        namespace channel {
            using OnReceiveHandleT = ELROND_LAMBDA_FUNC(void, const elrond::word, elrond::TaskContext* const);
            class BaseChannelManager;
            class TxChannel;
            class RxChannel;
        }

        namespace input {
            class InputCallback;
            using OnInputHandleT = ELROND_LAMBDA_FUNC(void, const elrond::word, elrond::TaskContext* const);
        }

        //Singleton instance of runtime application
        extern interface::Runtime* __rtInstance__;
        interface::Runtime& app();
        const interface::DebugOut& dout();
        void error(const char* error);
        #ifdef ELROND_WITH_STR_TYPE
            void error(elrond::String error);
        #endif

        //Internal modules
        using Example = elrond::modules::Example;
        using Loopback = elrond::modules::Loopback;
        using InputToChannel = elrond::modules::InputToChannel;
        using ChannelToChannel = elrond::modules::ChannelToChannel;
        using DigitalLed = elrond::modules::DigitalLed;
        using AnalogLed = elrond::modules::AnalogLed;
        using Servo = elrond::modules::Servo;

        #ifndef ELROND_TASK_CONTEXT
            #define ELRONND_TASK_CONTEXT
            class TaskContext {};
        #endif
    }

#endif
