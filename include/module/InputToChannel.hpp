#if !defined  _ELROND_INPUT_TO_CHANNEL_MODULE_HPP
    #define _ELROND_INPUT_TO_CHANNEL_MODULE_HPP

    #include "module/BaseModule.hpp"
    #include "channel/TxChannel.hpp"
    #include "input/InputCallback.hpp"

    namespace elrond {
        namespace module {

            class InputToChannel : public elrond::module::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::TxChannel txCh;
                    elrond::input::InputCallback inKey;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~InputToChannel();
                    #endif

                    virtual void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
