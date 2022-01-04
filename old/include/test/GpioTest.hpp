#if !defined  _ELROND_TEST_GPIO_HPP
#define _ELROND_TEST_GPIO_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class GpioTest : public elrond::module::BaseGpioModule {

                protected:

                    using OnAttachT = ELROND_LAMBDA_FUNC(void, elrond::gpio::BaseGpioPin&);
                    using OnWriteT = ELROND_LAMBDA_FUNC(void, elrond::gpio::BaseGpioPin&, const elrond::word);

                    std::map<elrond::uInt8, elrond::word> pinHeader;

                    OnWriteT onWrite = nullptr;
                    OnAttachT onAttach = nullptr;

                public:

                    GpioTest(OnAttachT onAttach = nullptr, OnWriteT onWrite = nullptr);

                    void attach(elrond::gpio::BaseGpioPin& pin) override;
                    elrond::word read(elrond::gpio::BaseGpioPin& pin) override;
                    void write(elrond::gpio::BaseGpioPin& pin,
                                       const elrond::word data) override;

                    bool simulateInput(elrond::gpio::BaseGpioPin& pin, const elrond::word data);
            };
        }
    }

#endif
