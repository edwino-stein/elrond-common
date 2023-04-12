#include "mock/ConsoleAdapter.hpp"
#include "mock/StreamAdapter.hpp"

using elrond::mock::ConsoleAdapter;
using elrond::interface::Stream;
using elrond::mock::StreamAdapter;
using elrond::runtime::NullStream;

ConsoleAdapter::ConsoleAdapter(Stream& stream):
_stream(stream), _makeStreamAdapter(StreamAdapter::makeNull) {}

ConsoleAdapter::ConsoleAdapter(Stream& stream, MakeStreamAdapterH makeStreamAdapter):
_stream(stream), _makeStreamAdapter(makeStreamAdapter) {}

void ConsoleAdapter::info(std::ostringstream&, const std::string&) const {}
void ConsoleAdapter::error(std::ostringstream&, const std::string&) const {}

elrond::pointer<elrond::interface::StreamAdapter>
ConsoleAdapter::makeStreamAdapter(const elrond::string& severity) const
{
    return this->_makeStreamAdapter(this->_stream, severity);
}

elrond::pointer<elrond::interface::StreamAdapter> ConsoleAdapter::getInfoStreamAdapter() const
{
    return this->makeStreamAdapter("INFO");
}

elrond::pointer<elrond::interface::StreamAdapter> ConsoleAdapter::getErrorStreamAdapter() const
{
    return this->makeStreamAdapter("ERROR");
}

ConsoleAdapter* ConsoleAdapter::null()
{
    static NullStream nullStream;
    static ConsoleAdapter nullConsoleAdapter(nullStream);
    return &nullConsoleAdapter;
}
