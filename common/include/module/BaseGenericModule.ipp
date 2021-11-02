#ifndef ELROND_COMMON_MODULE_BASE_GENERIC_MODULE_IPP
    #define ELROND_COMMON_MODULE_BASE_GENERIC_MODULE_IPP

    #include "module/BaseGenericModule.hpp"
    #include "module/AbstractModule.ipp"

    namespace elrond
    {
        namespace module
        {
            #ifndef ELROND_DISABLE_DESTRUCTORS
                ELROND_INLINE BaseGenericModule::~BaseGenericModule(){}
            #endif

            ELROND_INLINE elrond::ModuleType BaseGenericModule::moduleType() const
            { return elrond::ModuleType::GENERIC; }
        }
    }

#endif
