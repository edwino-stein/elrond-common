#ifndef ELROND_MOCK_TYPES_HPP
    #define ELROND_MOCK_TYPES_HPP

    #include <elrond.hpp>

    #ifndef ELROND_STD_PLATFORM
        #error "Mock project is only compatible with STD platforms"
    #endif

    #include <elrond_runtime.hpp>
    
    #include <sstream>
    #include <memory>
    #include <map>

    namespace elrond
    {
        namespace mock
        {
            class RuntimeCtx;
            class Console;
            class StringStream;
            class Parameters;
        }
    }

#endif
