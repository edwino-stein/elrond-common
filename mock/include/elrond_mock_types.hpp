#ifndef ELROND_MOCK_TYPES_HPP
    #define ELROND_MOCK_TYPES_HPP

    #include <elrond.hpp>
    #include <elrond_platform_runtime.hpp>
    #include <elrond_common_runtime.hpp>
    #include <map>

    namespace elrond
    {
        namespace mock
        {
            class RuntimeCtx;
            class StreamAdapter;
            class ConsoleAdapter;
            class Arguments;
            class ModuleInstanceHandle;
            class ExternalInstanceModuleHandle;
            template <class T> class InternalInstanceModuleHandle;

            inline std::string SeverityToStr(elrond::interface::ConsoleAdapter::SEVERITY severity)
            {
                switch (severity)
                {
                    case elrond::interface::ConsoleAdapter::ERROR:
                        return "ERROR";
                    break;
                    default:
                    case elrond::interface::ConsoleAdapter::INFO:
                        return "INFO";
                    break;
                }
            }
        }
    }

#endif
