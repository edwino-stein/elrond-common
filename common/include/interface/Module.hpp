#ifndef ELROND_COMMON_INTERFACE_MODULE_HPP
    #define ELROND_COMMON_INTERFACE_MODULE_HPP

    #include "elrond_common_types.hpp"
    #include "platform/ModuleObject.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Module : public elrond::platform::ModuleObject
            {
                public:
                    virtual ~Module() = ELROND_DEFAULT_DESTRUCTOR;
                    virtual elrond::ModuleType moduleType() const =0;
                    virtual void setup(const elrond::Arguments& params) =0;
                    virtual void start() =0;
                    virtual void loop() =0;
                    virtual void stop() =0;
            };
        }
    }

#endif
