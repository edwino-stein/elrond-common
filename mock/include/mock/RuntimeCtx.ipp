#ifndef ELROND_MOCK_RUNTIME_CTX_IPP
    #define ELROND_MOCK_RUNTIME_CTX_IPP

    #include "mock/RuntimeCtx.hpp"
    #include "mock/ModuleInstanceHandle.ipp"

    namespace elrond
    {
        namespace mock
        {
            template <class T>
            RuntimeCtx RuntimeCtx::create(const elrond::string& name)
            {
                auto moduleHandle = std::make_shared<InternalInstanceModuleHandle<T>>(name, elrond::platform::ModuleInfo());
                return RuntimeCtx(moduleHandle); 
            }

            template <class T>
            RuntimeCtx RuntimeCtx::create(const elrond::string& name, const elrond::platform::ModuleInfo& info)
            {
                auto moduleHandle = std::make_shared<InternalInstanceModuleHandle<T>>(name, info);
                return RuntimeCtx(moduleHandle); 
            }
        }
    }

#endif
