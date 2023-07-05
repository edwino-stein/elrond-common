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
                    //
                    // Special Members
                    //
                    ELROND_CLASS_SPECIAL_MEMBERS(Stream, =default, =delete, =default, =delete, =delete)

                    //
                    // Char and strings
                    //
                    virtual const elrond::interface::Stream&
                    operator<<(char c) const =0;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(unsigned char c) const =0;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(const char* c) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(elrond::string str) const =0;

                    //
                    // Numeric
                    //
                    virtual const elrond::interface::Stream&
                    operator<<(int i) const =0;
                    
                    virtual const elrond::interface::Stream&
                    operator<<(unsigned int i) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(long l) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(unsigned long l) const =0;

                    virtual const elrond::interface::Stream&
                    operator<<(double d) const =0;
            };
        }
    }

#endif
