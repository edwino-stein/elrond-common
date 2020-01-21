#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::ChannelManagerTest;
using elrond::test::TransportTest;
using elrond::test::RuntimeTest;

TEST_CASE("Elrond Protocol")
{
    RuntimeTest::setAppInstance(nullptr);

    TransportTest selfTrans(
        [](elrond::byte data[], const elrond::sizeT length, TransportTest &me)
        {
            CHECK(length == ELROND_PROTOCOL_HEADER_SIZE + 2*ELROND_PROTOCOL_BYTES_PER_CHANNEL);
            CHECK(data[0] == ELROND_PROTOCOL_HEAD_BYTE_ACTION);
            CHECK(data[1] == 0);
            CHECK(data[2] == 0);
            CHECK(data[3] == 0);
            CHECK(data[4] == 0);
            CHECK(data[5] == 2);

            CHECK(data[6] == 0);
            CHECK(data[7] == elrond::highByte(123));
            CHECK(data[8] == elrond::lowByte(123));

            CHECK(data[9] == 1);
            CHECK(data[10] == elrond::highByte(0xABCD));
            CHECK(data[11] == elrond::lowByte(0xABCD));

            me.receive(data, length);
        }
    );
    ChannelManagerTest chm(selfTrans, 2, false);

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
}
