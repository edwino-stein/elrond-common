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
            GENERIC
        };


        // Interfaces
        namespace interfaces {
            class RuntimeInterface;
            class ModuleInterface;
            class ConfigMapMemoryInterface;
        }

        //Singleton instance of runtime application
        extern interfaces::RuntimeInterface *__rtInstance__;
        interfaces::RuntimeInterface &app();
        void error(const char *error);
    }

#endif
