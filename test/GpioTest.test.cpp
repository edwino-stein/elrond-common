#include "elrond-test.hpp"
#include "catch.hpp"

using elrond::test::RuntimeTest;
using elrond::test::GpioTest;
using elrond::gpio::BaseGpioPin;
using elrond::gpio::DOutPin;
using elrond::gpio::PwmPin;
using elrond::gpio::ServoPin;
using elrond::gpio::AInPin;

TEST_CASE("GPIO for Elrond Test Library")
{
    RuntimeTest::setAppInstance(nullptr);

    GpioTest gpio;

    auto dop = gpio.attachDOut(0);
    auto pwm = gpio.attachPwm(1);
    auto servo = gpio.attachServo(2);
    auto ain = gpio.attachAIn(3);

    dop.write(HIGH_VALUE);
    CHECK(dop.read() == HIGH_VALUE);

    dop.write(123);
    CHECK(dop.read() == HIGH_VALUE);

    dop.write(LOW_VALUE);
    CHECK(dop.read() == LOW_VALUE);

    pwm.write(HIGH_VALUE);
    CHECK(pwm.read() == HIGH_VALUE);

    pwm.write(123);
    CHECK(pwm.read() == 123);

    pwm.write(LOW_VALUE);
    CHECK(pwm.read() == LOW_VALUE);

    servo.write(HIGH_VALUE);
    CHECK(servo.read() == 180);

    servo.write(HIGH_VALUE/2 + 1);
    CHECK(servo.read() == 90);

    servo.write(LOW_VALUE);
    CHECK(servo.read() == 0);

    gpio.simulateAin(3, HIGH_VALUE);
    CHECK(ain.read() == HIGH_VALUE);

    gpio.simulateAin(3, LOW_VALUE);
    CHECK(ain.read() == LOW_VALUE);

    gpio.simulateAin(3, 123);
    CHECK(ain.read() == 123);
}
