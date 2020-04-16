#if !defined  _ELROND_ANALOG_LED_MODULE_HPP
    #define _ELROND_ANALOG_LED_MODULE_HPP

    #include "elrond_ext_types.hpp"
    #include "module/BaseModule.hpp"
    #include "channel/RxChannel.hpp"
    #include "gpio/BaseGpioPin.hpp"
    #include "gpio/GenericGpioPin.hpp"

    namespace elrond {
        namespace module {

            class AnalogLed : public module::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::RxChannel ch;
                    elrond::gpio::PwmPin pin;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~AnalogLed();
                    #endif

                    virtual void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;

                    ELROND_DEFINE_INTER_MOD_DEF_FUNCS;
            };
        }
    }

#endif
