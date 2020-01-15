#if !defined  _ELROND_TEST_GPIO_HPP
#define _ELROND_TEST_GPIO_HPP

    #include "elrond.hpp"

    #include <functional>
    #include <vector>
    #include <memory>
    #include <map>

    namespace elrond {
        namespace test {

            class GpioTest : public elrond::modules::BaseGpioModule {

                private:
                    using onWriteActionT = std::function<void(elrond::gpio::BaseGpioPin&, elrond::word, GpioTest&)>;
                    using onReadActionT = std::function<elrond::word(elrond::gpio::BaseGpioPin&, GpioTest&)>;

                    class TestDOutPin: public elrond::gpio::DOutPin
                    { public: TestDOutPin(int pin); };

                    class TestAInPin: public elrond::gpio::AInPin
                    { public: TestAInPin(int pin); };

                    class TestPwmPin: public elrond::gpio::PwmPin
                    { public: TestPwmPin(int pin); };

                    class TestServoPin: public elrond::gpio::ServoPin
                    { public: TestServoPin(int pin); };

                protected:

                    static GpioTest* currentGpio;

                    onWriteActionT onWrite;
                    onReadActionT onRead;

                    using BaseGpioPinP = std::unique_ptr<elrond::gpio::BaseGpioPin>;
                    std::vector<BaseGpioPinP> testPinInsts;
                    std::map<int, elrond::word> testAinValues;

                public:
                    GpioTest(const bool current = true, onWriteActionT onWrite = nullptr, onReadActionT onRead = nullptr);

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

                    static void write(elrond::gpio::BaseGpioPin &pin, elrond::word& data);
                    static elrond::word read(elrond::gpio::BaseGpioPin &pin);
                    static void setCurrentGpio(GpioTest* gpio);
            };
        }
    }

#endif
