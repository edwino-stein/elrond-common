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
            class Stream;
        }

        namespace module
        {
            class Abstract;
            template<elrond::ModuleType M> class Base;
            class BaseGeneric;
        }

        // Handles
        using StreamH = elrond::procedure<elrond::interface::Stream&>;
    }

#endif
