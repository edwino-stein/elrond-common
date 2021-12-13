#ifndef ELROND_PLATFORM_MODULE_FACTORY_IPP
    #define ELROND_PLATFORM_MODULE_FACTORY_IPP

    #include "platform/Factory.hpp"

    namespace elrond
    {
        namespace platform
        {
            template <class M>
            Factory<M>::Factory(const ModuleInfo& info, const std::string& name)
            :
                BaseFactory(info, name)
            {}

            template <class M>
            elrond::interface::Module* Factory<M>::create() const
            {
                return new M();
            }
            
            template <class M>
            void Factory<M>::destroy(elrond::interface::Module* inst) const
            {
                if (inst != nullptr && dynamic_cast<M*>(inst) != nullptr) delete inst;
            }
        }
    }

#endif
