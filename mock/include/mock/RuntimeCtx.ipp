#ifndef ELROND_MOCK_RUNTIME_CTX_IPP
    #define ELROND_MOCK_RUNTIME_CTX_IPP

    #include "mock/RuntimeCtx.hpp"

    namespace elrond
    {
        namespace mock
        {
            template <class T>
            RuntimeCtx RuntimeCtx::create(elrond::string name)
            {
                return RuntimeCtx (
                    name,
                    std::make_shared<elrond::platform::InternalFactoryAdapter<T>>(
                        RuntimeCtx::mockedModuleInfo
                    )
                ); 
            }

            template <class T>
            RuntimeCtx RuntimeCtx::create(elrond::string name, elrond::platform::ModuleInfo& info)
            {
                return RuntimeCtx (
                    name,
                    std::make_shared<elrond::platform::InternalFactoryAdapter<T>>(info)
                ); 
            }
        }
    }

#endif
