#include <elrond_mock.hpp>
#include "catch2.hpp"
#include <cstdlib>
#include <ctime>

using elrond::mock::RuntimeCtx;
using elrond::interface::Module;
using elrond::module::BaseGeneric;
using elrond::mock::Console;
using elrond::mock::StringStream;

SCENARIO("Test a mocked runtime context with a simple module instance for lyfecycle methods", "[mock][RuntimeCtx]")
{
    class TestModule : public BaseGeneric
    {
        public:
            elrond::string called = "none";
            elrond::sizeT loops = 0;
            void setup() { this->called = "setup"; }
            void start() { this->called = "start"; }
            void stop() { this->called = "stop"; }
            void loop()
            {
                this->called = "loop";
                this->loops++;
            }
    };

    GIVEN("A generic module instance")
    {
        auto ctx = RuntimeCtx::create<TestModule>("test");
        REQUIRE(ctx.name() == "test");
        REQUIRE(instanceof<Module>(ctx.instance()));
        REQUIRE(ctx.instance().moduleType() == elrond::ModuleType::GENERIC);

        WHEN("Module instance requires your context")
        {
            auto& context = elrond::ctx(ctx.instance());    
            THEN("Must be the same context instance")
            {
                REQUIRE(&context == &ctx);
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
                REQUIRE(instance.loops == times);
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
            void setup()
            {
                auto& console = elrond::ctx(this).console();
                if(this->error) console.error("Error message");
                else console.info("Info message");
            }
    };

    GIVEN("A generic module instance")
    {
        auto ctx = RuntimeCtx::create<TestConsoleModule>("test");
        REQUIRE(ctx.name() == "test");
        REQUIRE(instanceof<Module>(ctx.instance()));
        REQUIRE(ctx.instance().moduleType() == elrond::ModuleType::GENERIC);

        WHEN("Calls console getter")
        {
            auto& console = ctx.console();
            THEN("Must be the default null console instance")
            {
                CHECK(&console == &(Console::null()));
            }
        }

        WHEN("Set a custom console instance")
        {
            StringStream info;
            StringStream error;
            Console console(
                [&info](elrond::StreamH h){ h(info); },
                [&error](elrond::StreamH h){ h(error); }
            );

            ctx.console(console);
            THEN("The context console instance must not be the null instance")
            {
                CHECK(&(ctx.console()) != &(Console::null()));
            }

            WHEN("The module instance calls console info method")
            {
                auto& instance = reinterpret_cast<TestConsoleModule&>(ctx.instance());
                REQUIRE((!instance.error));

                ctx.callSetup();
                THEN("The info StringStream must capture the string")
                {
                    CHECK(info.getString() == "Info message");
                    CHECK(error.getString() == "");
                }
            }

            WHEN("The module instance calls console error method")
            {
                auto& instance = reinterpret_cast<TestConsoleModule&>(ctx.instance());
                instance.error = true;
                REQUIRE((instance.error));

                ctx.callSetup();
                THEN("The info StringStream must capture the string")
                {
                    CHECK(info.getString() == "");
                    CHECK(error.getString() == "Error message");
                }
            }
        }
    }
}
