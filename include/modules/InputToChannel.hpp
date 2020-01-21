#if !defined  _ELROND_INPUT_TO_CHANNEL_MODULE_HPP
    #define _ELROND_INPUT_TO_CHANNEL_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"
    #include "runtime/channel/TxChannel.hpp"
    #include "runtime/InputCallback.hpp"

    namespace elrond {
        namespace modules {

            class InputToChannel : public modules::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::TxChannel txCh;
                    elrond::input::InputCallback inKey;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~InputToChannel();
                    #endif

                    virtual void onInit(elrond::interfaces::ConfigMapInterface &cfg) override;

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
