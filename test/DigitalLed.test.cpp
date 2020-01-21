#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMap;
using elrond::test::DebugOut;

using elrond::module::DigitalLed;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;
using elrond::LoopControl;

TEST_CASE("Digital LED module params test (no channel)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMap cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module params test (no pin)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module params test (invalid gpio)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Digital LED module params test (invalid channel manager)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio;
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio);

    DigitalLed inst;
    ConfigMap cfg;

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
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, const elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::DOUT);
            CHECK(data == HIGH_VALUE);
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

    chm.init();

    DigitalLed inst;
    ConfigMap cfg;

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
}

TEST_CASE("Digital LED module (inverted)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, const elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::DOUT);
            CHECK(data == LOW_VALUE);
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

    chm.init();

    DigitalLed inst;
    ConfigMap cfg;

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
}
