#ifndef ELROND_PLATFORM_INTERFACE_CONSOLE_STREAM_ADAPTER_HPP
    #define ELROND_PLATFORM_INTERFACE_CONSOLE_STREAM_ADAPTER_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class ConsoleStreamAdapter
            {
                public:
                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(ConsoleStreamAdapter)
                    virtual void preAppend(elrond::SEVERITY severity) =0;
                    virtual void postAppend(elrond::SEVERITY severity) =0;
                    virtual elrond::interface::Stream& stream() const =0;
            };
        }
    }

#endif
