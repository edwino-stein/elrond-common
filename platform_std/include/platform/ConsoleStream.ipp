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
            const elrond::interface::Stream& ConsoleStream::operator<<(const char c) const
            { return this->adapter->stream() << c; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const unsigned char c) const
            { return this->adapter->stream() << c; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const char c[]) const
            { return this->adapter->stream() << c; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(elrond::string str) const
            { return this->adapter->stream() << str; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const int i) const
            { return this->adapter->stream() << i; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const unsigned int i) const
            { return this->adapter->stream() << i; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const long l) const
            { return this->adapter->stream() << l; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const unsigned long l) const
            { return this->adapter->stream() << l; }

            ELROND_INLINE
            const elrond::interface::Stream& ConsoleStream::operator<<(const double d) const
            { return this->adapter->stream() << d; }
        }
    }

#endif
