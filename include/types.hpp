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
        using dword = ELROND_UINT32_TYPE;
        using dWord = ELROND_UINT32_TYPE;
        using sizeT = size_t;

        //Enums
        enum class ModuleType {
            GENERIC,
            TRANSPORT
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
            class ConfigMapMemoryInterface;
            class DebugOutInterface;
        }

        // Modules
        namespace modules {
            class BaseModule;
            class BaseTransportModule;
            class ExampleModule;
        }

        // Runtime
        class TaskContext;

        namespace config {
            class ConfigMap;
            class ConfigMapAllocator;
        }

        //Singleton instance of runtime application
        extern interfaces::RuntimeInterface *__rtInstance__;
        interfaces::RuntimeInterface &app();
        const interfaces::DebugOutInterface &dout();
        void error(const char *error);
    }

#endif
