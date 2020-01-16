#include "elrond-test.hpp"

using elrond::test::RuntimeTest;
using elrond::test::ChannelManagerTest;
using elrond::test::DebugOut;

using elrond::modules::Loopback;

TEST_CASE("Loopback module")
{
    RuntimeTest::setAppInstance(nullptr);

    Loopback transport;
    ChannelManagerTest chm(transport, 3, false);
    chm.init();

    chm.onRxReceive(0, [](elrond::word data){
        REQUIRE(data == 123);
    });

    chm.onRxReceive(1, [](elrond::word data){
        REQUIRE(data == 0xAB00);
    });

    chm.onRxReceive(2, [](elrond::word data){
        REQUIRE(data == 0x00CD);
    });

    chm.txTrigger(0, 123);
    chm.txTrigger(1, 0xAB00);
    chm.txTrigger(2, 0x00CD);

    chm.txSync();
}
