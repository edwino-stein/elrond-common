#if !defined  _ELROND_COMMON_TYPES_HPP
#define _ELROND_COMMON_TYPES_HPP

    #include "elrond_platform.hpp"

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
            DATA_LINK,
            GPIO,
            INPUT
        };

        enum class GpioType {
            UNKNOWN,
            DOUT,
            DIN_PD,
            DIN_PU,
            AIN,
            PWM,
            SERVO
        };

        // Structs
        struct LoopControl {
            bool enable = false;
            bool ownThread = false;
            elrond::timeT interval = 0;
        };

        // Constants
        constexpr word high = ELROND_HIGH_VALUE;
        constexpr word low = ELROND_LOW_VALUE;

        // Interfaces
        namespace interface {
            class Runtime;
            class Module;
            class ChannelManager;
            class ConfigMap;
            class DebugOut;
        }

        // Modules
        namespace module {
            class BaseModule;
            class BaseDataLinkModule;
            class BaseGpioModule;
            class BaseInputModule;
        }

        // Others
        class TaskContext;

        // GPIO
        namespace gpio {
            class BaseGpioPin;
            template <elrond::GpioType G> class GpioPin;
            using DOutPin = GpioPin<elrond::GpioType::DOUT>;
            using DInPDPin = GpioPin<elrond::GpioType::DIN_PD>;
            using DInPUPin = GpioPin<elrond::GpioType::DIN_PU>;
            using AInPin = GpioPin<elrond::GpioType::AIN>;
            using ServoPin = GpioPin<elrond::GpioType::SERVO>;
            using PwmPin = GpioPin<elrond::GpioType::PWM>;
        }

        // Channel
        namespace channel {
            using OnReceiveHandleT = ELROND_LAMBDA_FUNC(void, const elrond::word, elrond::TaskContext* const);
            using OnChmReceiveHandleT = ELROND_LAMBDA_FUNC(elrond::sizeT, elrond::byte*, const elrond::sizeT, elrond::TaskContext* const);
            class BaseChannel;
            class TxChannel;
            class RxChannel;
        }

        // Input
        namespace input {
            class InputListener;
            using OnInputHandleT = ELROND_LAMBDA_FUNC(void, const elrond::word, elrond::TaskContext* const);
        }

        // Singleton instance of runtime application
        extern ELROND_MOD_INFO_APP_P ELROND_MOD_APP_VAR_N;
        interface::Runtime& app();
        const interface::DebugOut& dout();
        void error(const char* error);
        #ifdef ELROND_WITH_STR_TYPE
            void error(elrond::String error);
        #endif

        #ifndef ELROND_TASK_CONTEXT
            #define ELRONND_TASK_CONTEXT
            class TaskContext {};
        #endif
    }

    // Runtime functions
    #include "runtime/bitwise.hpp"
    #include "runtime/time.hpp"
    #include "runtime/math.ipp"

#endif
