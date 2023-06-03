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
                    virtual void setup(elrond::Context ctx) override;
                    virtual void start(elrond::Context ctx) override;
                    virtual void loop(elrond::Context ctx) override;
                    virtual void stop(elrond::Context ctx) override;
            };
        }
    }

#endif
