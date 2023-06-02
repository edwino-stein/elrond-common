#include "elrond_platform_runtime_types.hpp"
#include "platform/DlHandle.ipp"

#include <algorithm>

#if defined(__clang__) || defined(__GNUC__)
    #include <cstdlib>
    #include <cxxabi.h>
#endif

using IFactory = elrond::interface::Factory;
using elrond::platform::DlHandle;

IFactory& elrond::platform::parseExternalFactoryFromDlHandle(DlHandle& handle)
{
    constexpr const char* getApiVerName = ELROND_TO_STR(ELROND_ABI_GET_API_VERSION_FUNC_NAME);
    constexpr const char* getFactoryName = ELROND_TO_STR(ELROND_ABI_GET_FACTORY_FUNC_NAME);
    IFactory* factory = nullptr;

    try
    {
        auto getApiVer = handle.getFunction<ELROND_ABI_NUM_TYPE>(getApiVerName);
        const elrond::byte majorVer = elrond::lowByteHighWord(getApiVer());
        const elrond::byte buildType = elrond::BUILD_TYPE & 0xF0;

        if(buildType == ELROND_BUILD_Release && majorVer != elrond::MAJOR_VER)
        {
            throw std::runtime_error("Invalid module version");
        }

        auto getFactory = handle.getFunction<ELROND_ABI_FACTORY_TYPE>(getFactoryName);

        factory = getFactory();
        if (factory == nullptr)
        {
            throw std::runtime_error("Invalid module factory");
        }
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(std::string("Unable to load elrond module: ") + e.what()); 
    }

    return *factory;
}

std::string elrond::platform::demangle(const std::type_info& info)
{
    #if defined(__clang__) || defined(__GNUC__)

        int status = 0;
        std::unique_ptr<char, void(*)(void*)> res {
            abi::__cxa_demangle(info.name(), nullptr, nullptr, &status),
            std::free
        };

        return (status == 0) ? res.get() : info.name() ;

    #elif defined(ELROND_WINDOWS_PLATFORM)
        const std::string name = info.name();
        const std::size_t pos = name.find(' ');
        return pos != std::string::npos ? name.substr(pos + 1) : name;
    #else
        return info.name();
    #endif
}

bool elrond::platform::isAbsolutePath(const std::string& path)
{
    return path[0] == '/' || path[0] == '\\' || (path.size() > 2 && path[1] == ':');
}

std::string elrond::platform::fileExtension(const std::string& path)
{
    const auto p = path.find_last_of("./\\");
    return (p != std::string::npos && path[p] == '.') ? path.substr(p) : "";
}

std::string elrond::platform::normilizePath(const std::string& path)
{
    std::string p = (path.size() > 2 && path[1] == ':') ? path.substr(2) : path;

    std::transform(
        p.cbegin(),
        p.cend(),
        p.begin(),
        [](char c) -> char
        {
        #ifdef ELROND_WINDOWS_PLATFORM
            return c == '/' ? '\\' : c;
        #else
            return c == '\\' ? '/' : c;
        #endif
        }
    );

    #ifdef ELROND_WINDOWS_PLATFORM
        return (path.size() > 2 && path[1] == ':') ? path.substr(0, 2) + p : p;
    #else
        return p;
    #endif
}
