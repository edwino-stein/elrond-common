#ifndef ELROND_RUNTIME_MODULE_HELLO_WORLD_HPP
    #define ELROND_RUNTIME_MODULE_HELLO_WORLD_HPP

    #include <elrond.hpp>

    namespace elrond
    {
        namespace module
        {
            class HelloWorld : public elrond::module::BaseGenericModule
            {
                public:

                    #ifndef ELROND_DISABLE_DESTRUCTORS
                        virtual ~HelloWorld();
                    #endif

                    void setup() override;
                    void start() override;
                    void loop() override;
                    void stop() override;
            };
        }
    }

#endif
