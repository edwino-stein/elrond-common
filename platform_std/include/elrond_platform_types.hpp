#ifndef ELROND_PLATFORM_TYPES_HPP
    #define ELROND_PLATFORM_TYPES_HPP

    #include "elrond_platform_std.hpp"

    namespace elrond
    {
        // Scalar types
        using int8 = int8_t;
        using uInt8 = uint8_t;
        using int16 = int16_t;
        using uInt16 = uint16_t;
        using int32 = int32_t;
        using uInt32 = uint32_t;

        // Size and time types
        using sizeT = std::size_t;
        using timeT = uintmax_t;

        // Byte based types
        using byte = uint8_t;
        using word = uint16_t;
        using dWord = uint32_t;

        // String
        using string = std::string;
        
        // Lambda function
        template <class R, class...As>
        using function = std::function<R(As...)>;

        // Lambda procedure
        template <class...As>
        using procedure = std::function<void(As...)>;

        // Platform specific classes
        namespace platform
        {
            class Object;
            class ModuleObject;
        }
    }

#endif
