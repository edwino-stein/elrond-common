#include <elrond.hpp>
#include "catch2.hpp"

TEST_CASE("Check create a timespan using elrond::seconds() function", "[timespan]")
{
    auto ts = elrond::seconds(1);
    CHECK(ts.count == 1);
    CHECK(ts.unit == elrond::TimeUnit::SECONDS);
}

TEST_CASE("Check create a timespan using elrond::miliseconds() function", "[timespan]")
{
    auto ts = elrond::milliseconds(1);
    CHECK(ts.count == 1);
    CHECK(ts.unit == elrond::TimeUnit::MILLISECONDS);
}

TEST_CASE("Check create a timespan using elrond::microseconds() function", "[timespan]")
{
    auto ts = elrond::microseconds(1);
    CHECK(ts.count == 1);
    CHECK(ts.unit == elrond::TimeUnit::MICROSECONDS);
}

TEST_CASE("Check converting timespans from seconds", "[timespan]")
{
    auto s = elrond::seconds(30);

    auto ms = elrond::milliseconds(s);
    CHECK(ms.count == 30000);
    CHECK(ms.unit == elrond::TimeUnit::MILLISECONDS);

    auto us = elrond::microseconds(s);
    CHECK(us.count == 30000000);
    CHECK(us.unit == elrond::TimeUnit::MICROSECONDS);
}

TEST_CASE("Check converting timespans from miliseconds", "[timespan]")
{
    auto ms = elrond::milliseconds(30000);

    auto s = elrond::seconds(ms);
    CHECK(s.count == 30);
    CHECK(s.unit == elrond::TimeUnit::SECONDS);

    auto us = elrond::microseconds(ms);
    CHECK(us.count == 30000000);
    CHECK(us.unit == elrond::TimeUnit::MICROSECONDS);
}

TEST_CASE("Check converting timespans from microseconds", "[timespan]")
{
    auto us = elrond::microseconds(30000000);

    auto s = elrond::seconds(us);
    CHECK(s.count == 30);
    CHECK(s.unit == elrond::TimeUnit::SECONDS);

    auto ms = elrond::milliseconds(us);
    CHECK(ms.count == 30000);
    CHECK(ms.unit == elrond::TimeUnit::MILLISECONDS);
}
