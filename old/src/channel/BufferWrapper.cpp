#include "channel/BufferWrapper.hpp"

using elrond::channel::BufferWrapper;

/*  ****************************************************************************
    ************** elrond::channel::BufferWrapper Implementation ***************
    ****************************************************************************/

BufferWrapper::BufferWrapper(elrond::byte* const data, const elrond::sizeT length):
data(data), length(length) {}
