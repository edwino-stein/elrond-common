#include "elrond-test.hpp"
#include <string>

using elrond::test::RuntimeTest;
using elrond::test::DebugOut;
using elrond::test::ConfigMap;
using elrond::modules::Example;

TEST_CASE("Runtime application for Elrond Test Library")
{
    DebugOut dout([](std::ostringstream& oss){ UNSCOPED_INFO(oss.str()); });
    RuntimeTest appt;

    RuntimeTest::setAppInstance(appt);
    appt.set(dout);

    Example inst;
    ConfigMap cfg;

    cfg.set("allow", true)
       .set("timeLoop", 1000);

    REQUIRE_NOTHROW([&appt, &inst, &cfg](){
        int loops = 0;
        appt.init(inst, cfg)
            .start(
               inst,
               [&loops](){ return loops++ < 1; }
            );
    }());
}
