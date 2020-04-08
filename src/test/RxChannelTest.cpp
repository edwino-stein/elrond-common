#include "test/RxChannelTest.hpp"

using elrond::test::RxChannelTest;
using elrond::channel::OnReceiveHandleT;

RxChannelTest::RxChannelTest(OnReceiveHandleT handle) { this->handle = handle; }
