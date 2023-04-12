#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::ConsoleAdapter;
using elrond::mock::Arguments;
using elrond::runtime::OStream;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    OStream stream(std::cout);
    ConsoleAdapter consoleAdapter(stream, elrond::mock::StreamAdapter::makePretty);
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
