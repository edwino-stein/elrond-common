#include "runtime/OStringStream.hpp"

using elrond::runtime::OStringStream;
using elrond::runtime::OStream;

OStringStream::OStringStream(): OStream(_oss), _oss() {}
std::ostringstream& OStringStream::oss() { return this->_oss; }
