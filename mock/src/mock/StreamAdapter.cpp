#include "mock/StreamAdapter.hpp"

using elrond::mock::StreamAdapter;
using elrond::interface::Stream;

StreamAdapter::StreamAdapter(Stream& stream, AppendH preAppend, AppendH postAppend)
: _stream(stream), _preAppend(preAppend), _postAppend(postAppend) {}

const Stream& StreamAdapter::stream() const { return this->_stream; }
void StreamAdapter::preAppend() const { this->_preAppend(this->stream()); }
void StreamAdapter::postAppend() const { this->_postAppend(this->stream()); }

void StreamAdapter::eolAppend(const Stream& stream) { stream << '\n'; }
void StreamAdapter::voidAppend(const elrond::interface::Stream&) {}

elrond::pointer<elrond::interface::StreamAdapter>
StreamAdapter::makePretty(Stream& stream, elrond::string tag)
{
    return std::make_shared<StreamAdapter>(
        stream,
        [tag](const Stream& s) { s << '[' << tag << "]\t"; },
        StreamAdapter::eolAppend
    );
}

elrond::pointer<elrond::interface::StreamAdapter>
StreamAdapter::makeNull(Stream& stream, elrond::string)
{
    return std::make_shared<StreamAdapter>(
        stream,
        StreamAdapter::voidAppend,
        StreamAdapter::voidAppend
    );
}
