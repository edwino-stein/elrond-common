#if !defined  _ELROND_DIGITAL_LED_MODULE_HPP
    #define _ELROND_DIGITAL_LED_MODULE_HPP

    #include "elrond_ext_types.hpp"
    #include "module/BaseModule.hpp"
    #include "channel/RxChannel.hpp"
    #include "gpio/GpioPin.hpp"

    namespace elrond {
        namespace module {

            class DigitalLed : public elrond::module::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::RxChannel ch;
                    elrond::gpio::DOutPin pin;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~DigitalLed();
                    #endif

                    virtual void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
