#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::ConsoleAdapter;
using elrond::mock::Arguments;
using elrond::runtime::OStream;
using elrond::interface::Stream;
using elrond::mock::SeverityToStr;
using IConsoleStreamAdapter = elrond::interface::ConsoleStreamAdapter;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    ConsoleAdapter consoleAdapter(
        [](){ return std::make_shared<OStream>(std::cout); },
        [&ctx](IConsoleStreamAdapter& adapter, elrond::SEVERITY severity)
        { adapter.stream() << ctx.moduleHandle().name() << " [" << SeverityToStr(severity) << "]: "; },
        [](IConsoleStreamAdapter& adapter, elrond::SEVERITY) { adapter.stream() << "\n"; }
    );

    ctx.with(consoleAdapter);

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    Arguments args;
    args.set("message", "Test hello world")
        .set("loop", true)
        .set("async", true)
        .set("interval", 500);

    ctx.with(args);

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    return 0;
}
