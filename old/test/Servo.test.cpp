#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::test::DataLinkTest;
using elrond::test::ChannelManagerTest;
using elrond::test::TxChannelTest;
using elrond::test::ConfigMapTest;

using elrond::module::Servo;
using elrond::gpio::BaseGpioPin;
using elrond::LoopControl;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("[elrond::module::Servo] Module metadata test")
{
    CHECK(Servo::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(Servo::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::Servo"));
    CHECK(Servo::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Servo"));
    CHECK(Servo::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(Servo::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(Servo::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("[elrond::module::Servo] Channel parameter missing test")
{
    RuntimeTest appt;
    Servo inst;
    ConfigMapTest cfg;

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::Servo] Pin parameter missing test")
{
    RuntimeTest appt;
    Servo inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::Servo] Invalid gpio test")
{
    RuntimeTest appt;
    Servo inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::Servo] Invalid channel manager test")
{
    GpioTest gpio;
    RuntimeTest appt;

    appt.set(gpio);

    Servo inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 123);

    CHECK_THROWS([&appt, &inst, &cfg](){
        LoopControl lc;
        appt.init(inst, cfg, lc);
    }());
}

TEST_CASE("[elrond::module::Servo] Normal test")
{
    EXPECT_ASSERTS(3);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::SERVO);
            CHECK_N_COUNT(pin.pin() == 0);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == elrond::high); }
    );
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(gpio)
        .set(chm);

    Servo inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0);

    TxChannelTest tx(0, chm);

    CHECK_NOTHROW([&appt, &inst, &cfg, &tx](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
                inst,
                lc,
                [&loops, &tx](){
                    if(loops == 0) tx.trigger(elrond::high);
                    return loops++ < 1;
                }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::module::Servo] With inverted parameter test")
{
    EXPECT_ASSERTS(3);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::SERVO);
            CHECK_N_COUNT(pin.pin() == 0);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == elrond::low); }
    );
    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 1);
    RuntimeTest appt;

    appt.set(gpio)
        .set(chm);

    Servo inst;
    ConfigMapTest cfg;

    cfg.set("channel", 0)
       .set("pin", 0)
       .set("chm", 0)
       .set("inverted", true);

    TxChannelTest tx(0, chm);

    CHECK_NOTHROW([&appt, &inst, &cfg, &tx](){
        LoopControl lc;
        int loops = 0;
        appt.init(inst, cfg, lc)
            .start(
                inst,
                lc,
                [&loops, &tx](){
                    if(loops == 0) tx.trigger(elrond::high);
                    return loops++ < 1;
                }
            );
    }());

    REQUIRE_ALL_DONE("Check if all tests are done");
}
