#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ChannelManagerTest;
using elrond::test::RxChannelTest;
using elrond::test::TxChannelTest;

using elrond::module::Loopback;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("[elrond::module::Loopback] Module metadata test")
{
    CHECK(Loopback::ELROND_MOD_API_VER_FUNC_N() == ELROND_API_VERSION);
    CHECK(Loopback::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::Loopback"));
    CHECK(Loopback::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Loopback Transport"));
    CHECK(Loopback::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(Loopback::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(Loopback::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_API_VERSION_STR));
}
#endif

TEST_CASE("[elrond::module::Loopback] Normal test")
{
    EXPECT_ASSERTS(3);

    Loopback inst;
    ChannelManagerTest chm(inst, 3);

    RxChannelTest rx0(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == 123); },
        chm
    );

    RxChannelTest rx1(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == 0xAB00); },
        chm
    );

    RxChannelTest rx2(
        2,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == 0x00CD); },
        chm
    );

    TxChannelTest tx0(0, chm);
    TxChannelTest tx1(1, chm);
    TxChannelTest tx2(2, chm);

    tx0.trigger(123);
    tx1.trigger(0xAB00);
    tx2.trigger(0x00CD);

    chm.txSync();

    REQUIRE_ALL_DONE("Check if all tests are done");
}
