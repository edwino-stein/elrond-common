#include "elrond_platform_runtime_types.hpp"
#include <algorithm>

#if defined(__clang__) || defined(__GNUC__)
    #include <cstdlib>
    #include <cxxabi.h>
#endif

std::string elrond::platform::demangle(const std::type_info& info)
{
    #if defined(__clang__) || defined(__GNUC__)

        int status = 0;
        std::unique_ptr<char, void(*)(void*)> res {
            abi::__cxa_demangle(info.name(), nullptr, nullptr, &status),
            std::free
        };

        return (status == 0) ? res.get() : info.name() ;

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

    return p;
}
