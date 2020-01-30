#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ChannelManagerTest;
using elrond::test::DebugOut;

using elrond::module::Loopback;

#ifdef ELROND_WITH_MODULES_INFO
TEST_CASE("Loopback module metadata check")
{
    RuntimeTest::setAppInstance(nullptr);
    CHECK(Loopback::ELROND_MOD_API_VER_FUNC_N() == elrond::makeDWord(ELROND_API_VERSION, ELROND_API_REVISION));
    CHECK(Loopback::ELROND_MOD_MAIN_CLASS_FUNC_N() == elrond::String("elrond::Loopback"));
    CHECK(Loopback::ELROND_MOD_PRETTY_NAME_FUNC_N() == elrond::String("Loopback Transport"));
    CHECK(Loopback::ELROND_MOD_AUTHOR_NAME_FUNC_N() == elrond::String("Edwino Stein"));
    CHECK(Loopback::ELROND_MOD_AUTHOR_EMAIL_FUNC_N() == elrond::String("edwino.stein@gmail.com"));
    CHECK(Loopback::ELROND_MOD_VERSION_FUNC_N() == elrond::String(ELROND_TO_STR_CONCAT(ELROND_API_VERSION.ELROND_API_REVISION-ELROND_API_DEVSTATE)));
}
#endif

TEST_CASE("Loopback module")
{
    RuntimeTest::setAppInstance(nullptr);

    Loopback transport;
    ChannelManagerTest chm(transport, 3, false);

    chm.onRxReceive(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == 123);
        }
    );

    chm.onRxReceive(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == 0xAB00);
        }
    );

    chm.onRxReceive(
        2,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            CHECK(data == 0x00CD);
        }
    );

    chm.txTrigger(0, 123);
    chm.txTrigger(1, 0xAB00);
    chm.txTrigger(2, 0x00CD);
    chm.txSync();
}
