#if !defined  _ELROND_BASE_INPUT_DRIVER_MODULE_HPP
    #define _ELROND_BASE_INPUT_DRIVER_MODULE_HPP

    #include "types.hpp"
    #include "modules/BaseModule.hpp"

    namespace elrond {
        namespace modules {

            class BaseInputDriverModule : public elrond::modules::BaseModule {

                public:

                    #if !defined WITHOUT_DESTRUCTORS
                        virtual ~BaseInputDriverModule();
                    #endif

                    virtual elrond::ModuleType getType() const override;
            };
        }
    }

#endif
