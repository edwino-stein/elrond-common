#ifndef ELROND_COMMON_TYPES_HPP
    #define ELROND_COMMON_TYPES_HPP

    #include "elrond_platform_types.hpp"
    #include "enum/ModuleType.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Module;
            class Context;
            class Console;
            class Stream;
            class Parameters;
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
        using Parameters = elrond::interface::Parameters;
    }

#endif
