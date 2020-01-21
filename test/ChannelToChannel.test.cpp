#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMap;
using elrond::test::DebugOut;

using elrond::modules::ChannelToChannel;

TEST_CASE("Channel to Channel module params test (no txCh)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMap cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Channel to Channel module params test (no txChm)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMap cfg;

    cfg.set("txCh", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Channel to Channel module params test (no rxCh)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMap cfg;

    cfg.set("txCh", 0)
       .set("txChm", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Channel to Channel module params test (no rxChm)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMap cfg;

    cfg.set("txCh", 0)
       .set("txChm", 0)
       .set("rxCh", 1);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Channel to Channel module params test (invalid channel manager)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMap cfg;

    cfg.set("txCh", 0)
       .set("txChm", 0)
       .set("rxCh", 1)
       .set("rxChm", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        appt.init(inst, cfg);
    }());
}

TEST_CASE("Channel to Channel module (normal)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 2);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);
    appt.set(chm);

    chm.onRxReceive(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == HIGH_VALUE);
        }
    );

    ChannelToChannel inst;
    ConfigMap cfg;

    cfg.set("txCh", 1)
       .set("txChm", 0)
       .set("rxCh", 0)
       .set("rxChm", 0);

    CHECK_NOTHROW([&appt, &inst, &cfg, &chm](){
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

TEST_CASE("Channel to Channel module (inverted)")
{

    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 2);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);
    appt.set(chm);

    chm.onRxReceive(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == HIGH_VALUE - 123);
        }
    );

    ChannelToChannel inst;
    ConfigMap cfg;

    cfg.set("txCh", 1)
       .set("txChm", 0)
       .set("rxCh", 0)
       .set("rxChm", 0)
       .set("inverted", true);

    CHECK_NOTHROW([&appt, &inst, &cfg, &chm](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops, &chm](){
                   if(loops++ >= 1) return false;
                   chm.txTrigger(0, 123);
                   return true;
               }
            );
    }());
}
