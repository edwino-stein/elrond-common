#if !defined  _ELROND_TEST_TRANSPORT_HPP
#define _ELROND_TEST_TRANSPORT_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class TransportTest : public elrond::module::BaseTransportModule {

                private:
                    using onActionT = std::function<void(elrond::byte[], const elrond::sizeT, TransportTest&)>;

                protected:

                    elrond::interface::ChannelManager* cm = nullptr;
                    onActionT onSend;
                    onActionT onReceive;

                public:

                    TransportTest(onActionT onSend = nullptr, onActionT onReceive = nullptr);

                    void send(elrond::byte data[], const elrond::sizeT length) override;
                    void receive(elrond::byte data[], const elrond::sizeT length);
                    void notifyChm(elrond::byte data[], const elrond::sizeT length) const;

                    void setChannelManager(elrond::interface::ChannelManager* cm) override;
            };
        }
    }

#endif
