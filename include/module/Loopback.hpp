#if !defined  _ELROND_LOOPBACK_MODULE_HPP
    #define _ELROND_LOOPBACK_MODULE_HPP

    #include "module/BaseTransportModule.hpp"

    namespace elrond {
        namespace module {

            class Loopback : public elrond::module::BaseTransportModule {

                protected:
                    elrond::interface::ChannelManager* cm = nullptr;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~Loopback();
                    #endif

                    void send(elrond::byte data[], const elrond::sizeT length) override;
                    void setChannelManager(elrond::interface::ChannelManager* cm) override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
