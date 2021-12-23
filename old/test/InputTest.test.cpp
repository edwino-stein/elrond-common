#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::InputTest;
using elrond::test::InputTriggerTest;
using elrond::test::InputListenerTest;

TEST_CASE("[elrond::test::InputTest] Trigger and listener test")
{
    EXPECT_ASSERTS(4);

    InputTest input;

    InputListenerTest listenerKey0(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == 123); },
        input
    );

    InputListenerTest listenerKey1(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == elrond::high); },
        input
    );

    InputListenerTest listenerKey2(
        2,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == elrond::low); },
        input
    );

    InputListenerTest otherListenerKey0(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { CHECK_N_COUNT(data == 123); },
        input
    );

    InputTriggerTest key0(0, input);
    InputTriggerTest key1(1, input);
    InputTriggerTest key2(2, input);

    key0.trigger(123);
    key1.trigger(elrond::high);
    key2.trigger(elrond::low);

    REQUIRE_ALL_DONE("Check if all tests are done");
}
