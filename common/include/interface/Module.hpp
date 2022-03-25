#ifndef ELROND_COMMON_INTERFACE_MODULE_HPP
    #define ELROND_COMMON_INTERFACE_MODULE_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Module
            {
                public:
                    virtual ~Module() = ELROND_DEFAULT_DESTRUCTOR;
                    virtual elrond::ModuleType moduleType() const =0;

                    virtual void setup(elrond::ContextP ctx) =0;
                    virtual void start(elrond::ContextP ctx) =0;
                    virtual void loop(elrond::ContextP ctx) =0;
                    virtual void stop(elrond::ContextP ctx) =0;
            };
        }
    }

#endif
