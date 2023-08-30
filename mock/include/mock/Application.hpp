#ifndef ELROND_MOCK_APPLICATION_HPP
    #define ELROND_MOCK_APPLICATION_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class Application
            {
                private:
                    elrond::mock::ConsoleAdapter* _consoleAdapter;
                    elrond::interface::Arguments* _arguments;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS(Application,, =default, =default, =default, =default)

                    elrond::pointer<elrond::interface::Console> makeConsole() const;
                    elrond::pointer<elrond::interface::Arguments> makeArguments() const;

                    Application& with(elrond::mock::ConsoleAdapter& _consoleAdapter);
                    Application& with(elrond::interface::Arguments& args);
            };
        }
    }

#endif
