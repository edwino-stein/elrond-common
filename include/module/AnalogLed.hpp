#if !defined  _ELROND_ANALOG_LED_MODULE_HPP
    #define _ELROND_ANALOG_LED_MODULE_HPP

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

                    virtual void onInit(elrond::interface::ConfigMap& cfg) override;

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
