#if !defined  _ELROND_TEST_DEBUG_OUT_HPP
#define _ELROND_TEST_DEBUG_OUT_HPP

    #include "elrond.hpp"

    #include "interfaces/DebugOutInterface.hpp"
    #include <functional>
    #include <sstream>

    namespace elrond {
        namespace test {

            class DebugOut : public elrond::interfaces::DebugOutInterface {

                protected:
                    std::function<void(std::ostringstream&)> handle;

                public:

                    DebugOut(std::function<void(std::ostringstream&)> handle);

                    const elrond::interfaces::DebugOutInterface& put(const char c[]) const override;
                    const elrond::interfaces::DebugOutInterface& put(char c) const override;
                    const elrond::interfaces::DebugOutInterface& put(unsigned char c) const override;
                    const elrond::interfaces::DebugOutInterface& put(int i) const override;
                    const elrond::interfaces::DebugOutInterface& put(unsigned int i) const override;
                    const elrond::interfaces::DebugOutInterface& put(long l) const override;
                    const elrond::interfaces::DebugOutInterface& put(unsigned long l) const override;
                    const elrond::interfaces::DebugOutInterface& put(double d) const override;

                    const elrond::interfaces::DebugOutInterface& putLn(const char c[]) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(char c) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(unsigned char c) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(int i) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(unsigned int i) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(long l) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(unsigned long l) const override;
                    const elrond::interfaces::DebugOutInterface& putLn(double d) const override;
                    const elrond::interfaces::DebugOutInterface& putLn() const override;

                    const elrond::interfaces::DebugOutInterface& flush() const override;

                    #ifdef ELROND_WITH_STR_TYPE
                        const elrond::interfaces::DebugOutInterface& put(elrond::String str) const override;
                        const elrond::interfaces::DebugOutInterface& putLn(elrond::String str) const override;
                    #endif
            };
        }
    }

#endif
