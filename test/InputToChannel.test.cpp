#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::InputDriverTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMap;
using elrond::test::DebugOut;

using elrond::modules::InputToChannel;

TEST_CASE("Input to Channel module params test (no channel)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    InputToChannel inst;
    ConfigMap cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Input to Channel module params test (no input)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Input to Channel module params test (invalid channel manager)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("chm", 123)
       .set("input", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Input to Channel module params test (invalid input driver)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 1);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout)
        .set(chm);

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("chm", 0)
       .set("input", 0)
       .set("ins", 123);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Input to Channel module (normal)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    InputDriverTest input;
    TransportTest transport;
    ChannelManagerTest chm(transport, 1);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout)
        .set(input)
        .set(chm);

    chm.onRxReceive(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == HIGH_VALUE);
        }
    );

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("input", 0);

    CHECK_NOTHROW([&appt, &inst, &cfg, &input](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops, &input](){
                   if(loops++ >= 1) return false;
                   input.trigger(0, HIGH_VALUE);
                   return true;
               }
            );
    }());
}

TEST_CASE("Input to Channel module (inverted)")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    InputDriverTest input;
    TransportTest transport;
    ChannelManagerTest chm(transport, 1);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);
    appt.set(input);
    appt.set(chm);

    chm.onRxReceive(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == HIGH_VALUE);
        }
    );

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("input", 0)
       .set("inverted", true);

    CHECK_NOTHROW([&appt, &inst, &cfg, &input](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops, &input](){
                   if(loops++ >= 1) return false;
                   input.trigger(0, LOW_VALUE);
                   return true;
               }
            );
    }());
}
