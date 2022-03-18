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
                    virtual ~HelloWorld() = ELROND_DEFAULT_DESTRUCTOR;
                    void setup(const elrond::Parameters& params) override;
                    void start() override;
                    void loop() override;
                    void stop() override;
            };
        }
    }

#endif
