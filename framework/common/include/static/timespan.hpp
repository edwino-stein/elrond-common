#ifndef ELROND_COMMON_STATIC_TIME_SPAN_HPP
    #define ELROND_COMMON_STATIC_TIME_SPAN_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        inline TimeSpan seconds(elrond::timeT count);
        inline TimeSpan seconds(const TimeSpan& ts);

        inline TimeSpan milliseconds(elrond::timeT count);
        inline TimeSpan milliseconds(const TimeSpan& ts);

        inline TimeSpan microseconds(elrond::timeT count);
        inline TimeSpan microseconds(const TimeSpan& ts);
    }

#endif
