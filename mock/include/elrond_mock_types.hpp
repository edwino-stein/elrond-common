#ifndef ELROND_MOCK_TYPES_HPP
    #define ELROND_MOCK_TYPES_HPP

    #include <elrond.hpp>
    #include <elrond_platform_runtime.hpp>
    #include <elrond_common_runtime.hpp>
    #include <map>
    #include <utility>

    namespace elrond
    {
        namespace mock
        {
            class Application;
            class RuntimeCtx;
            class StreamAdapter;
            class ConsoleAdapter;
            class ConsoleStreamAdapter;
            class Arguments;
            class ModuleInstanceHandle;
            class ExternalInstanceModuleHandle;
            template <class T> class InternalInstanceModuleHandle;

            inline std::string SeverityToStr(elrond::SEVERITY severity)
            {
                switch (severity)
                {
                    case elrond::SEVERITY::ERROR:
                        return "ERROR";
                    break;
                    default:
                    case elrond::SEVERITY::INFO:
                        return "INFO";
                    break;
                }
            }
        }
    }

#endif
