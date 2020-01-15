#include "elrond-test.hpp"

using elrond::test::ChannelManagerTest;
using elrond::test::TransportTest;
using elrond::test::RuntimeTest;

TEST_CASE("Elrond Protocol")
{
    RuntimeTest::setAppInstance(nullptr);

    TransportTest selfTrans(
        [](elrond::byte data[], const elrond::sizeT length, TransportTest &me)
        {
            REQUIRE(length == ELROND_PROTOCOL_HEADER_SIZE + 2*ELROND_PROTOCOL_BYTES_PER_CHANNEL);
            REQUIRE(data[0] == ELROND_PROTOCOL_HEAD_BYTE_ACTION);
            REQUIRE(data[1] == 0);
            REQUIRE(data[2] == 0);
            REQUIRE(data[3] == 0);
            REQUIRE(data[4] == 0);
            REQUIRE(data[5] == 2);

            REQUIRE(data[6] == 0);
            REQUIRE(data[7] == elrond::highByte(123));
            REQUIRE(data[8] == elrond::lowByte(123));

            REQUIRE(data[9] == 1);
            REQUIRE(data[10] == elrond::highByte(0xABCD));
            REQUIRE(data[11] == elrond::lowByte(0xABCD));

            me.receive(data, length);
        }
    );
    ChannelManagerTest chm(selfTrans, 2, false);
    chm.init();

    chm.txTrigger(0, 123);
    chm.txTrigger(1, 0xABCD);
    chm.txSync();
}

TEST_CASE("Channel Manager for Elrond Test Library")
{
    RuntimeTest::setAppInstance(nullptr);

    TransportTest selfTrans;
    ChannelManagerTest chm(selfTrans, 3);
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
}
