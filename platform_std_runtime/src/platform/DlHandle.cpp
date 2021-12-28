#include "platform/DlHandle.ipp"

#ifdef ELROND_WINDOWS_PLATFORM
    #define DL_WIN_API
#else
    #define DL_UNIX_API
    #include <dlfcn.h>
#endif

using elrond::platform::DlHandle;
using elrond::platform::fileExtension;
using elrond::platform::isAbsolutePath;
using elrond::platform::normilizePath;

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

    std::string DlHandle::dlError()
    {
        return "";
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
        if(!(handle)) throw std::runtime_error(DlHandle::dlError());
        return handle;
    }

    void DlHandle::dlClose(void* handle)
    {
        if (handle == nullptr) return;
        if (::dlclose(handle) != 0) throw std::runtime_error(DlHandle::dlError());
    }

    void* DlHandle::dlSym(void* handle, const std::string& symbol)
    {
        void* s = ::dlsym(handle, symbol.c_str());
        if(s == nullptr) throw std::runtime_error(DlHandle::dlError());
        return s;
    }

    std::string DlHandle::dlError()
    {
        return dlerror();
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

    std::string DlHandle::dlError()
    {
        return "";
    }

#endif

std::string DlHandle::parseObjectPath(const std::string& path)
{
    #ifdef ELROND_WINDOWS_PLATFORM
        constexpr const char* LIB_EXT = ".dll";
        constexpr const char* PREFFIX = "\\.";
    #elif defined(ELROND_APPLE_PLATFORM)
        constexpr const char* LIB_EXT = ".dylib";
        constexpr const char* PREFFIX = "./";
    #elif defined(ELROND_LINUX_PLATFORM)
        constexpr const char* LIB_EXT = ".so";
        constexpr const char* PREFFIX = "./";
    #else
        throw std::runtime("Incompatible platform");
    #endif

    const std::string pfx = (isAbsolutePath(path) || path[0] == '.') ? "" : PREFFIX;
    const std::string ext = fileExtension(path) == "" ? LIB_EXT : "";
    return normilizePath(pfx + path + ext);
}
