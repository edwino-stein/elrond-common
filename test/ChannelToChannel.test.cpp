#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ChannelManagerTest;
using elrond::test::TxChannelTest;
using elrond::test::RxChannelTest;
using elrond::test::DataLinkTest;
using elrond::test::ConfigMapTest;
using elrond::test::DebugOutTest;
using elrond::LoopControl;

using elrond::module::ChannelToChannel;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("[elrond::module::ChannelToChannel] Module metadata test")
{
    CHECK(ChannelToChannel::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(ChannelToChannel::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::ChannelToChannel"));
    CHECK(ChannelToChannel::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Channel to Channel"));
    CHECK(ChannelToChannel::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(ChannelToChannel::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(ChannelToChannel::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("[elrond::module::ChannelToChannel] TxCh parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::ChannelToChannel] TxChm parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    cfg.set("txCh", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::ChannelToChannel] RxCh parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    cfg.set("txCh", 0)
       .set("txChm", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::ChannelToChannel] RxChm parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    cfg.set("txCh", 0)
       .set("txChm", 0)
       .set("rxCh", 1);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::ChannelToChannel] Invalid channel manager test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    cfg.set("txCh", 0)
       .set("txChm", 0)
       .set("rxCh", 1)
       .set("rxChm", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::ChannelToChannel] Normal test")
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 3);
    RuntimeTest appt;

    appt.set(dout)
        .set(chm);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    cfg.set("txCh", 1)
       .set("txChm", 0)
       .set("rxCh", 0)
       .set("rxChm", 0);

    RxChannelTest rx(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == HIGH_VALUE); },
        chm
    );

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
                    return loops++ <= 1;
                }
            );

    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::module::ChannelToChannel] With inverted parameter test")
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 2);
    RuntimeTest appt;

    appt.set(dout)
        .set(chm);

    ChannelToChannel inst;
    ConfigMapTest cfg;

    cfg.set("txCh", 1)
       .set("txChm", 0)
       .set("rxCh", 0)
       .set("rxChm", 0)
       .set("inverted", true);

    RxChannelTest rx(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == HIGH_VALUE - 123); },
        chm
    );

    TxChannelTest tx(0, chm);

    CHECK_NOTHROW([&appt, &inst, &cfg, &tx](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
               inst,
               lc,
               [&loops, &tx](){
                   if(loops == 0) tx.trigger(123);
                   return loops++ <= 1;
               }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}
