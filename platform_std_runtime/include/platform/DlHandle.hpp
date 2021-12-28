#ifndef ELROND_PLATFORM_RUNTIME_DL_HANDLE_HPP
    #define ELROND_PLATFORM_RUNTIME_DL_HANDLE_HPP

    #include "elrond_platform_runtime_types.hpp"

    namespace elrond
    {
        namespace platform
        {
            class DlHandle
            {
                protected:

                    void *const handle;

                public:

                    DlHandle(const std::string& path);
                    virtual ~DlHandle();

                    template <class R, class... Args> 
                    std::function<R(Args...)>
                    getFunction(const std::string& name) const;

                    template <class T> 
                    T getFunctionPtr(const std::string& name) const;

                    static void* dlOpen(const std::string& path);
                    static void dlClose(void* handle);
                    static void* dlSym(void* handle, const std::string& symbol);
                    static std::string dlError();

                    static std::string parseObjectPath(const std::string& path);
            };
        }
    }
#endif
