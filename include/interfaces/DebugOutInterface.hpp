#if !defined  _ELROND_RUNTIME_DEBUG_OUT_INTERFACE_HPP
#define _ELROND_RUNTIME_DEBUG_OUT_INTERFACE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interfaces {

            class DebugOutInterface {

                public:

                    virtual const elrond::interfaces::DebugOutInterface& put(const char c[]) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(char c) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(unsigned char c) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(int i) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(unsigned int i) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(long l) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(unsigned long l) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& put(double d) const =0;

                    virtual const elrond::interfaces::DebugOutInterface& putLn(const char c[]) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(char c) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(unsigned char c) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(int i) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(unsigned int i) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(long l) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(unsigned long l) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn(double) const =0;
                    virtual const elrond::interfaces::DebugOutInterface& putLn() const =0;

                    virtual const elrond::interfaces::DebugOutInterface& flush() const =0;

                    #ifdef ELROND_WITH_STR_TYPE
                        virtual const elrond::interfaces::DebugOutInterface& put(elrond::String str) const =0;
                        virtual const elrond::interfaces::DebugOutInterface& putLn(elrond::String str) const =0;
                    #endif
            };
        }
    }

#endif
