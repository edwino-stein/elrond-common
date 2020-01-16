#include "elrond-test.hpp"

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
    InputDriverTest input;
    TransportTest transport;
    ChannelManagerTest chm(transport, 1);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);
    appt.set(input);
    appt.set(chm);

    chm.init();

    InputToChannel inst;
    ConfigMap cfg;

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops](){
                   return loops++ < 1;
               }
            );
    }());
}

TEST_CASE("Input to Channel module params test (no input)")
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

    chm.init();

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops](){
                   return loops++ < 1;
               }
            );
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

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops](){
                   return loops++ < 1;
               }
            );
    }());
}

TEST_CASE("Input to Channel module params test (invalid input driver)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 1);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    chm.init();

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("chm", 0)
       .set("input", 0)
       .set("ins", 123);

    REQUIRE_THROWS([&appt, &inst, &cfg](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops](){
                   return loops++ < 1;
               }
            );
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
    appt.set(dout);
    appt.set(input);
    appt.set(chm);

    chm.init();
    chm.onRxReceive(0, [](elrond::word data){
        REQUIRE(data == HIGH_VALUE);
    });

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("input", 0);

    REQUIRE_NOTHROW([&appt, &inst, &cfg, &input](){
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

    chm.init();
    chm.onRxReceive(0, [](elrond::word data){
        REQUIRE(data == HIGH_VALUE);
    });

    InputToChannel inst;
    ConfigMap cfg;

    cfg.set("channel", 0)
       .set("input", 0)
       .set("inverted", true);

    REQUIRE_NOTHROW([&appt, &inst, &cfg, &input](){
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
