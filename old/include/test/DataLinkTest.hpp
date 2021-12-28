#if !defined  _ELROND_TEST_DATA_LINK_HPP
#define _ELROND_TEST_DATA_LINK_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class DataLinkTest : public elrond::module::Loopback {

                private:
                    using onActionT = ELROND_LAMBDA_FUNC(bool, elrond::byte[], const elrond::sizeT);

                protected:

                    onActionT onSend;
                    onActionT onReceive;

                public:

                    DataLinkTest(onActionT onSend = nullptr, onActionT onReceive = nullptr);

                    bool send(elrond::byte data[], const elrond::sizeT length) override;
                    void receive(elrond::channel::OnChmReceiveHandleT handle,
                                 elrond::TaskContext* const ctx) override;
            };
        }
    }

#endif
