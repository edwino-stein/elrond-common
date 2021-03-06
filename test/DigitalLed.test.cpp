#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMapTest;
using elrond::test::DebugOutTest;

using elrond::module::DigitalLed;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;
using elrond::LoopControl;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("Digital LED module metadata check")
{
    RuntimeTest::setAppInstance(nullptr);
    CHECK(DigitalLed::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(DigitalLed::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::DigitalLed"));
    CHECK(DigitalLed::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Digital LED"));
    CHECK(DigitalLed::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(DigitalLed::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(DigitalLed::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("Digital LED module params test (no channel)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMapTest cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module params test (no pin)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module params test (invalid gpio)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module params test (invalid channel manager)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio;
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio);

    DigitalLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 123);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module (normal)")
{
    EXPECT_ASSERTS(2);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, const elrond::word data)
        {
            CHECK_N_COUNT(pin.getType() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(data == HIGH_VALUE);
            gpio.write((DOutPin&) pin, data);
        }
    );

    TransportTest transport;
    ChannelManagerTest chm(transport, 1);

    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio)
        .set(chm);

    DigitalLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0);

    CHECK_NOTHROW([&appt, &inst, &cfg, &chm](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
                inst,
                lc,
                [&loops, &chm](){
                    if(loops++ >= 1) return false;
                    chm.txTrigger(0, HIGH_VALUE);
                    return true;
                }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("Digital LED module (inverted)")
{
    EXPECT_ASSERTS(2);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, const elrond::word data)
        {
            CHECK_N_COUNT(pin.getType() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(data == LOW_VALUE);
            gpio.write((DOutPin&) pin, data);
        }
    );

    TransportTest transport;
    ChannelManagerTest chm(transport, 1);

    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio)
        .set(chm);

    DigitalLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0)
       .set("inverted", true);

    CHECK_NOTHROW([&appt, &inst, &cfg, &chm](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
                inst,
                lc,
                [&loops, &chm](){
                    if(loops++ >= 1) return false;
                    chm.txTrigger(0, HIGH_VALUE);
                    return true;
                }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}
