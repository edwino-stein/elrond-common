#include "elrond-test.hpp"
#include "catch.hpp"

#include <string>

using elrond::test::RuntimeTest;
using elrond::test::DebugOut;
using elrond::test::ConfigMap;

using elrond::module::Example;
using elrond::LoopControl;

TEST_CASE("Runtime application for Elrond Test Library")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(&appt);
    appt.set(dout);

    Example inst;
    ConfigMap cfg;

    cfg.set("loop", true)
       .set("thread", false)
       .set("interval", 1000);

    CHECK_NOTHROW([&appt, &inst, &cfg](){

        LoopControl lc;
        int loops = 0;

        appt.init(inst, cfg, lc);

        CHECK(lc.enable == true);
        CHECK(lc.ownThread == false);
        CHECK(lc.interval == 1000);

        appt.start(
               inst,
               lc,
               [&loops](){ return loops++ < 1; }
            );
    }());
}
