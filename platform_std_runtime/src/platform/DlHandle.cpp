#include "platform/DlHandle.ipp"

#ifdef ELROND_WINDOWS_PLATFORM
    #define DL_WIN_API
#else
    #define DL_UNIX_API
    #include <dlfcn.h>
#endif

using elrond::platform::DlHandle;

DlHandle::DlHandle(const std::string& path) : handle(DlHandle::dlOpen(path))
{}

DlHandle::~DlHandle()
{
    DlHandle::dlClose(this->handle);
}

#ifdef DL_WIN_API

    void* DlHandle::dlOpen(const std::string& path)
    {
        throw std::runtime_error("Windows DL not implemented");
    }

    void DlHandle::dlClose(void* handle)
    {
        throw std::runtime_error("Windows DL not implemented");
    }

    void* DlHandle::dlSym(void* handle, const std::string& symbol)
    {
        throw std::runtime_error("Windows DL not implemented");
    }

#elif defined(DL_UNIX_API)

    void* DlHandle::dlOpen(const std::string& path)
    {
        #if defined(ELROND_APPLE_PLATFORM)
            constexpr int DL_MODE = RTLD_LOCAL;
        #elif defined(ELROND_LINUX_PLATFORM)
            constexpr int DL_MODE = RTLD_NOW | RTLD_GLOBAL;
        #else
            constexpr int DL_MODE = 0;
        #endif

        void* handle = ::dlopen(DlHandle::parseObjectPath(path).c_str(), DL_MODE);
        if(!(handle)) throw std::runtime_error(dlerror());
        return handle;
    }

    void DlHandle::dlClose(void* handle)
    {
        if (handle != nullptr) ::dlclose(handle);
    }

    void* DlHandle::dlSym(void* handle, const std::string& symbol)
    {
        void* s = ::dlsym(handle, symbol.c_str());
        if(s == nullptr) throw std::runtime_error(dlerror());
        return s;
    }

#else

    void* DlHandle::dlOpen(const std::string& path)
    {
        throw std::runtime_error("Incompatible platform");
    }

    void DlHandle::dlClose(void* handle)
    {
        throw std::runtime_error("Incompatible platform");
    }

    void* DlHandle::dlSym(void* handle, const std::string& symbol)
    {
        throw std::runtime_error("Incompatible platform");
    }

#endif

std::string DlHandle::parseObjectPath(const std::string& path)
{
    #ifdef ELROND_WINDOWS_PLATFORM
        constexpr const char* LIB_EXT = "dll";
    #elif defined(ELROND_APPLE_PLATFORM)
        constexpr const char* LIB_EXT = "dylib";
    #elif defined(ELROND_LINUX_PLATFORM)
        constexpr const char* LIB_EXT = "so";
    #else
        throw std::runtime("Incompatible platform")
    #endif

    std::string preffix = "";
    std::string suffix = "";
    
    #ifdef DL_UNIX_API
        if (path[0] != '/' && path[0] != '.')
        {
            preffix = "./";
        }
    #endif

    if (DlHandle::getObjectExt(path) != LIB_EXT)
    {
        suffix = std::string(".") + LIB_EXT; 
    }

    return preffix + path + suffix;
}

std::string DlHandle::getObjectExt(const std::string& path)
{
    const std::size_t p = path.rfind('.', path.length());
    return (p != std::string::npos) ? path.substr(p + 1, path.length() - p) : "";
}
