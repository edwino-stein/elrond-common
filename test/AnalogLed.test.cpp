#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::DataLinkTest;
using elrond::test::ChannelManagerTest;
using elrond::test::TxChannelTest;
using elrond::test::ConfigMapTest;
using elrond::test::DebugOutTest;
using elrond::LoopControl;

using elrond::module::AnalogLed;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::PwmPin;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("[elrond::module::AnalogLed] Module metadata test")
{
    CHECK(AnalogLed::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(AnalogLed::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::AnalogLed"));
    CHECK(AnalogLed::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Analog LED"));
    CHECK(AnalogLed::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(AnalogLed::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(AnalogLed::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("[elrond::module::AnalogLed] Channel parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    RuntimeTest::setAppInstance(&appt);

    AnalogLed inst;
    ConfigMapTest cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::AnalogLed] Pin parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    RuntimeTest::setAppInstance(&appt);

    AnalogLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::AnalogLed] Invalid gpio test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    RuntimeTest::setAppInstance(&appt);

    AnalogLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::AnalogLed] Invalid channel manager test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio;
    RuntimeTest appt;

    appt.set(dout)
        .set(gpio);

    RuntimeTest::setAppInstance(&appt);

    AnalogLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 123);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::AnalogLed] Normal test")
{
    EXPECT_ASSERTS(2);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });

    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK_N_COUNT(pin.getType() == elrond::GpioType::PWM);
            CHECK_N_COUNT(data == HIGH_VALUE);
            gpio.write((PwmPin&) pin, data);
        }
    );

    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(dout)
        .set(gpio)
        .set(chm);

    RuntimeTest::setAppInstance(&appt);

    AnalogLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0);

    TxChannelTest tx(0, chm);

    CHECK_NOTHROW([&appt, &inst, &cfg, &tx](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
                inst,
                lc,
                [&loops, &tx](){
                    if(loops == 0) tx.trigger(HIGH_VALUE);
                    return loops++ < 1;
                }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::module::AnalogLed] With inverted parameter test")
{
    EXPECT_ASSERTS(2);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });

    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK_N_COUNT(pin.getType() == elrond::GpioType::PWM);
            CHECK_N_COUNT(data == LOW_VALUE);
            gpio.write((PwmPin&) pin, data);
        }
    );

    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(dout)
        .set(gpio)
        .set(chm);

    RuntimeTest::setAppInstance(&appt);

    AnalogLed inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0)
       .set("inverted", true);

    TxChannelTest tx(0, chm);

    CHECK_NOTHROW([&appt, &inst, &cfg, &tx](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
                inst,
                lc,
                [&loops, &tx](){
                    if(loops == 0) tx.trigger(HIGH_VALUE);
                    return loops++ < 1;
                }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}
