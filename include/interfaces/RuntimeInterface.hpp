#if !defined  _ELROND_RUNTIME_INTERFACE_HPP
#define _ELROND_RUNTIME_INTERFACE_HPP

    #include "types.hpp"

    namespace elrond {
        namespace interfaces {

            class RuntimeInterface {

                public:

                    virtual elrond::modules::BaseGpioModule &getGpioService() const =0;
                    virtual elrond::modules::BaseInputDriverModule &getInputService(const elrond::sizeT id = 0) const =0;
                    virtual elrond::channel::BaseChannelManager &getChannelManager(const elrond::sizeT id = 0) const =0;
                    virtual const elrond::interfaces::DebugOutInterface &dout() const =0;

                    virtual void onError(const char *error)=0;
                    #ifdef ELROND_WITH_STR_TYPE
                        virtual void onError(elrond::String error)=0;
                    #endif
            };
        }
    }

#endif
