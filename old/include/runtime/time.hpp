#if !defined  _ELROND_TIME_HPP
#define _ELROND_TIME_HPP

    #include "elrond_types.hpp"

    namespace elrond {

        elrond::timeT millis();
        elrond::timeT micros();

        void delay(const elrond::timeT ms);
        void delayMicroseconds(const elrond::timeT us);
    }

#endif
