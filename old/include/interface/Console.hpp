#if !defined  _ELROND_INTERFACE_CONSOLE_HPP
#define _ELROND_INTERFACE_CONSOLE_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace interface {

            class Console {

                public:

                    // Char and strings
                    virtual const elrond::interface::Console& operator<<(const char c) const =0;
                    virtual const elrond::interface::Console& operator<<(const unsigned char c) const =0;
                    virtual const elrond::interface::Console& operator<<(const char c[]) const =0;
                    #ifdef ELROND_WITH_STR_TYPE
                        virtual const elrond::interface::Console& operator<<(elrond::String str) const =0;
                    #endif

                    // Numeric
                    virtual const elrond::interface::Console& operator<<(const int i) const =0;
                    virtual const elrond::interface::Console& operator<<(const unsigned int i) const =0;
                    virtual const elrond::interface::Console& operator<<(const long l) const =0;
                    virtual const elrond::interface::Console& operator<<(const unsigned long l) const =0;
                    virtual const elrond::interface::Console& operator<<(const double d) const =0;

                    // Others
                    virtual const elrond::interface::Console& operator<<(elrond::ConsoleCallbackT cb) const =0;
                    virtual const elrond::interface::Console& endl() const =0;
            };
        }
    }

#endif
