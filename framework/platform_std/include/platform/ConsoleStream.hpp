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
                    elrond::interface::ConsoleAdapter* _adapter;
                    elrond::pointer<elrond::interface::Stream> _stream;
                    elrond::string _tag;
                    elrond::interface::ConsoleAdapter::SEVERITY _severity;

                public:
                    ELROND_CLASS_SPECIAL_MEMBERS_CONSTUCTORS(ConsoleStream, =delete, =delete, =default, =delete, =delete)
                    ConsoleStream(elrond::interface::ConsoleAdapter& adapter,
                                    const elrond::string& tag,
                                    elrond::interface::ConsoleAdapter::SEVERITY severity);

                    ~ConsoleStream();

                    //
                    // Char and strings
                    //
                    elrond::interface::Stream& operator<<(char c) override;
                    elrond::interface::Stream& operator<<(unsigned char c) override;
                    elrond::interface::Stream& operator<<(const char* c) override;
                    elrond::interface::Stream& operator<<(elrond::string str) override;

                    //
                    // Numeric
                    //
                    elrond::interface::Stream& operator<<(int i) override;
                    elrond::interface::Stream& operator<<(unsigned int i) override;
                    elrond::interface::Stream& operator<<(long l) override;
                    elrond::interface::Stream& operator<<(unsigned long l) override;
                    elrond::interface::Stream& operator<<(double d) override;
            };
        }
    }

#endif
