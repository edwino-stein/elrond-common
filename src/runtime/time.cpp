#include "runtime/time.hpp"

/*  ****************************************************************************
    ******************* Elrond time functions implementation *******************
    ****************************************************************************/

namespace elrond {

    ELROND_INLINE_FUNC elrond::timeT millis()
    {
        auto duration = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    ELROND_INLINE_FUNC elrond::timeT micros()
    {
        auto duration = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    ELROND_INLINE_FUNC void delay(const elrond::timeT ms)
    { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

    ELROND_INLINE_FUNC void delayMicroseconds(const elrond::timeT us)
    { std::this_thread::sleep_for(std::chrono::microseconds(us)); }
}
