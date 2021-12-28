#ifndef ELROND_PLATFORM_STD_EXTERNAL_IPP
    #define ELROND_PLATFORM_STD_EXTERNAL_IPP

    #ifndef ELROND_ENABLE_EXTERNAL_ABI_SETUP
        #error "This header must be used with ELROND_ENABLE_EXTERNAL_ABI_SETUP macro"
    #endif

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            extern elrond::platform::FactoryInterface* __external_factory__;

            template<class T>
            struct ExternalFactoryHolder
            {
                elrond::platform::Factory<T> factory;
                ExternalFactoryHolder(const elrond::platform::ModuleInfo info, const char* name)
                :
                    factory(info, name)
                {
                    __external_factory__ = &(this->factory);
                }
            };
        }
    }

    #define ELROND_DEFINE_MODULE(C, ...) \
        static elrond::platform::ExternalFactoryHolder<C> __elrond_module_factory__ ({__VA_ARGS__}, #C);

    #define ELROND_DEFINE_DEFAULT_MODULE(C, ...) \
    elrond::platform::FactoryInterface* elrond::platform::__external_factory__ = nullptr; \
    ELROND_DEFINE_MODULE(C, __VA_ARGS__) \
    extern "C" { \
        ELROND_ABI_EXPORT ELROND_ABI_NUM_TYPE ELROND_ABI_CALL ELROND_ABI_GET_API_VERSION_FUNC_NAME () \
        { return elrond::getApiVersion(); } \
        ELROND_ABI_EXPORT ELROND_ABI_FACTORY_TYPE ELROND_ABI_CALL ELROND_ABI_GET_FACTORY_FUNC_NAME () \
        { return elrond::platform::__external_factory__; } \
    }

#endif
