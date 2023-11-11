#include "mock/ConsoleAdapter.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::mock::ConsoleStreamAdapter;
using elrond::interface::Stream;
using elrond::runtime::NullStream;
using IConsoleStreamAdapter = elrond::interface::ConsoleStreamAdapter;

ConsoleAdapter::ConsoleAdapter(MakeStreamH makeStream):
    _makeStream(makeStream),
    _flush(ConsoleAdapter::nullFlush)
{}

ConsoleAdapter::ConsoleAdapter(MakeStreamH makeStream, FlushH flush):
    _makeStream(makeStream),
    _flush(flush)
{}

elrond::pointer<ConsoleStreamAdapter> ConsoleAdapter::makeConsoleStreamAdapter()
{ return std::make_shared<ConsoleStreamAdapter>(*this); }

ConsoleAdapter& ConsoleAdapter::null()
{
    static ConsoleAdapter nullConsoleAdapter(ConsoleAdapter::makeNullStream);
    return nullConsoleAdapter;
}

void ConsoleAdapter::nullFlush(Stream&, elrond::SEVERITY) {}

elrond::pointer<Stream> ConsoleAdapter::makeNullStream()
{ return std::make_shared<NullStream>(); }

ConsoleStreamAdapter::ConsoleStreamAdapter(ConsoleAdapter& adapter)
: _adapter(&adapter) {}

void ConsoleStreamAdapter::flush(Stream& stream, elrond::SEVERITY severity)
{ this->_adapter->_flush(stream, severity); }

elrond::pointer<Stream> ConsoleStreamAdapter::makeStream() const
{ return _adapter->_makeStream(); }
