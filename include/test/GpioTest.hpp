#if !defined  _ELROND_TEST_GPIO_HPP
#define _ELROND_TEST_GPIO_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class GpioTest : public elrond::module::BaseGpioModule {

                private:

                    class TestDOutPin: public elrond::gpio::DOutPin
                    { public: TestDOutPin(int pin); };

                    class TestAInPin: public elrond::gpio::AInPin
                    { public: TestAInPin(int pin); };

                    class TestPwmPin: public elrond::gpio::PwmPin
                    { public: TestPwmPin(int pin); };

                    class TestServoPin: public elrond::gpio::ServoPin
                    { public: TestServoPin(int pin); };

                protected:

                    elrond::gpio::WriteHandleT onWrite;
                    elrond::gpio::ReadHandleT onRead;

                    using BaseGpioPinP = std::unique_ptr<elrond::gpio::BaseGpioPin>;
                    std::vector<BaseGpioPinP> testPinInsts;
                    std::map<int, elrond::word> testAinValues;

                public:

                    GpioTest(
                        elrond::gpio::WriteHandleT onWrite = nullptr,
                        elrond::gpio::ReadHandleT onRead = nullptr
                    );

                    void attach(elrond::gpio::BaseGpioPin &pin) override;
                    elrond::gpio::DOutPin& attachDOut(int pin);
                    elrond::gpio::AInPin& attachAIn(int pin);
                    elrond::gpio::PwmPin& attachPwm(int pin);
                    elrond::gpio::ServoPin& attachServo(int pin);

                    void write(elrond::gpio::DOutPin& pin, const elrond::word data) const;
                    void write(elrond::gpio::PwmPin& pin, const elrond::word data) const;
                    void write(elrond::gpio::ServoPin& pin, const elrond::word data) const;

                    elrond::word read(elrond::gpio::DOutPin& pin) const;
                    elrond::word read(elrond::gpio::PwmPin& pin) const;
                    elrond::word read(elrond::gpio::ServoPin& pin) const;
                    elrond::word read(elrond::gpio::AInPin& pin) const;

                    void simulateAin(const int pin, const elrond::word data);
            };
        }
    }

#endif
