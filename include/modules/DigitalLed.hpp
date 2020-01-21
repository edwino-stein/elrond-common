#if !defined  _ELROND_DIGITAL_LED_MODULE_HPP
    #define _ELROND_DIGITAL_LED_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"
    #include "channel/RxChannel.hpp"
    #include "gpio/BaseGpioPin.hpp"
    #include "gpio/GenericGpioPin.hpp"

    namespace elrond {
        namespace modules {

            class DigitalLed : public modules::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::RxChannel ch;
                    elrond::gpio::DOutPin pin;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~DigitalLed();
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
