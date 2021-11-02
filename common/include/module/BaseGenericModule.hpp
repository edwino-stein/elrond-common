#ifndef ELROND_COMMON_MODULE_BASE_GENERIC_MODULE_HPP
    #define ELROND_COMMON_MODULE_BASE_GENERIC_MODULE_HPP

    #include "module/AbstractModule.hpp"

    namespace elrond
    {
        namespace module
        {
            class BaseGenericModule : public elrond::module::AbstractModule
            {
                public:
                    #ifndef ELROND_DISABLE_DESTRUCTORS
                        virtual ~BaseGenericModule();
                    #endif

                    elrond::ModuleType moduleType() const override;
            };
        }
    }

#endif
