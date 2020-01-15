#include "elrond-test.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMap;
using elrond::test::DebugOut;

using elrond::modules::DigitalLed;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;

TEST_CASE("Digital LED module params test (no channel)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    RuntimeTest::setAppInstance(&appt);

    appt.set(dout);

    DigitalLed inst;
    ConfigMap cfg;

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
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

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
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

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
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

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Digital LED module (normal)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        true,
        [](BaseGpioPin& pin, elrond::word data, GpioTest& me){
            CHECK(pin.getType() == elrond::GpioType::DOUT);
            CHECK(data == HIGH_VALUE);
            me.write((DOutPin&) pin, data);
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

TEST_CASE("Digital LED module (inverted)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    GpioTest gpio(
        true,
        [](BaseGpioPin& pin, elrond::word data, GpioTest& me){
            CHECK(pin.getType() == elrond::GpioType::DOUT);
            CHECK(data == LOW_VALUE);
            me.write((DOutPin&) pin, data);
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
