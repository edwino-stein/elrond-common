#if !defined  _ELROND_TEST_DEBUG_OUT_HPP
#define _ELROND_TEST_DEBUG_OUT_HPP

    #include "elrond.hpp"
    #include "interface/DebugOut.hpp"

    #include <sstream>

    namespace elrond {
        namespace test {

            class DebugOut : public elrond::interface::DebugOut {

                private:
                    using DebugOutHandleT = ELROND_LAMBDA_FUNC(void, std::ostringstream&);

                protected:
                    DebugOutHandleT handle;

                public:

                    DebugOut(DebugOutHandleT handle);

                    const elrond::interface::DebugOut& put(const char c[]) const override;
                    const elrond::interface::DebugOut& put(char c) const override;
                    const elrond::interface::DebugOut& put(unsigned char c) const override;
                    const elrond::interface::DebugOut& put(int i) const override;
                    const elrond::interface::DebugOut& put(unsigned int i) const override;
                    const elrond::interface::DebugOut& put(long l) const override;
                    const elrond::interface::DebugOut& put(unsigned long l) const override;
                    const elrond::interface::DebugOut& put(double d) const override;

                    const elrond::interface::DebugOut& putLn(const char c[]) const override;
                    const elrond::interface::DebugOut& putLn(char c) const override;
                    const elrond::interface::DebugOut& putLn(unsigned char c) const override;
                    const elrond::interface::DebugOut& putLn(int i) const override;
                    const elrond::interface::DebugOut& putLn(unsigned int i) const override;
                    const elrond::interface::DebugOut& putLn(long l) const override;
                    const elrond::interface::DebugOut& putLn(unsigned long l) const override;
                    const elrond::interface::DebugOut& putLn(double d) const override;
                    const elrond::interface::DebugOut& putLn() const override;

                    const elrond::interface::DebugOut& flush() const override;

                    #ifdef ELROND_WITH_STR_TYPE
                        const elrond::interface::DebugOut& put(elrond::String str) const override;
                        const elrond::interface::DebugOut& putLn(elrond::String str) const override;
                    #endif
            };
        }
    }

#endif
