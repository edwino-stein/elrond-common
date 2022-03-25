#ifndef ELROND_PLATFORM_RUNTIME_INTERNAL_FACTORY_ADAPTER_HPP
    #define ELROND_PLATFORM_RUNTIME_INTERNAL_FACTORY_ADAPTER_HPP

    #include "platform/BaseFactoryAdapter.hpp"

    namespace elrond
    {
        namespace platform
        {
            template <class M>
            class InternalFactoryAdapter : public BaseFactoryAdapter
            {
                private:

                    const Factory<M> _factory;

                protected:

                    const FactoryInterface& factory() const override;

                public:

                    InternalFactoryAdapter(const ModuleInfo& info);
            };
        }
    }

#endif
