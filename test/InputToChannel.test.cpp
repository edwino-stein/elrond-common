#include "elrond-test.hpp"
#include "elrond-catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::InputDriverTest;
using elrond::test::TransportTest;
using elrond::test::ChannelManagerTest;
using elrond::test::ConfigMapTest;
using elrond::test::DebugOutTest;

using elrond::module::InputToChannel;
using elrond::LoopControl;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("Input to Channel module metadata check")
{
    RuntimeTest::setAppInstance(nullptr);
    CHECK(InputToChannel::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(InputToChannel::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::InputToChannel"));
    CHECK(InputToChannel::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Input to Channel"));
    CHECK(InputToChannel::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(InputToChannel::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(InputToChannel::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("Input to Channel module params test (no channel)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    InputToChannel inst;
    ConfigMapTest cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Input to Channel module params test (no input)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("Input to Channel module params test (invalid channel manager)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
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

TEST_CASE("Input to Channel module params test (invalid input driver)")
{
    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    TransportTest transport;
    ChannelManagerTest chm(transport, 1);
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
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

TEST_CASE("Input to Channel module (normal)")
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
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
            CHECK_N_COUNT(data == HIGH_VALUE);
        }
    );

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("input", 0);

    CHECK_NOTHROW([&appt, &inst, &cfg, &input](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
               inst,
               lc,
               [&loops, &input](){
                   if(loops++ >= 1) return false;
                   input.trigger(0, HIGH_VALUE);
                   return true;
               }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("Input to Channel module (inverted)")
{
    EXPECT_ASSERTS(1);

    DebugOutTest dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
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
            CHECK_N_COUNT(data == HIGH_VALUE);
        }
    );

    InputToChannel inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("input", 0)
       .set("inverted", true);

    CHECK_NOTHROW([&appt, &inst, &cfg, &input](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
               inst,
               lc,
               [&loops, &input](){
                   if(loops++ >= 1) return false;
                   input.trigger(0, LOW_VALUE);
                   return true;
               }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}
