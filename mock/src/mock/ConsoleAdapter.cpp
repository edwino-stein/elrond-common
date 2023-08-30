#include "mock/ConsoleAdapter.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::mock::ConsoleStreamAdapter;
using elrond::interface::Stream;
using elrond::runtime::NullStream;
using IConsoleStreamAdapter = elrond::interface::ConsoleStreamAdapter;

ConsoleAdapter::ConsoleAdapter(MakeStreamH makeStream):
    _makeStream(makeStream),
    _preAppend(ConsoleAdapter::nullAppend),
    _postAppend(ConsoleAdapter::nullAppend)
{}

ConsoleAdapter::ConsoleAdapter(MakeStreamH makeStream, AppendH preAppend):
    _makeStream(makeStream),
    _preAppend(preAppend),
    _postAppend(ConsoleAdapter::nullAppend)
{}

ConsoleAdapter::ConsoleAdapter(MakeStreamH makeStream, AppendH preAppend, AppendH postAppend):
    _makeStream(makeStream),
    _preAppend(preAppend),
    _postAppend(postAppend)
{}

elrond::pointer<ConsoleStreamAdapter> ConsoleAdapter::makeConsoleStreamAdapter()
{ return std::make_shared<ConsoleStreamAdapter>(*this); }

ConsoleAdapter& ConsoleAdapter::null()
{
    static ConsoleAdapter nullConsoleAdapter(ConsoleAdapter::makeNullStream);
    return nullConsoleAdapter;
}

void ConsoleAdapter::nullAppend(IConsoleStreamAdapter&, elrond::SEVERITY) {}

elrond::pointer<Stream> ConsoleAdapter::makeNullStream()
{ return std::make_shared<NullStream>(); }

ConsoleStreamAdapter::ConsoleStreamAdapter(ConsoleAdapter& adapter)
: _adapter(&adapter), _stream(_adapter->_makeStream())
{}

Stream& ConsoleStreamAdapter::stream() const
{ return *(this->_stream); }

void ConsoleStreamAdapter::preAppend(elrond::SEVERITY severity)
{ this->_adapter->_preAppend(*this, severity); }

void ConsoleStreamAdapter::postAppend(elrond::SEVERITY severity)
{ this->_adapter->_postAppend(*this, severity); }

