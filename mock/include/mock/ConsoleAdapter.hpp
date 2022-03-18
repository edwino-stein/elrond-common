#ifndef ELROND_MOCK_CONSOLE_ADAPTER_HPP
    #define ELROND_MOCK_CONSOLE_ADAPTER_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class ConsoleAdapter : public elrond::interface::ConsoleAdapter
            {
                public:

                    using CallbackStream = elrond::procedure<std::ostringstream&>;

                protected:

                    CallbackStream printInfoH;
                    CallbackStream throwErrorH;

                    static void defaultThrowError(std::ostringstream& msg);

                public:

                    ConsoleAdapter();
                    ConsoleAdapter(const CallbackStream& printInfoH);
                    ConsoleAdapter(const CallbackStream& printInfoH, const CallbackStream throwErrorH);

                    void info(std::ostringstream& msg, const std::string& tag) const override;
                    void error(std::ostringstream& msg, const std::string& tag) const override;

                    static ConsoleAdapter& null();
            };
        }
    }

#endif
