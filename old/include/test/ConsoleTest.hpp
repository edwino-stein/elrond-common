#if !defined  _ELROND_TEST_CONSOLE_HPP
#define _ELROND_TEST_CONSOLE_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class ConsoleTest : public elrond::interface::Console {
                protected:
                    using ConsoleHandleT = ELROND_LAMBDA_FUNC(void, std::ostringstream&);

                    ConsoleHandleT handle = nullptr;
                    std::unique_ptr<std::ostringstream> oss;
                    const bool putEL;

                    std::ostringstream& getOSS() const;

                public:
                    ConsoleTest(ConsoleHandleT handle = nullptr, const bool putEL = true);

                    // Char and strings
                    const elrond::interface::Console& operator<<(const char c) const override;
                    const elrond::interface::Console& operator<<(const unsigned char c) const override;
                    const elrond::interface::Console& operator<<(const char c[]) const override;
                    const elrond::interface::Console& operator<<(elrond::String str) const override;

                    // Numeric
                    const elrond::interface::Console& operator<<(const int i) const override;
                    const elrond::interface::Console& operator<<(const unsigned int i) const override;
                    const elrond::interface::Console& operator<<(const long l) const override;
                    const elrond::interface::Console& operator<<(const unsigned long l) const override;
                    const elrond::interface::Console& operator<<(const double d) const override;

                    // Others
                    const elrond::interface::Console& operator<<(elrond::ConsoleCallbackT cb) const override;
                    const elrond::interface::Console& endl() const override;
            };
        }
    }

#endif
