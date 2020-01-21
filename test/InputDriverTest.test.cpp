#include "elrond-test.hpp"

using elrond::test::InputDriverTest;
using elrond::test::RuntimeTest;

TEST_CASE("Input Driver for Elrond Test Library")
{
    RuntimeTest::setAppInstance(nullptr);

    InputDriverTest input;

    input.addInputListener(
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx){
            CHECK(data == 123);
        }
    );

    input.addInputListener(
        1,
        [](const elrond::word data, elrond::TaskContext* const ctx){
            CHECK(data == HIGH_VALUE);
        }
    );

    input.addInputListener(
        2,
        [](const elrond::word data, elrond::TaskContext* const ctx){
            CHECK(data == LOW_VALUE);
        }
    );

    input.trigger(0, 123);
    input.trigger(1, HIGH_VALUE);
    input.trigger(2, LOW_VALUE);
}
