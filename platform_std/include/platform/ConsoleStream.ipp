#ifndef ELROND_PLATFORM_BASE_CONSOLE_STREAM_IPP
    #define ELROND_PLATFORM_BASE_CONSOLE_STREAM_IPP

    #include "platform/ConsoleStream.hpp"

    namespace elrond
    {
        namespace platform 
        {
            ELROND_INLINE
            ConsoleStream::ConsoleStream(elrond::pointer<elrond::interface::StreamAdapter> adapter)
            : adapter(adapter) { this->adapter->preAppend(); }

            ELROND_INLINE
            ConsoleStream::~ConsoleStream() { this->adapter->postAppend(); }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(char c) const
            { return this->adapter->stream() << c; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(unsigned char c) const
            { return this->adapter->stream() << c; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const char* c) const
            { return this->adapter->stream() << c; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(elrond::string str) const
            { return this->adapter->stream() << str; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(int i) const
            { return this->adapter->stream() << i; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(unsigned int i) const
            { return this->adapter->stream() << i; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(long l) const
            { return this->adapter->stream() << l; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(unsigned long l) const
            { return this->adapter->stream() << l; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(double d) const
            { return this->adapter->stream() << d; }
        }
    }

#endif
