#ifndef ELROND_PLATFORM_MODULE_OBJECT_HPP
    #define ELROND_PLATFORM_MODULE_OBJECT_HPP

    #include "elrond_common_types.hpp"
    #include "platform/Object.hpp"
    
    namespace elrond
    {
        namespace platform
        {
            class ModuleObject : public elrond::platform::Object
            {
                public:
                    virtual ~ModuleObject() = ELROND_DEFAULT_DESTRUCTOR;
            };
        }
    }

#endif
