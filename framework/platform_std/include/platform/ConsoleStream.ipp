#ifndef ELROND_PLATFORM_BASE_CONSOLE_STREAM_IPP
    #define ELROND_PLATFORM_BASE_CONSOLE_STREAM_IPP

    #include "platform/ConsoleStream.hpp"

    namespace elrond
    {
        namespace platform 
        {
            ELROND_INLINE
            ConsoleStream::ConsoleStream(
                elrond::pointer<elrond::interface::ConsoleStreamAdapter> adapter,
                elrond::SEVERITY severity
            ): _adapter(adapter), _stream(_adapter->makeStream()), _severity(severity)
            {}

            ELROND_INLINE
            ConsoleStream::~ConsoleStream()
            { this->_adapter->flush(*(this->_stream), this->_severity); }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(char c)
            { return *(this->_stream) << c; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(unsigned char c)
            { return *(this->_stream) << c; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(const char* c)
            { return *(this->_stream) << c; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(elrond::string str)
            { return *(this->_stream) << str; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(int i)
            { return *(this->_stream) << i; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(unsigned int i)
            { return *(this->_stream) << i; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(long l)
            { return *(this->_stream) << l; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(unsigned long l)
            { return *(this->_stream) << l; }

            ELROND_INLINE
            elrond::interface::Stream& ConsoleStream::operator<<(double d)
            { return *(this->_stream) << d; }
        }
    }

#endif
