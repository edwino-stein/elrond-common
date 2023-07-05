#ifndef ELROND_PLATFORM_BASE_INTERFACE_STREAM_ADAPTER_HPP
    #define ELROND_PLATFORM_BASE_INTERFACE_STREAM_ADAPTER_HPP

    #include "interface/Stream.hpp"

    namespace elrond
    {
        namespace interface
        {
            class StreamAdapter
            {
                public:
                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(StreamAdapter)
                    virtual const elrond::interface::Stream& stream() const=0;
                    virtual void preAppend() const =0;
                    virtual void postAppend() const =0;
            };
        }
    }

#endif
