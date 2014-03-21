#ifndef TIMETABLE_H_INCLUDED
#define TIMETABLE_H_INCLUDED

#include "timestamp.h"

#define F_DAY_NONE 0x00000000
#define F_DAY_MON_TO_THU 0x00000001
#define F_DAY_FRIDAY 0x00000002
#define F_DAY_SATURDAY 0x00000004
#define F_DAY_SUNDAY 0x00000008
#define F_DAY_EVERY_DAY 0xFFFFFF

#define F_DAY_FIRST_DAY 0x00000001
#define F_DAY_LAST_DAY 0x00000008
typedef unsigned int DayFlags;

#define DAY_NUM 4

enum PlanName
{
    PLAN_WEEKDAY,
    PLAN_MORNING_RUSH,
    PLAN_EVENING_RUSH,
    PLAN_WEEKEND,
    PLAN_NIGHT,
    PLAN_CUSTOM,
    PLAN_NUM
};


class Timetable
{
public:

    class Plan
    {
    public:
        typedef DayTime DayTimeType;
        typedef TimeInterval IntervalType;
        Plan()
            :_startTime(0), _endTime(0), _interval(0), _days(F_DAY_NONE)
        {    }

        Plan(const DayTimeType& startTime, const DayTimeType& endTime, const TimeInterval& interval, DayFlags daymask)
            : _startTime(startTime), _endTime(endTime), _interval(interval), _days(daymask)
        {
            _startTime.normalize();
            _endTime.normalize();
        }
        void setStartTime(const DayTimeType& startTime)
        {
            _startTime = startTime;
        }
        DayTimeType& getStartTime()
        {
            return _startTime;
        }
        const DayTimeType& getStartTime() const
        {
            return _startTime;
        }
        void setEndTime(const DayTimeType& endTime)
        {
            _endTime = endTime;
        }
        DayTimeType& getEndTime()
        {
            return _endTime;
        }
        const DayTimeType& getEndTime() const
        {
            return _endTime;
        }
        TimeInterval& getInterval()
        {
            return _interval;
        }
        const TimeInterval& getInterval() const
        {
            return _interval;
        }

        const bool activeAtDays(const DayFlags& days)const // true when all dayflags are set
        {
            return (_days | days) == _days;
        }

        void activateDays(const DayFlags& days)
        {
            _days = _days | days;
        }

        void deactivateDays(const DayFlags& days)
        {
            _days = _days & ~days;
        }

        void toggleDays(const DayFlags& days)
        {
            _days = _days ^ days;
        }

    private:
        DayTimeType _startTime;
        DayTimeType _endTime;
        IntervalType _interval;

        DayFlags _days;
    };
    typedef Plan PlanType;
    typedef PlanType::DayTimeType DayTimeType;
    typedef PlanType::IntervalType IntervalType;

    //------------------------------------------------------------------------------------------

    Timetable()
    {
        _plans[PLAN_WEEKDAY] = Plan(DayTimeType(6, 0), DayTimeType(22, 0), IntervalType(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_MORNING_RUSH] = Plan(DayTimeType(7, 0), DayTimeType(7, 30), IntervalType(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_EVENING_RUSH] = Plan(DayTimeType(17, 0), DayTimeType(17, 30), IntervalType(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_WEEKEND] = Plan(PlanType::DayTimeType(6, 0), PlanType::DayTimeType(21, 0), IntervalType(3, 0), F_DAY_SATURDAY | F_DAY_SUNDAY);
        _plans[PLAN_NIGHT] = Plan(DayTimeType(0, 0), DayTimeType(3, 0), IntervalType(3, 0), F_DAY_EVERY_DAY);
        _plans[PLAN_CUSTOM] = Plan(DayTimeType(0, 0), DayTimeType(0, 0), IntervalType(0, 0), F_DAY_NONE);
    }

    Plan& getPlan(const PlanName& plan)
    {
        return _plans[plan];
    }
    const Plan& getPlan(const unsigned int& plan) const
    {
        return _plans[plan];
    }


    inline WeekTime getEndOfWeek() /**< returns the last TimeStamp of the week +1 */
    {
        return WeekTime(TIME_RESOLUTION * DAY_NUM);
    }


private:
    PlanType _plans[PLAN_NUM];



};

#endif // TIMETABLE_H_INCLUDED
