#if !defined  _ELROND_BASE_GPIO_MODULE_HPP
    #define _ELROND_BASE_GPIO_MODULE_HPP

    #include "module/BaseModule.hpp"

    namespace elrond {
        namespace module {

            class BaseGpioModule : public elrond::module::BaseModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseGpioModule();
                    #endif

                    virtual elrond::ModuleType getType() const override;

                    virtual void attach(elrond::gpio::BaseGpioPin& pin)=0;
                    virtual elrond::word read(elrond::gpio::BaseGpioPin& pin)=0;
                    virtual void write(elrond::gpio::BaseGpioPin& pin,
                                       const elrond::word data)=0;
            };
        }
    }

#endif
