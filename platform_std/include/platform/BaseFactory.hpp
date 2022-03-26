#ifndef ELROND_PLATFORM_BASE_FACTORY_HPP
    #define ELROND_PLATFORM_BASE_FACTORY_HPP

    #include "platform/FactoryInterface.hpp"

    namespace elrond
    {
        namespace platform
        {
            class BaseFactory : public FactoryInterface
            {
                private:

                    const ModuleInfo _info;
                    const std::string _name;

                public:
                    BaseFactory(const ModuleInfo& info, const std::string& name);

                    const ModuleInfo& info() const override;
                    const elrond::string& name() const override;
                    elrond::dWord apiVersion() const override;
            };
        }
    }

#endif
