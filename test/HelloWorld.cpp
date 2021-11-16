#include <elrond_mock.hpp>

using elrond::module::HelloWorld;

int main()
{
    HelloWorld inst;

    inst.setup();
    inst.start();
    inst.loop();
    inst.stop();

    return 0;
}
