#ifndef ELROND_PLATFORM_RUNTIME_INTERNAL_FACTORY_ADAPTER_IPP
    #define ELROND_PLATFORM_RUNTIME_INTERNAL_FACTORY_ADAPTER_IPP

    #include "platform/InternalFactoryAdapter.hpp"
    
    namespace elrond
    {
        namespace platform
        {
            template <class M>
            InternalFactoryAdapter<M>::InternalFactoryAdapter(const ModuleInfo& info)
            :
                _factory(info, elrond::platform::demangle<M>())
            {}

            template <class M>
            const FactoryInterface& InternalFactoryAdapter<M>::factory() const
            {
                return this->_factory;
            }
        }
    }

#endif
