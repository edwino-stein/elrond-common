#ifndef ELROND_PLATFORM_BASE_FACTORY_HPP
    #define ELROND_PLATFORM_BASE_FACTORY_HPP

    #include "interface/Factory.hpp"

    namespace elrond
    {
        namespace platform
        {
            class BaseFactory : public elrond::interface::Factory
            {
                private:
                    ModuleInfo _info;

                protected:
                    BaseFactory(const ModuleInfo& info);

                public:
                    ~BaseFactory() = default;

                    const ModuleInfo& info() const override;
                    elrond::dWord apiVersion() const override;
            };
        }
    }

#endif
