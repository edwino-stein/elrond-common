#ifndef ELROND_PLATFORM_INTERFACE_CONSOLE_ADAPTER_HPP
    #define ELROND_PLATFORM_INTERFACE_CONSOLE_ADAPTER_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class ConsoleAdapter
            {
                public:
                    enum SEVERITY
                    {
                        INFO,
                        ERROR
                    };

                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(ConsoleAdapter)
                    virtual void preAppend(elrond::interface::Stream& stream, const elrond::string& tag, SEVERITY severity) const =0;
                    virtual void postAppend(elrond::interface::Stream& stream, const elrond::string& tag, SEVERITY severity) const =0;
                    virtual elrond::pointer<elrond::interface::Stream> makeStream() const =0;
            };
        }
    }

#endif
