#if !defined  _ELROND_TEST_RX_CHANNEL_HPP
#define _ELROND_TEST_RX_CHANNEL_HPP

    #include "elrond.hpp"

    namespace elrond {
        namespace test {

            class RxChannelTest : public elrond::channel::RxChannel {

                public:
                    RxChannelTest(elrond::channel::OnReceiveHandleT handle);
            };
        }
    }

#endif
