#include "mock/ConsoleAdapter.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::interface::Stream;
using elrond::runtime::NullStream;

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

void ConsoleAdapter::preAppend(Stream& stream, const elrond::string& tag, ConsoleAdapter::SEVERITY severity) const
{ this->_preAppend(stream, tag, severity); }

void ConsoleAdapter::postAppend(Stream& stream, const elrond::string& tag, SEVERITY severity) const
{ this->_postAppend(stream, tag, severity); }

elrond::pointer<Stream> ConsoleAdapter::makeStream() const
{ return this->_makeStream(); }

ConsoleAdapter& ConsoleAdapter::null()
{
    static ConsoleAdapter nullConsoleAdapter(ConsoleAdapter::makeNullStream);
    return nullConsoleAdapter;
}

void ConsoleAdapter::nullAppend(Stream&, const elrond::string&, ConsoleAdapter::SEVERITY) {}

elrond::pointer<Stream> ConsoleAdapter::makeNullStream()
{ return std::make_shared<NullStream>(); }
