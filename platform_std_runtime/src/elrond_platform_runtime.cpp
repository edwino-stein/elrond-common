#include "elrond_platform_runtime_types.hpp"

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

        return (status==0) ? res.get() : info.name() ;

    #else
        return info.name();
    #endif
}
