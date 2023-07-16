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
                    virtual elrond::interface::Stream& operator<<(char c) =0;
                    virtual elrond::interface::Stream& operator<<(unsigned char c) =0;
                    virtual elrond::interface::Stream& operator<<(const char* c) =0;
                    virtual elrond::interface::Stream& operator<<(elrond::string str) =0;

                    //
                    // Numeric
                    //
                    virtual elrond::interface::Stream& operator<<(int i) =0;
                    virtual elrond::interface::Stream& operator<<(unsigned int i) =0;
                    virtual elrond::interface::Stream& operator<<(long l) =0;
                    virtual elrond::interface::Stream& operator<<(unsigned long l) =0;
                    virtual elrond::interface::Stream& operator<<(double d) =0;
            };
        }
    }

#endif
