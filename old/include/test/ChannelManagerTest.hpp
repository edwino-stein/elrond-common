#if !defined  _ELROND_TEST_CHANNEL_MANAGER_HPP
#define _ELROND_TEST_CHANNEL_MANAGER_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class ChannelManagerTest : public elrond::channel::BaseChannelManager {

                private:

                    using RxChCollection = std::vector<elrond::channel::RxChannel*>;
                    using RxChCollectionP = std::unique_ptr<RxChCollection>;

                protected:

                    const elrond::sizeT chs;
                    std::unique_ptr<elrond::byte[]> txBuffer;
                    std::unique_ptr<RxChCollectionP[]> rxChannels;


                    void rxTrigger(const elrond::sizeT ch,
                                   const elrond::word data) override;


                    elrond::channel::BufferWrapper getTxBuffer() const override;

                public:

                    ChannelManagerTest(elrond::module::BaseDataLinkModule& dataLink,
                                       const elrond::sizeT chs);

                    void txTrigger(elrond::channel::TxChannel* const tx) override;
                    void addRxListener(elrond::channel::RxChannel* const rx) override;
                    void addRxListener(elrond::test::RxChannelTest &rx);

                    elrond::sizeT getTotalTx() const override;
                    elrond::sizeT getTotalRx() const override;
            };
        }
    }

#endif
