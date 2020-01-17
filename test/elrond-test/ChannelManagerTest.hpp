#if !defined  _ELROND_TEST_CHANNEL_MANAGER_HPP
#define _ELROND_TEST_CHANNEL_MANAGER_HPP

    #include "elrond.hpp"

    #include <vector>
    #include <memory>

    namespace elrond {
        namespace test {

            class ChannelManagerTest : public elrond::channel::BaseChannelManager {

                private:

                    struct RxChCollection {
                        std::vector<elrond::channel::RxChannel*> channels;
                    };

                    using RxChCollectionP = std::unique_ptr<RxChCollection>;

                    class RxChannelTest : public elrond::channel::RxChannel {
                        public:
                            RxChannelTest(elrond::channel::OnReceiveHandleT handle);
                    };

                    using RxChTestP = std::unique_ptr<RxChannelTest>;

                protected:

                    const elrond::sizeT chs;
                    const bool autoSync;
                    std::unique_ptr<elrond::byte[]> txBuffer;
                    std::unique_ptr<RxChCollectionP[]> rxChannels;

                    std::vector<RxChTestP> rxChTestInsts;

                    void rxTrigger(const elrond::sizeT ch, const elrond::word data) override;
                    elrond::byte *getTxBuffer() const override;

                public:

                    ChannelManagerTest(
                        elrond::modules::BaseTransportModule& transport,
                        const elrond::sizeT chs,
                        const bool autoSync = true,
                        const bool autoInit = true
                    );

                    void txTrigger(const elrond::sizeT ch, const elrond::word data) override;
                    void addRxListener(const elrond::sizeT ch, elrond::channel::RxChannel *rx) override;
                    elrond::sizeT getTotalTx() const override;
                    elrond::sizeT getTotalRx() const override;

                    void onRxReceive(const elrond::sizeT ch, elrond::channel::OnReceiveHandleT handle);
            };
        }
    }

#endif
