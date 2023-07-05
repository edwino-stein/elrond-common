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
                    ELROND_CLASS_SPECIAL_MEMBERS(BaseFactory, =delete, =delete, =delete, =delete, =delete)

                    const ModuleInfo& info() const override;
                    elrond::dWord apiVersion() const override;
            };
        }
    }

#endif
