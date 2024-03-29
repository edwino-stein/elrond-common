#ifndef ELROND_PLATFORM_BASE_FACTORY_IPP
    #define ELROND_PLATFORM_BASE_FACTORY_IPP

    #include "platform/BaseFactory.hpp"

    namespace elrond
    {
        namespace platform
        {
            ELROND_INLINE
            BaseFactory::BaseFactory(
                const elrond::platform::ModuleInfo& info,
                const std::string& name
            ):
                _info(info),
                _name(name)
            {}

            ELROND_INLINE
            const ModuleInfo& BaseFactory::info() const
            {
                return this->_info;
            }

            ELROND_INLINE
            const elrond::string& BaseFactory::name() const
            {
                return this->_name;
            }

            ELROND_INLINE
            elrond::dWord BaseFactory::apiVersion() const
            {
                return elrond::getApiVersion();
            }
        }
    }

#endif
