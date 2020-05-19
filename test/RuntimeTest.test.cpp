#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ExternalModuleTest;
using elrond::test::DataLinkTest;
using elrond::test::ChannelManagerTest;
using elrond::test::InputTest;
using elrond::test::InputTriggerTest;
using elrond::test::GpioTest;
using elrond::test::DebugOutTest;
using elrond::test::ConfigMapTest;

using elrond::module::Example;
using elrond::LoopControl;
using elrond::gpio::BaseGpioPin;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("[elrond::module::Example] Module metadata test")
{
    CHECK(Example::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(Example::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::Example"));
    CHECK(Example::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Example"));
    CHECK(Example::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(Example::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(Example::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("[elrond::module::Example] Normal test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
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

TEST_CASE("[elrond::test::ExternalModuleTest] Loading \"external_module\" test")
{
    EXPECT_ASSERTS(12);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 2);
    InputTest input;

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(pin.pin() == 0);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == elrond::high); }
    );

    RuntimeTest appt;

    appt.set(dout)
        .set(chm)
        .set(input)
        .set(gpio);

    InputTriggerTest key(0, input);

    REQUIRE_NOTHROW(
        [&appt, &key]()
        {
            ExternalModuleTest inst("external_module", appt);

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
               [&loops, &key]()
               {
                   if(loops == 0) key.trigger(elrond::high);
                   return loops++ < 1;
               }
            );

        }()
    );

    REQUIRE_ALL_DONE("Check if all tests are done");
}

#ifdef LINUX_PLATFORM
TEST_CASE("[elrond::test::ExternalModuleTest] Loading \"external_module_who\" test")
{
    EXPECT_ASSERTS(12);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 2);
    InputTest input;
    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(pin.pin() == 0);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == elrond::high); }
    );

    RuntimeTest appt;

    appt.set(dout)
        .set(chm)
        .set(input)
        .set(gpio);

    InputTriggerTest key(0, input);

    REQUIRE_NOTHROW(
        [&appt, &key]()
        {
            ExternalModuleTest inst("external_module_who", appt);

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
               [&loops, &key]()
               {
                   if(loops == 0) key.trigger(elrond::high);
                   return loops++ < 1;
               }
            );

        }()
    );

    REQUIRE_ALL_DONE("Check if all tests are done");
}
#endif
