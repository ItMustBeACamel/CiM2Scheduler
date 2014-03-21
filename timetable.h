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
        //typedef unsigned int DayType;
        typedef TimeStamp TimeStampType;
        Plan()
            :_begin(0), _end(0), _interval(0), _days(F_DAY_NONE)
        {    }

        Plan(const TimeStampType& begin, const TimeStampType& end, const TimeStampType& interval, DayFlags daymask)
            : _begin(begin), _end(end), _interval(interval), _days(daymask)
        {
            _begin.normalize();
            _end.normalize();
        }
        void setBegin(const TimeStamp& begin)
        {
            _begin = begin;
        }
        TimeStampType& getBegin()
        {
            return _begin;
        }
        const TimeStampType& getBegin() const
        {
            return _begin;
        }
        void setEnd(const TimeStamp& end)
        {
            _end = end;
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
        TimeStampType _begin;
        TimeStampType _end;
        TimeStampType _interval;

        DayFlags _days;
    };
    typedef Plan PlanType;

    //------------------------------------------------------------------------------------------

    Timetable()
    {
        _plans[PLAN_WEEKDAY] = Plan(TimeStamp(6, 0), TimeStamp(22, 0), TimeStamp(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_MORNING_RUSH] = Plan(TimeStamp(7, 0), TimeStamp(7, 30), TimeStamp(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_EVENING_RUSH] = Plan(TimeStamp(17, 0), TimeStamp(17, 30), TimeStamp(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_WEEKEND] = Plan(TimeStamp(6, 0), TimeStamp(21, 0), TimeStamp(3, 0), F_DAY_SATURDAY | F_DAY_SUNDAY);
        _plans[PLAN_NIGHT] = Plan(TimeStamp(0, 0), TimeStamp(3, 0), TimeStamp(3, 0), F_DAY_EVERY_DAY);
        _plans[PLAN_CUSTOM] = Plan(TimeStamp(0, 0), TimeStamp(0, 0), TimeStamp(0, 0), F_DAY_NONE);
    }

    Plan& getPlan(const PlanName& plan)
    {
        return _plans[plan];
    }
    const Plan& getPlan(const unsigned int& plan) const
    {
        return _plans[plan];
    }


private:
    PlanType _plans[PLAN_NUM];



};

#endif // TIMETABLE_H_INCLUDED
