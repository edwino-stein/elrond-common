#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMap;
using elrond::test::DebugOut;

using elrond::modules::Servo;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::ServoPin;

TEST_CASE("Servo module params test (no channel)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    Servo inst;
    ConfigMap cfg;

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Servo module params test (no pin)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    Servo inst;
    ConfigMap cfg;

    cfg.set("channel", 0);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Servo module params test (invalid gpio)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    Servo inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Servo module params test (invalid channel manager)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio;
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout)
        .set(gpio);

    Servo inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 123);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Servo module (normal)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, const elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::SERVO);
            CHECK(data == HIGH_VALUE);
            gpio.write((ServoPin&) pin, data);
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

    Servo inst;
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

TEST_CASE("Servo module (inverted)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        [&gpio](BaseGpioPin& pin, const elrond::word data){
            CHECK(pin.getType() == elrond::GpioType::SERVO);
            CHECK(data == LOW_VALUE);
            gpio.write((ServoPin&) pin, data);
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

    Servo inst;
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
