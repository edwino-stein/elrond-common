#ifndef ELROND_MOCK_CONSOLE_HPP
    #define ELROND_MOCK_CONSOLE_HPP

    #include "elrond_mock_types.hpp"

    namespace elrond
    {
        namespace mock
        {
            class Console : public elrond::runtime::BaseConsole
            {
                public:
                    using CallbackStream = elrond::procedure<elrond::StreamH>;

                protected:

                    CallbackStream printInfoH;
                    CallbackStream throwErrorH;

                    void printInfo(const elrond::StreamH& handle) const override;
                    void throwError(const elrond::StreamH& handle) const override;

                    static std::unique_ptr<elrond::interface::Console> nullSingleton;
                    static void defaultThrowError(elrond::StreamH handle);
    
                public:
                    Console();
                    Console(const CallbackStream& printInfoH);
                    Console(const CallbackStream& printInfoH, const CallbackStream throwErrorH);

                    static std::shared_ptr<elrond::interface::Console> null();
            };
        }
    }

#endif
