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

                public:

                    HelloWorld();

                    void setup(elrond::ContextP ctx) override;
                    void start(elrond::ContextP ctx) override;
                    void loop(elrond::ContextP ctx) override;
                    void stop(elrond::ContextP ctx) override;
            };
        }
    }

#endif
