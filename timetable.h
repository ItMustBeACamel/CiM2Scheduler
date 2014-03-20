#ifndef TIMETABLE_H_INCLUDED
#define TIMETABLE_H_INCLUDED

#include "timestamp.h"

#define DAY_NONE 0x00000000
#define DAY_MON_TO_THU 0x00000001
#define DAY_FRIDAY 0x00000002
#define DAY_SATURDAY 0x00000004
#define DAY_SUNDAY 0x00000008
#define DAY_EVERY_DAY 0x00000F

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
        typedef unsigned int DayType;
        typedef TimeStamp TimeStampType;
        Plan()
            :_begin(0), _end(0), _interval(0), _days(DAY_NONE)
        {    }

        Plan(const TimeStampType& begin, const TimeStampType& end, const TimeStampType& interval, DayType daymask)
            : _begin(begin), _end(end), _interval(interval), _days(daymask)
        {
            _begin.normalize();
            _end.normalize();
        }

        TimeStampType& getBegin()
        {
            return _begin;
        }
        const TimeStampType& getBegin() const
        {
            return _begin;
        }
        TimeStampType& getEnd()
        {
            return _end;
        }
        const TimeStampType& getEnd() const
        {
            return _end;
        }
        TimeStampType& getInterval()
        {
            return _interval;
        }
        const TimeStampType& getInterval() const
        {
            return _interval;
        }


    private:
        TimeStampType _begin;
        TimeStampType _end;
        TimeStampType _interval;

        DayType _days;
    };
    typedef Plan PlanType;

    //------------------------------------------------------------------------------------------

    Timetable()
    {
        _plans[PLAN_WEEKDAY] = Plan(TimeStamp(6, 0), TimeStamp(22, 0), TimeStamp(2, 0), DAY_MON_TO_THU | DAY_FRIDAY);
        _plans[PLAN_MORNING_RUSH] = Plan(TimeStamp(7, 0), TimeStamp(7, 30), TimeStamp(2, 0), DAY_MON_TO_THU | DAY_FRIDAY);
        _plans[PLAN_EVENING_RUSH] = Plan(TimeStamp(17, 0), TimeStamp(17, 30), TimeStamp(2, 0), DAY_MON_TO_THU | DAY_FRIDAY);
        _plans[PLAN_WEEKEND] = Plan(TimeStamp(6, 0), TimeStamp(21, 0), TimeStamp(3, 0), DAY_SATURDAY | DAY_SUNDAY);
        _plans[PLAN_NIGHT] = Plan(TimeStamp(0, 0), TimeStamp(3, 0), TimeStamp(3, 0), DAY_EVERY_DAY);
        _plans[PLAN_CUSTOM] = Plan(TimeStamp(0, 0), TimeStamp(0, 0), TimeStamp(0, 0), DAY_NONE);
    }

    Plan& getPlan(const PlanName& plan)
    {
        return _plans[plan];
    }
    const Plan& getPlan(const PlanName& plan) const
    {
        return _plans[plan];
    }


private:
    PlanType _plans[PLAN_NUM];



};

#endif // TIMETABLE_H_INCLUDED
