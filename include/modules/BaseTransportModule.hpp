#if !defined  _ELROND_BASE_TRANSPORT_MODULE_HPP
    #define _ELROND_BASE_TRANSPORT_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"

    namespace elrond {
        namespace modules {

            class BaseTransportModule : public elrond::modules::BaseModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseTransportModule();
                    #endif

                    virtual void send(elrond::byte data[], const elrond::sizeT length)=0;
                    virtual void setChannelManager(elrond::channel::BaseChannelManager *cm)=0;
                    virtual elrond::ModuleType getType() const override;
            };
        }
    }

#endif
