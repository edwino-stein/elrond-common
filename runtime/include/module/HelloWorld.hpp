#ifndef ELROND_RUNTIME_MODULE_HELLO_WORLD_HPP
    #define ELROND_RUNTIME_MODULE_HELLO_WORLD_HPP

    #include <elrond.hpp>

    namespace elrond
    {
        namespace module
        {
            class HelloWorld : public elrond::module::BaseGeneric
            { 
                public:
                    virtual ~HelloWorld() = ELROND_DEFAULT_DESTRUCTOR;
                    void setup() override;
                    void start() override;
                    void loop() override;
                    void stop() override;
            };
        }
    }

#endif
