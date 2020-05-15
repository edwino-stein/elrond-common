#include "elrond_test.hpp"
#include "lib/elrond_catch.hpp"

TEST_CASE("Bitwise functions")
{
    CHECK(elrond::highByte(0xABCD) == 0xAB);
    CHECK(elrond::highByte(0xCD) == 0x00);
    CHECK(elrond::lowByte(0xABCD) == 0xCD);
    CHECK(elrond::lowByte(0xABCD) == 0xCD);
    CHECK(elrond::makeWord(0xAB, 0xCD) == 0xABCD);

    CHECK(elrond::highWord(0x1234ABCD) == 0x1234);
    CHECK(elrond::lowWord(0x1234ABCD) == 0xABCD);
    CHECK(elrond::makeDWord(0x1234, 0xABCD) == 0x1234ABCD);
}

TEST_CASE("Math functions")
{
    CHECK(elrond::abs(-1) == 1);
    CHECK(elrond::abs(1) == 1);
    CHECK(elrond::abs(0) == 0);
    CHECK(elrond::mod(123.456) == Approx(0.456));

    CHECK(elrond::map(0, 0, 100, LOW_VALUE, HIGH_VALUE) == LOW_VALUE);
    CHECK(elrond::map(100, 0, 100, LOW_VALUE, HIGH_VALUE) == HIGH_VALUE);
    CHECK(elrond::map(50, 0, 100, LOW_VALUE, HIGH_VALUE) == (elrond::int32) (HIGH_VALUE * 0.5));

    int a = 10, b = 20;
    elrond::swap<int>(a, b);
    CHECK(a == 20);
    CHECK(b == 10);

    double c = 123.456, d = 3.14;
    elrond::swap<double>(c, d);
    CHECK(c == Approx(3.14));
    CHECK(d == Approx(123.456));

    elrond::String e = "hello", f = "world";
    elrond::swap<elrond::String>(e, f);
    CHECK(e == "world");
    CHECK(f == "hello");
}

TEST_CASE("Time functions")
{
    auto nowMs = elrond::millis();
    elrond::delay(100);
    CHECK(elrond::millis() >= nowMs + 100);

    auto nowUs = elrond::micros();
    elrond::delayMicroseconds(100);
    CHECK(elrond::micros() >= nowUs + 100);
}

TEST_CASE("Object type check functions")
{
    elrond::Example inst;
    elrond::module::BaseModule *pointer = &inst;

    CHECK(elrond::test::instanceOf<elrond::Example>(pointer));
    CHECK_FALSE(elrond::test::instanceOf<elrond::Loopback>(pointer));

    CHECK(elrond::test::baseOf<elrond::module::BaseModule>(&inst));
    CHECK_FALSE(elrond::test::baseOf<elrond::module::BaseDataLinkModule>(&inst));
}
