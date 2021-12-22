#ifndef ELROND_PLATFORM_RUNTIME_TYPES_HPP
    #define ELROND_PLATFORM_RUNTIME_TYPES_HPP

    #include "elrond.hpp"

    #ifndef ELROND_STD_PLATFORM
        #error "This project is only compatible with STD platforms"
    #endif

    namespace elrond
    {
        namespace platform
        {
            std::string demangle(const std::type_info& info);

            template <class T>
            inline std::string demangle() { return demangle(typeid(T)); }
        }
    }

#endif