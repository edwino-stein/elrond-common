#if !defined  _ELROND_BASE_INPUT_MODULE_HPP
    #define _ELROND_BASE_INPUT_MODULE_HPP

    #include "module/BaseModule.hpp"

    namespace elrond {
        namespace module {

            class BaseInputModule : public elrond::module::BaseModule {

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseInputModule();
                    #endif

                    virtual void addInputListener(const elrond::sizeT key,
                                                  elrond::input::InputListener* listener)=0;

                    virtual elrond::ModuleType getType() const override;
            };
        }
    }

#endif
