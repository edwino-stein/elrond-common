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
                public:

                    using GetApiVerP = ELROND_MOD_NUM_TYPE (*)();
                    using GetApiVerH = std::function<ELROND_MOD_NUM_TYPE ()>;

                    using GetFactoryP = ELROND_MOD_FACTORY_TYPE (*)();
                    using GetFactoryH = std::function<ELROND_MOD_FACTORY_TYPE ()>;

                    static constexpr const char* GetApiVerName = ELROND_TO_STR(ELROND_MOD_GET_API_VERSION_FUNC_NAME);
                    static constexpr const char* GetFactoryName = ELROND_TO_STR(ELROND_MOD_GET_FACTORY_FUNC_NAME);

                private:

                    DlHandle _handle;
                    FactoryInterface* _factory;

                protected:

                    const FactoryInterface& factory() const override;

                public:
                    ExternalFactoryAdapter(const std::string& path);
                    virtual ~ExternalFactoryAdapter() = default;
            };
        }
    }

#endif
