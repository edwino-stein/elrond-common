#if !defined  _ELROND_INTERFACE_RUNTIME_HPP
#define _ELROND_INTERFACE_RUNTIME_HPP

    #include "elrond_types.hpp"

    namespace elrond {
        namespace interface {

            class Runtime {

                public:

                    virtual elrond::module::BaseGpioModule& getGpio() const =0;
                    virtual elrond::module::BaseInputModule& getInput(const elrond::sizeT id = 0) const =0;
                    virtual elrond::interface::ChannelManager& getChannelManager(const elrond::sizeT id = 0) const =0;
                    virtual const elrond::interface::DebugOut& dout() const =0;

                    virtual void onError(const char* error)=0;
                    #ifdef ELROND_WITH_STR_TYPE
                        virtual void onError(elrond::String error)=0;
                    #endif
            };
        }
    }

#endif
