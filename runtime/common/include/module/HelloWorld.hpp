#ifndef ELROND_COMMON_RUNTIME_MODULE_HELLO_WORLD_HPP
    #define ELROND_COMMON_RUNTIME_MODULE_HELLO_WORLD_HPP

    #include <elrond.hpp>

    namespace elrond
    {
        namespace module
        {
            class HelloWorld : public elrond::module::BaseGeneric
            {
                private:

                    elrond::string message;
                    long interval;

                public:

                    HelloWorld();

                    void setup(elrond::Context ctx) override;
                    void start(elrond::Context ctx) override;
                    void loop(elrond::Context ctx) override;
                    void stop(elrond::Context ctx) override;
            };
        }
    }

#endif
