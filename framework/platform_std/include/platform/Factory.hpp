#ifndef ELROND_PLATFORM_FACTORY_HPP
    #define ELROND_PLATFORM_FACTORY_HPP

    #include "platform/BaseFactory.hpp"

    namespace elrond
    {
        namespace platform
        {
            template <class M>
            class Factory : public BaseFactory
            {
                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(Factory, =delete, =delete, =delete, =delete, =delete)
                    Factory(const ModuleInfo& info);

                    elrond::interface::Module* create() const override;
                    void destroy(elrond::interface::Module* inst) const override;
            };
        }
    }
#endif
