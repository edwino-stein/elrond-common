#include "elrond-test.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMap;
using elrond::test::DebugOut;

using elrond::modules::AnalogLed;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::PwmPin;

TEST_CASE("Analog LED module params test (no channel)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    AnalogLed inst;
    ConfigMap cfg;

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Analog LED module params test (no pin)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    AnalogLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Analog LED module params test (invalid gpio)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    AnalogLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Analog LED module params test (invalid channel manager)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio;
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio);

    AnalogLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 123);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Analog LED module (normal)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::PWM);
            CHECK(data == HIGH_VALUE);
            gpio.write((PwmPin&) pin, data);
        }
    );

    TransportTest transport;
    ChannelManagerTest chm(transport, 1);

    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio)
        .set(chm);

    chm.init();

    AnalogLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0);

    REQUIRE_NOTHROW([&appt, &inst, &cfg, &chm](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
                inst,
                [&loops, &chm](){
                    if(loops++ >= 1) return false;
                    chm.txTrigger(0, HIGH_VALUE);
                    return true;
                }
            );
    }());
}

TEST_CASE("Analog LED module (inverted)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::PWM);
            CHECK(data == LOW_VALUE);
            gpio.write((PwmPin&) pin, data);
        }
    );

    TransportTest transport;
    ChannelManagerTest chm(transport, 1);

    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio)
        .set(chm);

    chm.init();

    AnalogLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0)
       .set("inverted", true);

    REQUIRE_NOTHROW([&appt, &inst, &cfg, &chm](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
                inst,
                [&loops, &chm](){
                    if(loops++ >= 1) return false;
                    chm.txTrigger(0, HIGH_VALUE);
                    return true;
                }
            );
    }());
}
