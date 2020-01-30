#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ExternalModuleTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::InputDriverTest;
using elrond::test::GpioTest;
using elrond::test::DebugOut;
using elrond::test::ConfigMap;

using elrond::module::Example;
using elrond::LoopControl;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("Example module metadata check")
{
    RuntimeTest::setAppInstance(nullptr);
    CHECK(Example::ELROND_MOD_API_VER_FUNC_N() == elrond::makeDWord(ELROND_API_VERSION, ELROND_API_REVISION));
    CHECK(Example::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::Example"));
    CHECK(Example::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Example"));
    CHECK(Example::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(Example::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(Example::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_TO_STR_CONCAT(ELROND_API_VERSION.ELROND_API_REVISION-ELROND_API_DEVSTATE)));
}
#endif

TEST_CASE("Runtime application for Elrond Test Library")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    Example inst;
    ConfigMap cfg;

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
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 2);
    InputDriverTest input;
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::DOUT);
            CHECK(data == HIGH_VALUE);
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
            ExternalModuleTest inst("build/test/external-module.so", appt);

            CHECK(inst.apiVer == elrond::makeDWord(ELROND_API_VERSION, ELROND_API_REVISION));
            CHECK(inst.className == "ExternalMod");
            CHECK(inst.prettyName == "External Module Test");
            CHECK(inst.authorName == "Elrond Half-elven");
            CHECK(inst.authorEmail == "elrond@rivendell.com");
            CHECK(inst.version == ELROND_TO_STR_CONCAT(ELROND_API_VERSION.ELROND_API_REVISION-ELROND_API_DEVSTATE));

            ConfigMap cfg;
            LoopControl lc;
            int loops = 0;

            appt.init(inst.getInstance(), cfg, lc);

            CHECK(lc.enable == true);
            CHECK(lc.ownThread == false);
            CHECK(lc.interval == 1000);

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
}
