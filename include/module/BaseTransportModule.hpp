#if !defined  _ELROND_BASE_TRANSPORT_MODULE_HPP
    #define _ELROND_BASE_TRANSPORT_MODULE_HPP

    #include "module/BaseModule.hpp"

    namespace elrond {
        namespace module {

            class BaseTransportModule : public elrond::module::BaseModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseTransportModule();
                    #endif

                    virtual void send(elrond::byte data[], const elrond::sizeT length)=0;
                    virtual void setChannelManager(elrond::interface::ChannelManager* cm)=0;
                    virtual elrond::ModuleType getType() const override;
            };
        }
    }

#endif
