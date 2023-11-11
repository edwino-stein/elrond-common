#include <elrond_mock.hpp>

using elrond::module::HelloWorld;
using elrond::mock::RuntimeCtx;
using elrond::mock::ConsoleAdapter;
using elrond::mock::Arguments;
using elrond::runtime::OStringStream;
using elrond::interface::Stream;
using elrond::mock::SeverityToStr;

int main()
{
    auto ctx = RuntimeCtx::create<HelloWorld>("teste");

    ConsoleAdapter consoleAdapter(
        [](){
            return std::make_shared<OStringStream>();
        },
        [&ctx](Stream& stream, elrond::SEVERITY severity)
        { 
            std::cout   << ctx.moduleHandle().name()
                        << " [" << SeverityToStr(severity) << "]: "
                        << reinterpret_cast<OStringStream&>(stream).oss().str()
                        << std::endl;
        }
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
