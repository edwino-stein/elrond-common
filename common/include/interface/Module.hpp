#ifndef ELROND_COMMON_INTERFACE_MODULE_HPP
    #define ELROND_COMMON_INTERFACE_MODULE_HPP

    #include "elrond_common_types.hpp"
    #include "elrond_platform.hpp"

    namespace elrond
    {
        namespace interface
        {
            class Module : public elrond::platform::ModuleObject
            {
                public:
                    #ifndef ELROND_DISABLE_DESTRUCTORS
                        virtual ~Module();
                    #endif

                    virtual elrond::ModuleType moduleType() const =0;
                    virtual void setup() =0;
                    virtual void start() =0;
                    virtual void loop() =0;
                    virtual void stop() =0;
            };
        }
    }

#endif
