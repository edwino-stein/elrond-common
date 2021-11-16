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
                RuntimeCtx ctx(name, new T());
                return ctx;
            }
        }
    }

#endif
