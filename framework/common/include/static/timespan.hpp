#ifndef ELROND_COMMON_STATIC_TIME_SPAN_HPP
    #define ELROND_COMMON_STATIC_TIME_SPAN_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        TimeSpan seconds(elrond::timeT count);
        TimeSpan seconds(const TimeSpan& ts);

        TimeSpan milliseconds(elrond::timeT count);
        TimeSpan milliseconds(const TimeSpan& ts);

        TimeSpan microseconds(elrond::timeT count);
        TimeSpan microseconds(const TimeSpan& ts);
    }

#endif
