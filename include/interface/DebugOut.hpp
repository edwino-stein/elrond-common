#if !defined  _ELROND_INTERFACE_DEBUG_OUT_HPP
#define _ELROND_INTERFACE_DEBUG_OUT_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace interface {

            class DebugOut {

                public:

                    virtual const elrond::interface::DebugOut& put(const char c[]) const =0;
                    virtual const elrond::interface::DebugOut& put(char c) const =0;
                    virtual const elrond::interface::DebugOut& put(unsigned char c) const =0;
                    virtual const elrond::interface::DebugOut& put(int i) const =0;
                    virtual const elrond::interface::DebugOut& put(unsigned int i) const =0;
                    virtual const elrond::interface::DebugOut& put(long l) const =0;
                    virtual const elrond::interface::DebugOut& put(unsigned long l) const =0;
                    virtual const elrond::interface::DebugOut& put(double d) const =0;

                    virtual const elrond::interface::DebugOut& putLn(const char c[]) const =0;
                    virtual const elrond::interface::DebugOut& putLn(char c) const =0;
                    virtual const elrond::interface::DebugOut& putLn(unsigned char c) const =0;
                    virtual const elrond::interface::DebugOut& putLn(int i) const =0;
                    virtual const elrond::interface::DebugOut& putLn(unsigned int i) const =0;
                    virtual const elrond::interface::DebugOut& putLn(long l) const =0;
                    virtual const elrond::interface::DebugOut& putLn(unsigned long l) const =0;
                    virtual const elrond::interface::DebugOut& putLn(double) const =0;
                    virtual const elrond::interface::DebugOut& putLn() const =0;

                    virtual const elrond::interface::DebugOut& flush() const =0;

                    #ifdef ELROND_WITH_STR_TYPE
                        virtual const elrond::interface::DebugOut& put(elrond::String str) const =0;
                        virtual const elrond::interface::DebugOut& putLn(elrond::String str) const =0;
                    #endif
            };
        }
    }

#endif
