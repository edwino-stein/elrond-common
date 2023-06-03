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

                    ELROND_OPT_DFLT_VDESTRUCTOR(Module);

                    virtual elrond::ModuleType moduleType() const =0;

                    virtual void setup(elrond::Context ctx) =0;
                    virtual void start(elrond::Context ctx) =0;
                    virtual void loop(elrond::Context ctx) =0;
                    virtual void stop(elrond::Context ctx) =0;
            };
        }
    }

#endif
