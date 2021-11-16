#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::Console;
using elrond::mock::StringStream;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    Console console(
        [](const elrond::StreamH& handle)
        {
            StringStream s;
            handle(s);
            std::cout << s.getString();
        }
    );

    ctx.console(console);

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    return 0;
}
