#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::InputTest;
using elrond::test::InputTriggerTest;
using elrond::test::DataLinkTest;
using elrond::test::ChannelManagerTest;
using elrond::test::RxChannelTest;
using elrond::test::ConfigMapTest;
using elrond::test::DebugOutTest;

using elrond::module::InputToChannel;
using elrond::LoopControl;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("[elrond::module::InputToChannel] Module metadata test")
{
    CHECK(InputToChannel::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(InputToChannel::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::InputToChannel"));
    CHECK(InputToChannel::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Input to Channel"));
    CHECK(InputToChannel::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(InputToChannel::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(InputToChannel::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("[elrond::module::InputToChannel] Channel parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    InputToChannel inst;
    ConfigMapTest cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::InputToChannel] Input parameter missing test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::InputToChannel] Invalid channel manager test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;
    appt.set(dout);

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("chm", 123)
       .set("input", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::InputToChannel] Invalid input driver test")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(dout)
        .set(chm);

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("chm", 0)
       .set("input", 0)
       .set("ins", 123);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::InputToChannel] Normal test")
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    InputTest input;
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(dout)
        .set(input)
        .set(chm);

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("input", 0);

    InputTriggerTest key(0, input);

    RxChannelTest rx(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == elrond::high); },
        chm
    );

    CHECK_NOTHROW([&appt, &inst, &cfg, &key](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
               inst,
               lc,
               [&loops, &key](){
                   if(loops == 0) key.trigger(elrond::high);
                   return loops++ < 1;
               }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::module::InputToChannel] With inverted parameter test")
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    InputTest input;
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(dout)
        .set(input)
        .set(chm);

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("input", 0)
       .set("inverted", true);

    InputTriggerTest key(0, input);

    RxChannelTest rx(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == elrond::high); },
        chm
    );

    CHECK_NOTHROW([&appt, &inst, &cfg, &key](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
               inst,
               lc,
               [&loops, &key](){
                   if(loops == 0) key.trigger(elrond::low);
                   return loops++ < 1;
               }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}
