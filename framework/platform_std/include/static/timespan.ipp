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

        ELROND_INLINE TimeSpan seconds(elrond::timeT count)
        { return TimeSpan {count, elrond::TimeUnit::SECONDS}; }

        ELROND_INLINE TimeSpan seconds(const TimeSpan& ts)
        { return platform::tsConvert<platform::seconds, TimeUnit::SECONDS>(ts); }

        ELROND_INLINE TimeSpan milliseconds(elrond::timeT count)
        { return {count, TimeUnit::MILLISECONDS}; }
    
        ELROND_INLINE TimeSpan milliseconds(const TimeSpan& ts)
        { return platform::tsConvert<platform::milliseconds, TimeUnit::MILLISECONDS>(ts); }

        ELROND_INLINE TimeSpan microseconds(elrond::timeT count)
        { return {count, TimeUnit::MICROSECONDS}; }

        ELROND_INLINE TimeSpan microseconds(const TimeSpan& ts)
        { return platform::tsConvert<platform::microseconds, TimeUnit::MICROSECONDS>(ts); }

    }

#endif
