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

                    #ifdef ELROND_WITH_MODULES_INFO
                        static const char *_getInternalName();
                        static const char *_infoMainClassName();
                        static int _infoApiVersion();
                        static int _infoApiRevision();
                        static const char *_infoPrettyName();
                        static const char *_infoAuthorName();
                        static const char *_infoAuthorEmail();
                        static const char *_infoVersion();
                    #endif
            };
        }
    }

#endif
