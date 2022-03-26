#ifndef ELROND_PLATFORM_RUNTIME_EXTERNAL_FACTORY_ADAPTER_HPP
    #define ELROND_PLATFORM_RUNTIME_EXTERNAL_FACTORY_ADAPTER_HPP

    #include "platform/BaseFactoryAdapter.hpp"
    #include "platform/DlHandle.ipp"

    namespace elrond
    {
        namespace platform
        {
            class ExternalFactoryAdapter : public BaseFactoryAdapter
            {
                private:

                    DlHandle _handle;
                    FactoryInterface* _factory;

                protected:

                    const FactoryInterface& factory() const override;

                public:
                    ExternalFactoryAdapter(const std::string& path);
            };
        }
    }

#endif
