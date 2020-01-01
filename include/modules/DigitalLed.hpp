#if !defined  _ELROND_DIGITAL_LED_MODULE_HPP
    #define _ELROND_DIGITAL_LED_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"
    #include "runtime/channel/RxChannel.hpp"
    #include "runtime/gpio/BaseGpioPin.hpp"
    #include "runtime/gpio/GenericGpioPin.hpp"

    namespace elrond {
        namespace modules {

            class DigitalLed : public modules::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::RxChannel ch;
                    elrond::gpio::DOutPin pin;

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~DigitalLed();
                    #endif

                    virtual void onInit(elrond::interfaces::ConfigMapInterface &cfg) override;

                    #if defined GENERIC_STD_PLATFORM
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
