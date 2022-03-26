#ifndef ELROND_COMMON_INTERFACE_STREAM_HPP
    #define ELROND_COMMON_INTERFACE_STREAM_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Stream
            {
                public:

                    ELROND_OPT_DFLT_VDESTRUCTOR(Stream);

                    //
                    // Char and strings
                    //
                    virtual const elrond::interface::Stream&
                    operator<<(const char c) const =0;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const unsigned char c) const =0;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const char c[]) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(elrond::string str) const =0;

                    //
                    // Numeric
                    //
                    virtual const elrond::interface::Stream&
                    operator<<(const int i) const =0;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const unsigned int i) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(const long l) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(const unsigned long l) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(const double d) const =0;
            };
        }
    }

#endif
