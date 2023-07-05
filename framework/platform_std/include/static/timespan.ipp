#ifndef ELROND_COMMON_STATIC_TIME_SPAN_IPP
    #define ELROND_COMMON_STATIC_TIME_SPAN_IPP

    #include "static/timespan.hpp"

    namespace elrond
    {
        namespace platform
        {
            template <class D>
            D tsToDurationConvert(const elrond::TimeSpan& ts)
            {
                switch (ts.unit)
                {
                    default:
                    case TimeUnit::SECONDS:
                        return std::chrono::duration_cast<D>(seconds(ts.count));
                    break;
                    case TimeUnit::MILLISECONDS:
                        return std::chrono::duration_cast<D>(milliseconds(ts.count));
                    break;
                    case TimeUnit::MICROSECONDS:
                        return std::chrono::duration_cast<D>(microseconds(ts.count));
                    break;
                }
            }

            template <class D, elrond::TimeUnit U>
            elrond::TimeSpan tsConvert(const elrond::TimeSpan& ts)
            {
                return  ts.unit == U ? ts : elrond::TimeSpan{ tsToDurationConvert<D>(ts).count(), U };
            }
        }

        inline TimeSpan seconds(elrond::timeT count)
        { return TimeSpan {count, elrond::TimeUnit::SECONDS}; }

        inline TimeSpan seconds(const TimeSpan& ts)
        { return platform::tsConvert<platform::seconds, TimeUnit::SECONDS>(ts); }

        inline TimeSpan milliseconds(elrond::timeT count)
        { return {count, TimeUnit::MILLISECONDS}; }
    
        inline TimeSpan milliseconds(const TimeSpan& ts)
        { return platform::tsConvert<platform::milliseconds, TimeUnit::MILLISECONDS>(ts); }

        inline TimeSpan microseconds(elrond::timeT count)
        { return {count, TimeUnit::MICROSECONDS}; }

        inline TimeSpan microseconds(const TimeSpan& ts)
        { return platform::tsConvert<platform::microseconds, TimeUnit::MICROSECONDS>(ts); }

    }

#endif
