#ifndef ELROND_PLATFORM_RUNTIME_BASE_FACTORY_ADAPTER_HPP
    #define ELROND_PLATFORM_RUNTIME_BASE_FACTORY_ADAPTER_HPP

    #include "elrond_platform_runtime_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            class BaseFactoryAdapter
            {
                protected:

                    virtual const FactoryInterface& factory() const =0;

                public:

                    virtual ~BaseFactoryAdapter() = default;

                    const std::string& name() const;
                    elrond::dWord apiVersion() const;

                    const std::string& infoName() const;
                    const std::string& infoAuthor() const;
                    const std::string& infoEmail() const;
                    const std::string& infoVersion() const;

                    ModuleInstanceP create(const std::string& name) const;
            };
        }
    }

#endif
