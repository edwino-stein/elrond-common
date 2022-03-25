#include <elrond.hpp>

using elrond::module::BaseGeneric;

class ExternalModule : public BaseGeneric
{
    public:
        ExternalModule() = default;
        virtual ~ExternalModule() = ELROND_DEFAULT_DESTRUCTOR;

        void setup(elrond::ContextP ctx) override
        {
            ctx->console()->info("setup");
        }

        void start(elrond::ContextP ctx) override
        {
            ctx->console()->info("start");
        }

        void loop(elrond::ContextP ctx) override
        {
            ctx->console()->info("loop");
        }

        void stop(elrond::ContextP ctx) override
        {
            ctx->console()->info("stop");
        }
};

ELROND_DEFINE_DEFAULT_MODULE (
    ExternalModule,
    "External Test Module",
    "Edwino Stein",
    "edwino.stein@gmail.com",
    "1.0.0"
)
