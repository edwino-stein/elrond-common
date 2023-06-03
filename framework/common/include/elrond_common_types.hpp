#ifndef ELROND_COMMON_TYPES_HPP
    #define ELROND_COMMON_TYPES_HPP

    #include "elrond_platform_types.hpp"
    #include "enum/ModuleType.hpp"
    #include "enum/TimeUnit.hpp"

    namespace elrond
    {
        struct TimeSpan
        {
            elrond::timeT count;
            elrond::TimeUnit unit;
        };

        constexpr elrond::byte MAJOR_VER  = ELROND_API_MAJOR;
        constexpr elrond::byte MINOR_VER  = ELROND_API_MINOR;
        constexpr elrond::byte PATCH_VER  = ELROND_API_PATCH;
        constexpr elrond::byte BUILD_TYPE = ELROND_BUILD_TYPE | ELROND_API_DEV_STAGE;

        constexpr elrond::dWord getApiVersion()
        {
            return static_cast<elrond::dWord>(BUILD_TYPE) << 24 | 
                   static_cast<elrond::dWord>(MAJOR_VER)  << 16 |
                   static_cast<elrond::dWord>(MINOR_VER)  <<  8 | 
                   static_cast<elrond::dWord>(PATCH_VER);
        }

        namespace interface
        {
            class Module;
            class Context;
            class Console;
            class Stream;
            class Arguments;
        }

        namespace module
        {
            class Abstract;
            template<elrond::ModuleType M> class Base;
            class BaseGeneric;
        }

        // Handles
        using StreamH = elrond::procedure<elrond::interface::Stream&>;
        
        // Type alies
        using Stream = elrond::interface::Stream;
        using ContextP = elrond::pointer<elrond::interface::Context>;
    }

#endif
