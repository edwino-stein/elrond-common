#ifndef ELROND_PLATFORM_RUNTIME_TYPES_HPP
    #define ELROND_PLATFORM_RUNTIME_TYPES_HPP

    #include "elrond.hpp"

    #ifndef ELROND_STD_PLATFORM
        #error "This project is only compatible with STD platforms"
    #endif

    namespace elrond
    {
        namespace platform
        {

            class ModuleInstance;
            class BaseFactoryAdapter;
            template<class M> class InternalFactoryAdapter;
            class DlHandle;

            using ModuleInstanceH = std::unique_ptr<elrond::interface::Module,
                                                    elrond::procedure<elrond::interface::Module*>>;
                                
            using ModuleInstanceP = std::shared_ptr<ModuleInstance>;
            using FactoryAdapterP = std::shared_ptr<BaseFactoryAdapter>;

            std::string demangle(const std::type_info& info);

            template <class T>
            inline std::string demangle() { return demangle(typeid(T)); }
        }
    }

#endif