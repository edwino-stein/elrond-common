#ifndef ELROND_COMMON_MODULE_ABSTRACT_MODULE_HPP
    #define ELROND_COMMON_MODULE_ABSTRACT_MODULE_HPP

    #include "interface/Module.hpp"

    namespace elrond
    {
        namespace module
        {
            class AbstractModule : public elrond::interface::Module
            {
                public:
                    #ifndef ELROND_DISABLE_DESTRUCTORS
                        virtual ~AbstractModule();
                    #endif

                    virtual void setup() override;
                    virtual void start() override;
                    virtual void loop() override;
                    virtual void stop() override;
            };
        }
    }

#endif
