#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ExternalModuleTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::InputDriverTest;
using elrond::test::GpioTest;
using elrond::test::DebugOutTest;
using elrond::test::ConfigMapTest;

using elrond::module::Example;
using elrond::LoopControl;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("Example module metadata check")
{
    RuntimeTest::setAppInstance(nullptr);
    CHECK(Example::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(Example::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::Example"));
    CHECK(Example::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Example"));
    CHECK(Example::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(Example::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(Example::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("Runtime application for Elrond Test Library")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    Example inst;
    ConfigMapTest cfg;

    cfg.set("loop", true)
       .set("thread", false)
       .set("interval", 1000);

    CHECK_NOTHROW([&appt, &inst, &cfg](){

        LoopControl lc;
        int loops = 0;

        appt.init(inst, cfg, lc);

        CHECK(lc.enable == true);
        CHECK(lc.ownThread == false);
        CHECK(lc.interval == 1000);

        appt.start(
               inst,
               lc,
               [&loops](){ return loops++ < 1; }
            );
    }());
}

TEST_CASE("External module Test")
{
    EXPECT_ASSERTS(11);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 2);
    InputDriverTest input;
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK_N_COUNT(pin.getType() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(data == HIGH_VALUE);
            gpio.write((DOutPin&) pin, data);
        }
    );

    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout)
        .set(chm)
        .set(input)
        .set(gpio);

    REQUIRE_NOTHROW(
        [&appt, &input]()
        {
            ExternalModuleTest inst("./external_module.so", appt);

            CHECK_N_COUNT(inst.apiVer == ELROND_API_VERSION);
            CHECK_N_COUNT(inst.className == "ExternalMod");
            CHECK_N_COUNT(inst.prettyName == "External Module Test");
            CHECK_N_COUNT(inst.authorName == "Elrond Half-elven");
            CHECK_N_COUNT(inst.authorEmail == "elrond@rivendell.com");
            CHECK_N_COUNT(inst.version == ELROND_API_VERSION_STR);

            ConfigMapTest cfg;
            LoopControl lc;
            int loops = 0;

            appt.init(inst.getInstance(), cfg, lc);

            CHECK_N_COUNT(lc.enable == true);
            CHECK_N_COUNT(lc.ownThread == false);
            CHECK_N_COUNT(lc.interval == 1000);

            appt.start(
               inst.getInstance(),
               lc,
               [&loops, &input]()
               {
                   if(loops++ >= 1) return false;
                   input.trigger(0, HIGH_VALUE);
                   return true;
               }
            );

        }()
    );

    REQUIRE_ALL_DONE("Check if all tests are done");
}

#ifdef LINUX_PLATFORM
TEST_CASE("External module Test with header only library")
{
    EXPECT_ASSERTS(11);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 2);
    InputDriverTest input;
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK_N_COUNT(pin.getType() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(data == HIGH_VALUE);
            gpio.write((DOutPin&) pin, data);
        }
    );

    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout)
        .set(chm)
        .set(input)
        .set(gpio);

    REQUIRE_NOTHROW(
        [&appt, &input]()
        {
            ExternalModuleTest inst("./external_module_who.so", appt);

            CHECK_N_COUNT(inst.apiVer == ELROND_API_VERSION);
            CHECK_N_COUNT(inst.className == "ExternalMod");
            CHECK_N_COUNT(inst.prettyName == "External Module Test");
            CHECK_N_COUNT(inst.authorName == "Elrond Half-elven");
            CHECK_N_COUNT(inst.authorEmail == "elrond@rivendell.com");
            CHECK_N_COUNT(inst.version == ELROND_API_VERSION_STR);

            ConfigMapTest cfg;
            LoopControl lc;
            int loops = 0;

            appt.init(inst.getInstance(), cfg, lc);

            CHECK_N_COUNT(lc.enable == true);
            CHECK_N_COUNT(lc.ownThread == false);
            CHECK_N_COUNT(lc.interval == 1000);

            appt.start(
               inst.getInstance(),
               lc,
               [&loops, &input]()
               {
                   if(loops++ >= 1) return false;
                   input.trigger(0, HIGH_VALUE);
                   return true;
               }
            );

        }()
    );

    REQUIRE_ALL_DONE("Check if all tests are done");
}
#endif
