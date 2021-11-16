#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    ctx.callSetup()
        .callStart()
        .callLoop(2)
        .callStop();

    return 0;
}
