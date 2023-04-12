#ifndef ELROND_PLATFORM_RUNTIME_RUNTIME_CONSOLE_HPP
    #define ELROND_PLATFORM_RUNTIME_RUNTIME_CONSOLE_HPP

    #include "elrond_platform_runtime_types.hpp"
    #include "interface/ConsoleAdapter.hpp"

    namespace elrond
    {
        namespace runtime
        {
            class Console : public elrond::interface::Console
            {
                protected:

                    elrond::interface::ConsoleAdapter& adapter;

                public:

                    Console(elrond::interface::ConsoleAdapter& adapter);

                    //
                    // Stream directly
                    //
                    const elrond::platform::ConsoleStream info() const override;
                    const elrond::platform::ConsoleStream error() const override;

                    //
                    // Char and strings
                    //
                    void info(const char c) const override;
                    void info(const unsigned char c) const override;
                    void info(const char c[]) const override;
                    void info(elrond::string str) const override;
                    void error(const char c[]) const override;
                    void error(elrond::string str) const override;

                    //
                    // Numeric
                    //
                    void info(const int i) const override;
                    void info(const unsigned int i) const override;
                    void info(const long l) const override;
                    void info(const unsigned long l) const override;
                    void info(const double d) const override;
            };
        }
    }

#endif
