#if !defined  _ELROND_TEST_TX_CHANNEL_HPP
#define _ELROND_TEST_TX_CHANNEL_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class TxChannelTest : public elrond::channel::TxChannel {

                public:

                    TxChannelTest(const elrond::sizeT ch,
                                  elrond::channel::BaseChannelManager& chm);
            };
        }
    }

#endif
