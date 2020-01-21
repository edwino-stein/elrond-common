#if !defined  _ELROND_ANALOG_LED_MODULE_HPP
    #define _ELROND_ANALOG_LED_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"
    #include "runtime/gpio/BaseGpioPin.hpp"
    #include "runtime/gpio/GenericGpioPin.hpp"
    #include "channel/RxChannel.hpp"

    namespace elrond {
        namespace modules {

            class AnalogLed : public modules::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::RxChannel ch;
                    elrond::gpio::PwmPin pin;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~AnalogLed();
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
