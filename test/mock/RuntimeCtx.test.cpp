#include <elrond_mock.hpp>
#include "catch2.hpp"
#include <cstdlib>
#include <ctime>

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::module::BaseGeneric;
using elrond::mock::ConsoleAdapter;
using elrond::mock::Arguments;
using elrond::runtime::OStream;
using elrond::mock::StreamAdapter;
using Catch::Matchers::ContainsSubstring;

const std::string TEST_BUILD_DIR = std::string(ELROND_BUILD_DIR) + "/test/";

SCENARIO("Test a mocked runtime context with a simple module instance for lyfecycle methods", "[mock][RuntimeCtx]")
{
    class TestModule : public BaseGeneric
    {
        public:
            elrond::string called = "none";
            elrond::sizeT loops = 0;
            void setup(elrond::ContextP) { this->called = "setup"; }
            void start(elrond::ContextP) { this->called = "start"; }
            void stop(elrond::ContextP) { this->called = "stop"; }
            void loop(elrond::ContextP)
            {
                this->called = "loop";
                this->loops++;
            }
    };

    GIVEN("A generic module instance")
    {
        auto ctx = RuntimeCtx::create<TestModule>("test");

        REQUIRE(ctx.name() == "test");
        REQUIRE(isInstanceOf<BaseGeneric>(ctx.instance()));
        REQUIRE(isInstanceOf<TestModule>(ctx.instance()));
        REQUIRE(ctx.instance().moduleType() == elrond::ModuleType::GENERIC);

        WHEN("Calls the factory getter")
        {
            auto& factory = ctx.factory();
            THEN("Must return the expected adapter")
            {
                CHECK(factory.apiVersion() == elrond::getApiVersion());
            }
        }

        WHEN("Module instance requires your context")
        {
            auto context = ctx.ctx();
            THEN("Must be the same context instance")
            {
                REQUIRE(isInstanceOf<RuntimeCtx::Context>(context.get()));
                REQUIRE(&(reinterpret_cast<RuntimeCtx::Context*>(context.get())->ctx) == &ctx);
            }
        }

        WHEN("Calls the setup method")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callSetup();
            THEN("Must be called the setup method")
            {
                REQUIRE(instance.called == "setup");
                REQUIRE(instance.loops == 0);
            }
        }

        WHEN("Calls the start method")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callStart();
            THEN("Must be called the start method")
            {
                REQUIRE(instance.called == "start");
                REQUIRE(instance.loops == 0);
            }
        }

        WHEN("Calls the loop method one time")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callLoop();
            THEN("Must be called the loop method one time")
            {
                REQUIRE(instance.called == "loop");
                REQUIRE(instance.loops == 1);
            }
        }

        WHEN("Calls the loop method zero time")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callLoop(0);
            THEN("Must be called the loop method one time")
            {
                REQUIRE(instance.called == "none");
                REQUIRE(instance.loops == 0);
            }
        }

        WHEN("Calls the loop method three times")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callLoop(3);
            THEN("Must be called the loop method three time")
            {
                REQUIRE(instance.called == "loop");
                REQUIRE(instance.loops == 3);
            }
        }

        WHEN("Calls the loop method until something happens")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            
            srand (time(nullptr));
            const int magic = rand() % 10 + 1;
            long times = -1;

            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callLoop(
                [&magic, &times]()
                {
                    times++;
                    srand (time(nullptr));
                    return magic == rand() % 10 + 1;
                }
            );

            THEN("Must be called the loop method many times until something happens")
            {
                REQUIRE((instance.called == "loop" || instance.called == "none"));
                REQUIRE(instance.loops == static_cast<elrond::sizeT>(times));
            }
        }

        WHEN("Calls the stop method")
        {
            auto& instance = reinterpret_cast<TestModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.loops == 0);

            ctx.callStop();
            THEN("Must be called the stop method")
            {
                REQUIRE(instance.called == "stop");
                REQUIRE(instance.loops == 0);
            }
        }
    }
}

SCENARIO("Test a mocked runtime context with a simple module instance for console operations", "[mock][RuntimeCtx]")
{
    class TestConsoleModule : public BaseGeneric
    {
        public:
            bool error = false;
            void setup(elrond::ContextP ctx)
            {
                auto console = ctx->console();
                if(this->error) console->error("Error message");
                else console->info("Info message");
            }
    };

    GIVEN("A generic module in a context with ConsoleAdapter instance")
    {
        auto ctx = RuntimeCtx::create<TestConsoleModule>("test");

        WHEN("Set a custom console adapter instance")
        {
            std::ostringstream oss;
            OStream stream(oss);
            ConsoleAdapter consoleAdapter(stream, StreamAdapter::makePretty);
            ctx.console(consoleAdapter);

            WHEN("The module instance calls console info method")
            {
                auto& instance = reinterpret_cast<TestConsoleModule&>(ctx.instance());
                REQUIRE_FALSE(instance.error);

                ctx.callSetup();
                THEN("The info ostringstream must capture the string")
                {
                    CHECK(oss.str() == "[INFO]\tInfo message\n");
                }
            }

            WHEN("The module instance calls console error method")
            {
                auto& instance = reinterpret_cast<TestConsoleModule&>(ctx.instance());
                instance.error = true;
                REQUIRE(instance.error);

                ctx.callSetup();
                THEN("The info ostringstream must capture the string")
                {
                    CHECK(oss.str() == "[ERROR]\tError message\n");
                }
            }
        }
    }
}

SCENARIO("Test a mocked runtime context with a simple module instance with arguments", "[mock][RuntimeCtx]")
{
    class TestArgsModule : public BaseGeneric
    {
        public:
            elrond::string arg = "none";
            elrond::string called = "none";
            void setup(elrond::ContextP ctx)
            {
                this->called = "setup";
                this->arg = ctx->arguments()->asString("arg");
            }
    };

    GIVEN("A generic module instance")
    {
        auto ctx = RuntimeCtx::create<TestArgsModule>("test");

        WHEN("Calls the setup method without arguments")
        {
            auto& instance = reinterpret_cast<TestArgsModule&>(ctx.instance());
            REQUIRE(instance.called == "none");
            REQUIRE(instance.arg == "none");

            ctx.callSetup();
            THEN("Must be called the setup method")
            {
                CHECK(instance.called == "setup");
                CHECK(instance.arg == "");
            }
        }

        WHEN("Set a arguments set")
        {
            Arguments args;
            args.set("arg", "Hello world!!");
            ctx.arguments(args);

            REQUIRE(ctx.arguments().get() != &args);
            REQUIRE(ctx.arguments()->asString("arg") == "Hello world!!");

            WHEN("Calls the setup method")
            {
                auto& instance = reinterpret_cast<TestArgsModule&>(ctx.instance());
                REQUIRE(instance.called == "none");
                REQUIRE(instance.arg == "none");

                ctx.callSetup();

                THEN("Must be called the setup method")
                {
                    CHECK(instance.called == "setup");
                    CHECK(instance.arg == "Hello world!!");
                }
            }
        }
    }
}

SCENARIO("Test a mocked runtime context with a simple module instance for check loop control setup", "[mock][RuntimeCtx]")
{
    class TestLoopCfgModule : public BaseGeneric
    {
        public:
            void setup(elrond::ContextP ctx)
            {
                auto args = ctx->arguments();
                if (args->isBool("loop") && args->asBool("loop"))
                {
                    ctx->setLoopEvery(
                        elrond::milliseconds(
                            args->isInt("interval") ?
                            args->asInt("interval") : 1000
                        )
                    );
                }
            }
    };

    GIVEN("A generic module instance")
    {
        auto ctx = RuntimeCtx::create<TestLoopCfgModule>("test");

        REQUIRE_FALSE(ctx.loopEnable());
        REQUIRE(ctx.loopTs().count == 0);
        REQUIRE(ctx.loopTs().unit == elrond::TimeUnit::SECONDS);

        WHEN("Calls the setup method without arguments")
        {
            ctx.callSetup();

            THEN("Must be called the setup method")
            {
                CHECK_FALSE(ctx.loopEnable());
                REQUIRE(ctx.loopTs().count == 0);
                REQUIRE(ctx.loopTs().unit == elrond::TimeUnit::SECONDS);
            }
        }

        WHEN("Setup loop control by an arguments set and call setup method")
        {
            Arguments args;
            args.set("loop", true)
                .set("interval", 500);
            ctx.arguments(args);

            ctx.callSetup();

            THEN("Must be called the setup method")
            {
                CHECK(ctx.loopEnable());
                REQUIRE(ctx.loopTs().count == 500);
                REQUIRE(ctx.loopTs().unit == elrond::TimeUnit::MILLISECONDS);
            }
        }
    }
}

SCENARIO("Test a mocked runtime context with a simple external module", "[mock][RuntimeCtx]")
{
    GIVEN("A generic external module instance")
    {
        auto ctx = RuntimeCtx::create("test", TEST_BUILD_DIR + "dlobject/ExternalModule");

        REQUIRE(ctx.name() == "test");
        REQUIRE(isInstanceOf<BaseGeneric>(ctx.instance()));
        REQUIRE(ctx.instance().moduleType() == elrond::ModuleType::GENERIC);

        std::ostringstream oss;
        OStream stream(oss);
        ConsoleAdapter consoleAdapter(stream);
        ctx.console(consoleAdapter);

        WHEN("Calls the factory getter")
        {
            auto& factory = ctx.factory();
            THEN("Must return the expected adapter")
            {
                CHECK(factory.apiVersion() == elrond::getApiVersion());
                CHECK(factory.info().name == "External Test Module");
                CHECK(factory.info().author == "Edwino Stein");
                CHECK(factory.info().email== "edwino.stein@gmail.com");
                CHECK(factory.info().version == "1.0.0");
            }
        }

        WHEN("Module instance requires your context")
        {
            auto context = ctx.ctx();
            THEN("Must be the same context instance")
            {
                REQUIRE(isInstanceOf<RuntimeCtx::Context>(context.get()));
                REQUIRE(&(reinterpret_cast<RuntimeCtx::Context*>(context.get())->ctx) == &ctx);
            }
        }

        WHEN("Calls the setup method without arguments")
        {
            ctx.callSetup();
            THEN("Must be called the setup method")
            {
                CHECK(oss.str() == "setup");
            }
        }

        AND_WHEN("Calls the start method")
        {
            ctx.callStart();
            THEN("Must be called the start method")
            {
                CHECK(oss.str() == "start");
            }
        }

        AND_WHEN("Calls the loop method")
        {
            ctx.callLoop();
            THEN("Must be called the loop method")
            {
                CHECK(oss.str() == "loop");
            }
        }

        AND_WHEN("Calls the stop method")
        {
            ctx.callStop();
            THEN("Must be called the stop method")
            {
                CHECK(oss.str() == "stop");
            }
        }
    }
}
