#ifndef ELROND_COMMON_INTERFACE_CONSOLE_HPP
    #define ELROND_COMMON_INTERFACE_CONSOLE_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Console
            {
                public:
                    
                    ELROND_OPT_DFLT_VDESTRUCTOR(Console);

                    //
                    // Stream directly
                    //
                    virtual const elrond::platform::ConsoleStream info() const =0;
                    virtual const elrond::platform::ConsoleStream error() const =0;

                    //
                    // Char and strings
                    //
                    virtual void info(const char c) const =0;
                    virtual void info(const unsigned char c) const =0;
                    virtual void info(const char c[]) const =0;
                    virtual void info(elrond::string str) const =0;
                    virtual void error(const char c[]) const =0;
                    virtual void error(elrond::string str) const =0;

                    //
                    // Numeric
                    //
                    virtual void info(const int i) const =0;
                    virtual void info(const unsigned int i) const =0;
                    virtual void info(const long l) const =0;
                    virtual void info(const unsigned long l) const =0;
                    virtual void info(const double d) const =0;
            };
        }
    }

#endif
