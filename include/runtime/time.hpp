#if !defined  _ELROND_TIME_HPP
#define _ELROND_TIME_HPP

    #include "types.hpp"

    namespace elrond {

        unsigned long millis();
        unsigned long micros();

        void delay(unsigned long ms);
        void delayMicroseconds(unsigned int us);
    }

#endif
