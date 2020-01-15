#include "elrond-test.hpp"

using elrond::test::ConfigMap;

TEST_CASE("ConfigMap for Elrond Test Library", "[app][config]" )
{
    ConfigMap cfg;
    cfg.set("i", 123)
       .set("d", 123.456)
       .set("b", true)
       .set("c", 'A')
       .set("s", "string");

    REQUIRE(cfg.isInt("i"));
    REQUIRE(cfg.asInt("i") == 123);

    REQUIRE(cfg.isDouble("d"));
    REQUIRE(cfg.asDouble("d") == Approx(123.456));

    REQUIRE(cfg.isBool("b"));
    REQUIRE(cfg.asBool("b") == true);

    REQUIRE(cfg.isChar("c"));
    REQUIRE(cfg.asChar("c") == 'A');

    REQUIRE(cfg.isString("s"));
    REQUIRE(std::string(cfg.asString("s")) == std::string("string"));

    REQUIRE(cfg.isNull("n"));
}
