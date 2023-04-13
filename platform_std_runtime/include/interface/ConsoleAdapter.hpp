#ifndef ELROND_PLATFORM_RUNTIME_INTERFACE_CONSOLE_ADAPTER_HPP
    #define ELROND_PLATFORM_RUNTIME_INTERFACE_CONSOLE_ADAPTER_HPP

    #include "elrond_platform_runtime_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class ConsoleAdapter
            {
                public:
                    virtual ~ConsoleAdapter() = default;
                    virtual elrond::pointer<elrond::interface::StreamAdapter> getInfoStreamAdapter() const =0;
                    virtual elrond::pointer<elrond::interface::StreamAdapter> getErrorStreamAdapter() const =0;
            };
        }
    }

#endif
