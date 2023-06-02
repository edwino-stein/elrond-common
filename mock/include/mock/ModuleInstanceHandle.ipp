#ifndef ELROND_MOCK_MODULE_INSTANCE_HANDLE_IPP
    #define ELROND_MOCK_MODULE_INSTANCE_HANDLE_IPP

    #include "mock/ModuleInstanceHandle.hpp"

    namespace elrond
    {
        namespace mock
        {
            template <class T>
            InternalInstanceModuleHandle<T>::InternalInstanceModuleHandle(const elrond::string& name, const elrond::platform::ModuleInfo& info)
            : ModuleInstanceHandle(name), _factory(info) { this->_instance = this->factory().create(); }
            
            template <class T>
            InternalInstanceModuleHandle<T>::~InternalInstanceModuleHandle() { this->factory().destroy(this->_instance); }

            template <class T>
            elrond::interface::Factory& InternalInstanceModuleHandle<T>::factory() const
            { return const_cast<InternalInstanceModuleHandle<T>*>(this)->_factory; }
        }
    }

#endif
