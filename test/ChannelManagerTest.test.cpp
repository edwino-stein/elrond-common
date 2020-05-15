#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::ChannelManagerTest;
using elrond::test::RxChannelTest;
using elrond::test::TxChannelTest;
using elrond::test::DataLinkTest;
using elrond::test::RuntimeTest;

TEST_CASE("[elrond::test::RxChannelTest] Direct trigger test")
{
    EXPECT_ASSERTS(1);

    RxChannelTest rxCh(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == HIGH_VALUE); }
    );

    rxCh.trigger(HIGH_VALUE);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::DataLinkTest] Elrond Protocol tests")
{
    EXPECT_ASSERTS(2*13);

    auto dlCallback = [](elrond::byte data[], const elrond::sizeT length)
    {
        CHECK_N_COUNT(length == ELROND_PROTOCOL_HEADER_SIZE + 2*ELROND_PROTOCOL_BYTES_PER_CHANNEL);
        CHECK_N_COUNT(data[0] == ELROND_PROTOCOL_HEAD_BYTE_ACTION);
        CHECK_N_COUNT(data[1] == 0);
        CHECK_N_COUNT(data[2] == 0);
        CHECK_N_COUNT(data[3] == 0);
        CHECK_N_COUNT(data[4] == 0);
        CHECK_N_COUNT(data[5] == 2);

        CHECK_N_COUNT(data[6] == 0);
        CHECK_N_COUNT(data[7] == elrond::highByte(123));
        CHECK_N_COUNT(data[8] == elrond::lowByte(123));

        CHECK_N_COUNT(data[9] == 1);
        CHECK_N_COUNT(data[10] == elrond::highByte(0xABCD));
        CHECK_N_COUNT(data[11] == elrond::lowByte(0xABCD));

        return true;
    };

    DataLinkTest dataLink(dlCallback, dlCallback);
    ChannelManagerTest chm(dataLink, 2);

    TxChannelTest tx0(0, chm);
    TxChannelTest tx1(1, chm);

    tx0.trigger(123);
    tx1.trigger(0xABCD);
    chm.txSync();

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::ChannelManagerTest] Normal RX and TX channels tests")
{
    EXPECT_ASSERTS(3);

    DataLinkTest dataLink;
    ChannelManagerTest chm(dataLink, 3);

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
