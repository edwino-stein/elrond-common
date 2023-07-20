#ifndef ELROND_PLATFORM_RUNTIME_TYPES_HPP
    #define ELROND_PLATFORM_RUNTIME_TYPES_HPP

    #include <elrond.hpp>

    #ifndef ELROND_STD_PLATFORM
        #error "This project is only compatible with STD platforms"
    #endif

    #include <sstream>
    #include <map>

    namespace elrond
    {
        namespace platform
        {
            class DlHandle;

            std::map<std::string, elrond::interface::Factory*>& internalModuleFactories();
            elrond::interface::Factory& parseExternalFactoryFromDlHandle(DlHandle& handle);
            std::string demangle(const std::type_info& info);

            template <class T>
            inline std::string demangle() { return demangle(typeid(T)); }

            bool isAbsolutePath(const std::string& path);
            std::string fileExtension(const std::string& path);
            std::string normilizePath(const std::string& path);
        }

        namespace runtime
        {
            class Console;
            class OStream;
        }
    }

#endif
