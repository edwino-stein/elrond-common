#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::Console;
using elrond::mock::StringStream;
using elrond::mock::Parameters;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    auto console = std::make_shared<Console> (
        [](const elrond::StreamH& handle)
        {
            StringStream s;
            handle(s);
            std::cout << s.getString() << '\n';
        }
    );

    ctx.console(console);

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
