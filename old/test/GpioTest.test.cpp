#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

using elrond::test::GpioTest;
using elrond::gpio::BaseGpioPin;
using elrond::test::DOutPinTest;
using elrond::test::PwmPinTest;
using elrond::test::ServoPinTest;
using elrond::test::AInPinTest;
using elrond::test::DInPDPinTest;
using elrond::test::DInPUPinTest;

TEST_CASE("[elrond::test::GpioTest] elrond::test::DOutPinTest test")
{
    EXPECT_ASSERTS(4);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::DOUT);
            CHECK_N_COUNT(pin.pin() == 0);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == elrond::high); }
    );

    DOutPinTest pin(0, gpio);
    pin.write(12345);
    CHECK_N_COUNT(pin.read() == elrond::high);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::GpioTest] elrond::test::PwmPinTest test")
{
    EXPECT_ASSERTS(4);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::PWM);
            CHECK_N_COUNT(pin.pin() == 1);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == 12345); }
    );

    PwmPinTest pin(1, gpio);

    pin.write(12345);
    CHECK_N_COUNT(pin.read() == 12345);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::GpioTest] elrond::test::ServoPinTest test")
{
    EXPECT_ASSERTS(4);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::SERVO);
            CHECK_N_COUNT(pin.pin() == 2);
        },
        [](BaseGpioPin& pin, const elrond::word data)
        { CHECK_N_COUNT(data == 12345); }
    );

    ServoPinTest pin(2, gpio);

    pin.write(12345);
    CHECK_N_COUNT(pin.read() == 12345);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::GpioTest] elrond::test::AInPinTest test")
{
    EXPECT_ASSERTS(3);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::AIN);
            CHECK_N_COUNT(pin.pin() == 3);
        }
    );

    AInPinTest pin(3, gpio);
    gpio.simulateInput(pin, 12345);
    CHECK_N_COUNT(pin.read() == 12345);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::GpioTest] elrond::test::DInPDPinTest test")
{
    EXPECT_ASSERTS(3);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::DIN_PD);
            CHECK_N_COUNT(pin.pin() == 4);
        }
    );

    DInPDPinTest pin(4, gpio);
    gpio.simulateInput(pin, 12345);
    CHECK_N_COUNT(pin.read() == elrond::high);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::GpioTest] elrond::test::DInPUPinTest test")
{
    EXPECT_ASSERTS(3);

    GpioTest gpio(
        [](BaseGpioPin& pin)
        {
            CHECK_N_COUNT(pin.type() == elrond::GpioType::DIN_PU);
            CHECK_N_COUNT(pin.pin() == 5);
        }
    );

    DInPUPinTest pin(5, gpio);
    gpio.simulateInput(pin, 12345);
    CHECK_N_COUNT(pin.read() == elrond::low);

    REQUIRE_ALL_DONE("Check if all tests are done");
}

TEST_CASE("[elrond::test::GpioTest] All pin types test")
{
    GpioTest gpio;

    DOutPinTest dop(0, gpio);
    PwmPinTest pwm(1, gpio);
    ServoPinTest servo(2, gpio);
    AInPinTest aip(3, gpio);
    DInPDPinTest dipdp(4, gpio);
    DInPUPinTest dipup(5, gpio);

    dop.write(12345);
    pwm.write(elrond::high - 12345);
    servo.write(54321);
    gpio.simulateInput(aip, 0xABCD);
    gpio.simulateInput(dipdp, 0xCDBA);
    gpio.simulateInput(dipup, 0xCDBA);

    CHECK(dop.read() == elrond::high);
    CHECK(pwm.read() == elrond::high - 12345);
    CHECK(servo.read() == 54321);
    CHECK(aip.read() == 0xABCD);
    CHECK(dipdp.read() == elrond::high);
    CHECK(dipup.read() == elrond::low);
}
