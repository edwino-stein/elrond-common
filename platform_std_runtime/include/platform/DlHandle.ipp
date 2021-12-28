#ifndef ELROND_PLATFORM_DL_HANDLE_IPP
    #define ELROND_PLATFORM_DL_HANDLE_IPP

    #include "platform/DlHandle.hpp"

    namespace elrond
    {
        namespace platform
        {
            template <class R, class... Args>
            std::function<R(Args...)>
            DlHandle::getFunction(const std::string& name) const
            {
                return this->getFunctionPtr<R(ELROND_ABI_CALL *)(Args...)>(name);
            }

            template <class T> 
            T DlHandle::getFunctionPtr(const std::string& name) const
            {
                return reinterpret_cast<T>(DlHandle::dlSym(this->handle, name));
            }
        }
    }

#endif
