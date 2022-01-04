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
                    Factory(const ModuleInfo& info, const std::string& name);
                    virtual ~Factory() = default;

                    elrond::interface::Module* create() const override;
                    void destroy(elrond::interface::Module* inst) const override;
            };
        }
    }
#endif
