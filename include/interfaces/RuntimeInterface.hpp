#if !defined  _ELROND_RUNTIME_INTERFACE_HPP
#define _ELROND_RUNTIME_INTERFACE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interfaces {

            class RuntimeInterface {
                public:
                    virtual const elrond::interfaces::DebugOutInterface &dout() const =0;

                    virtual void onError(const char *error)=0;
            };
        }
    }

#endif
