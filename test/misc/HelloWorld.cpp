#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::ConsoleAdapter;
using elrond::mock::Arguments;
using elrond::runtime::OStream;
using elrond::interface::Stream;
using elrond::mock::SeverityToStr;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    ConsoleAdapter consoleAdapter(
        [](){ return std::make_shared<OStream>(std::cout); },
        [](Stream& s, const elrond::string& tag, ConsoleAdapter::SEVERITY severity)
        { s << tag << " [" << SeverityToStr(severity) << "]: "; },
        [](Stream& s, const elrond::string&, ConsoleAdapter::SEVERITY) { s << "\n"; }
    );

    ctx.console(consoleAdapter);

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    Arguments args;
    args.set("message", "Test hello world")
        .set("loop", true)
        .set("async", true)
        .set("interval", 500);

    ctx.arguments(args);

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    return 0;
}
