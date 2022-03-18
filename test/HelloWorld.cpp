#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::ConsoleAdapter;
using elrond::mock::StringStream;
using elrond::mock::Parameters;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");
    ConsoleAdapter consoleAdapter(
        [](std::ostringstream& msg){ std::cout << msg.str(); }
    );

    ctx.console(consoleAdapter);

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    Parameters param;
    param.set("message", "Test hello world");

    ctx.callSetup(param)
        .callStart()
        .callLoop(2)
        .callStop();

    return 0;
}
