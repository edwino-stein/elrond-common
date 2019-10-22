#if !defined  _ELROND_SERVO_MODULE_HPP
    #define _ELROND_SERVO_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"
    #include "runtime/channel/RxChannel.hpp"
    #include "runtime/gpio/BaseGpioPin.hpp"
    #include "runtime/gpio/GenericGpioPin.hpp"

    namespace elrond {
        namespace modules {

            class Servo : public modules::BaseModule {

                protected:
                    bool inverted = false;
                    elrond::channel::RxChannel ch;
                    elrond::gpio::ServoPin pin;

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~Servo();
                    #endif

                    virtual void onInit(elrond::config::ConfigMap &cfg) override;

                    static const char *_getInternalName();
                    static const char *_infoMainClassName();
                    static int _infoApiVersion();
                    static int _infoApiRevision();
                    static const char *_infoPrettyName();
                    static const char *_infoAuthorName();
                    static const char *_infoAuthorEmail();
                    static const char *_infoVersion();
            };
        }
    }

#endif
