#if !defined  _ELROND_CHANNEL_TO_CHANNEL_MODULE_HPP
    #define _ELROND_CHANNEL_TO_CHANNEL_MODULE_HPP

    #include "module/BaseModule.hpp"
    #include "channel/TxChannel.hpp"
    #include "channel/RxChannel.hpp"

    namespace elrond {
        namespace module {

            class ChannelToChannel : public module::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::TxChannel txCh;
                    elrond::channel::RxChannel rxCh;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~ChannelToChannel();
                    #endif

                    virtual void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
