#ifndef ELROND_PLATFORM_BASE_CONSOLE_STREAM_HPP
    #define ELROND_PLATFORM_BASE_CONSOLE_STREAM_HPP

    #include "interface/Stream.hpp"
    #include "interface/StreamAdapter.hpp"

    namespace elrond
    {
        namespace platform 
        {
            class ConsoleStream : public elrond::interface::Stream
            {
                protected:
                    elrond::pointer<elrond::interface::StreamAdapter> adapter;

                public:
                    ConsoleStream(elrond::pointer<elrond::interface::StreamAdapter> adapter);
                    ~ConsoleStream();

                    ConsoleStream(ConsoleStream&&) = default;
                    ConsoleStream(const ConsoleStream&) = delete;
                    ConsoleStream& operator=(const ConsoleStream&) = delete;
                    ConsoleStream& operator=(ConsoleStream&&) = delete;

                    //
                    // Char and strings
                    //
                    const elrond::interface::Stream& operator<<(const char c) const override;
                    const elrond::interface::Stream& operator<<(const unsigned char c) const override;
                    const elrond::interface::Stream& operator<<(const char c[]) const override;
                    const elrond::interface::Stream& operator<<(elrond::string str) const override;

                    //
                    // Numeric
                    //
                    const elrond::interface::Stream& operator<<(const int i) const override;
                    const elrond::interface::Stream& operator<<(const unsigned int i) const override;
                    const elrond::interface::Stream& operator<<(const long l) const override;
                    const elrond::interface::Stream& operator<<(const unsigned long l) const override;
                    const elrond::interface::Stream& operator<<(const double d) const override;
            };
        }
    }

#endif
