#ifndef ELROND_COMMON_MODULE_ABSTRACT_HPP
    #define ELROND_COMMON_MODULE_ABSTRACT_HPP

    #include "interface/Module.hpp"

    namespace elrond
    {
        namespace module
        {
            class Abstract :  public elrond::interface::Module
            {
                public:
                    virtual void setup(elrond::ContextP ctx) override;
                    virtual void start(elrond::ContextP ctx) override;
                    virtual void loop(elrond::ContextP ctx) override;
                    virtual void stop(elrond::ContextP ctx) override;
            };
        }
    }

#endif
