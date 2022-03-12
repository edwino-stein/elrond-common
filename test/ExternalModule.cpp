#include <elrond.hpp>

using elrond::module::BaseGeneric;

class ExternalModule : public BaseGeneric
{
    public:
        ExternalModule() = default;
        virtual ~ExternalModule() = ELROND_DEFAULT_DESTRUCTOR;

        void setup(const elrond::Parameters&) override
        {
            elrond::ctx(this)->console()->info("setup");
        }

        void start() override
        {
            elrond::ctx(this)->console()->info("start");
        }

        void loop() override
        {
            elrond::ctx(this)->console()->info("loop");
        }

        void stop() override
        {
            elrond::ctx(this)->console()->info("stop");
        }
};

ELROND_DEFINE_DEFAULT_MODULE (
    ExternalModule,
    "External Test Module",
    "Edwino Stein",
    "edwino.stein@gmail.com",
    "1.0.0"
)
