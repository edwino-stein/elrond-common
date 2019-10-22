#if !defined  _ELROND_BASE_GPIO_MODULE_HPP
    #define _ELROND_BASE_GPIO_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"

    namespace elrond {
        namespace modules {

            class BaseGpioModule : public elrond::modules::BaseModule {

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~BaseGpioModule();
                    #endif

                    virtual elrond::ModuleType getType() const override;

                    virtual void attach(elrond::gpio::BaseGpioPin &pin)=0;
            };
        }
    }

#endif
