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
                    virtual ~Abstract() = ELROND_DEFAULT_DESTRUCTOR;

                    virtual void setup(const elrond::Arguments&) override;
                    virtual void start() override;
                    virtual void loop() override;
                    virtual void stop() override;
            };
        }
    }

#endif
