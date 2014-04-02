#ifndef TIMETABLE_H_INCLUDED
#define TIMETABLE_H_INCLUDED

#include "timestamp.h"
#include "serializable.h"

#include <cassert>

enum E_Days
{
    DAY_MONDAY,
    DAY_TUESDAY,
    DAY_WEDNESDAY,
    DAY_THURSDAY,
    DAY_FRIDAY,
    DAY_SATURDAY,
    DAY_SUNDAY,
    DAY_NUM
};

#define TIME_SLICES_PER_WEEK    (TIME_SLICES_PER_DAY * DAY_NUM)


#define F_DAY_NONE          0x00000000
#define F_DAY_MON_TO_THU    0x0000000F
#define F_DAY_MONDAY        0x00000001
#define F_DAY_TUESDAY       0x00000002
#define F_DAY_WEDNESDAY     0x00000004
#define F_DAY_THURSDAY      0x00000008
#define F_DAY_FRIDAY        0x00000010
#define F_DAY_SATURDAY      0x00000020
#define F_DAY_SUNDAY        0x00000040
#define F_DAY_EVERY_DAY     0xFFFFFFFF

#define F_DAY_FIRST_DAY 0x00000001
#define F_DAY_LAST_DAY 0x00000040

typedef unsigned int DayFlags;
typedef unsigned int DayName;

enum E_PlanLabel
{
    PLAN_WEEKDAY,
    PLAN_MORNING_RUSH,
    PLAN_EVENING_RUSH,
    PLAN_WEEKEND,
    PLAN_NIGHT,
    PLAN_CUSTOM,
    PLAN_NUM
};

/*
std::string PlanLab[] =
{
    std::string("Weekday"),
    std::string("Morning Rush"),
    std::string("Evening Rush"),
    std::string("Weekend"),
    std::string("Night"),
    std::string("Custom")
};
*/
/** \brief
 *
 * \return the first time slice of the week
 *
 */
inline WeekTime weekBegin()
{
    return WeekTime(0);
}

inline WeekTime weekEnd() /**< returns the time slice after the last time slice of the week*/
{
    return WeekTime(TIME_SLICES_PER_WEEK);
}

inline WeekTime dayBegin(const DayName& day) // returns the first time slice of the given day
{
    assert(day < DAY_NUM);
    return WeekTime(TIME_SLICES_PER_DAY * day);
}

inline WeekTime dayEnd(const DayName& day) // returns the time slice after the last slice of the given day
{
    assert(day < DAY_NUM);
    return WeekTime(TIME_SLICES_PER_DAY * (day+1));
}

inline WeekTime normalize(const WeekTime& weekTime)
{
    return WeekTime(weekTime.time % TIME_SLICES_PER_WEEK);
}

inline DayName getDayFromWeekTime(const WeekTime& time)
{
    return time.time / TIME_SLICES_PER_DAY;
}

/** \brief
 * Class representing a timetable
 *
 */
class Timetable : public Serializable
{
public:

    class Plan : public Serializable
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
            _startTime.makeDaytime();
            _endTime.makeDaytime();
        }
        Plan(const PropertyTree& pt)
        {
            deserialize(pt);
        }
        void setStartTime(const DayTimeType& startTime)
        {
            _startTime = startTime;
            _startTime.makeDaytime();
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
            _endTime.makeDaytime();
        }
        DayTimeType& getEndTime()
        {
            return _endTime;
        }
        const DayTimeType& getEndTime() const
        {
            return _endTime;
        }
        void setInterval(const IntervalType& interval)
        {
            _interval = interval;
        }
        TimeInterval& getInterval()
        {
            return _interval;
        }
        const TimeInterval& getInterval() const
        {
            return _interval;
        }

        const bool activeAtDay(const DayName& day)const /**< returns true if the given day is active in the plan */
        {
            assert(day < DAY_NUM);
            return _days & (1 << day);
        }

        const bool activeAtDays(const DayFlags& days)const /**< returns true if all the given days are active in the plan */
        {
            return (_days | days) == _days;
        }

        void activateDays(const DayFlags& days)
        {
            _days = _days | days;
        }

        void activateDay(const DayName& day)
        {
            activateDays((1 << day));
        }

        void deactivateDays(const DayFlags& days)
        {
            _days = _days & ~days;
        }

        void deactivateDay(const DayName& day)
        {
            deactivateDays((1 << day));
        }

        void toggleDays(const DayFlags& days)
        {
            _days = _days ^ days;
        }

        void toggleDay(const DayName& day)
        {
            toggleDays((1 << day));
        }

        virtual PropertyTree serialize() const
        {
            PropertyTree pt;

            pt.put("start-time", _startTime.time);
            pt.put("end-time", _endTime.time);
            pt.put("interval", _interval.time);
            pt.put("days", _days);
            return pt;
        }

        virtual void deserialize(const PropertyTree& pt)
        {
            _startTime = DayTimeType(pt.get<DayTimeType::ValueType>("start-time"));
            _endTime = DayTimeType(pt.get<DayTimeType::ValueType>("end-time"));
            _interval = IntervalType(pt.get<IntervalType::ValueType>("interval"));
            _days = pt.get<DayFlags>("days");
        }

    private:
        DayTimeType _startTime;
        DayTimeType _endTime;
        IntervalType _interval;

        DayFlags _days;
    };

    //------------------------------------------------------------------------------------------

    typedef Plan PlanType;
    typedef unsigned int PlanName;
    typedef PlanType::DayTimeType DayTimeType;
    typedef PlanType::IntervalType IntervalType;

    Timetable()
    {
        _plans[PLAN_WEEKDAY] = Plan(DayTimeType(6, 0), DayTimeType(22, 0), IntervalType(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_MORNING_RUSH] = Plan(DayTimeType(7, 0), DayTimeType(7, 30), IntervalType(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_EVENING_RUSH] = Plan(DayTimeType(17, 0), DayTimeType(17, 30), IntervalType(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
        _plans[PLAN_WEEKEND] = Plan(PlanType::DayTimeType(6, 0), PlanType::DayTimeType(21, 0), IntervalType(3, 0), F_DAY_SATURDAY | F_DAY_SUNDAY);
        _plans[PLAN_NIGHT] = Plan(DayTimeType(0, 0), DayTimeType(3, 0), IntervalType(3, 0), F_DAY_EVERY_DAY);
        _plans[PLAN_CUSTOM] = Plan(DayTimeType(0, 0), DayTimeType(0, 0), IntervalType(0, 0), F_DAY_NONE);
    }

    Timetable(const PropertyTree& pt)
    {
        deserialize(pt);
    }

    Plan& getPlan(const PlanName& plan)
    {
        return _plans[plan];
    }
    const Plan& getPlan(const PlanName& plan) const
    {
        return _plans[plan];
    }


    inline WeekTime getEndOfWeek() /**< returns the last TimeStamp of the week +1 */
    {
        return WeekTime(TIME_RESOLUTION * DAY_NUM);
    }

    virtual PropertyTree serialize() const
        {
            PropertyTree pt;

            pt.put_child("plans.weekday", _plans[PLAN_WEEKDAY].serialize());
            pt.put_child("plans.morning-rush", _plans[PLAN_MORNING_RUSH].serialize());
            pt.put_child("plans.evening-rush", _plans[PLAN_EVENING_RUSH].serialize());
            pt.put_child("plans.weekend", _plans[PLAN_WEEKEND].serialize());
            pt.put_child("plans.night", _plans[PLAN_NIGHT].serialize());
            pt.put_child("plans.custom", _plans[PLAN_CUSTOM].serialize());

            return pt;
        }

        virtual void deserialize(const PropertyTree& pt)
        {
            _plans[PLAN_WEEKDAY] = Plan(pt.get_child("plans.weekday"));
            _plans[PLAN_MORNING_RUSH] = Plan(pt.get_child("plans.morning-rush"));
            _plans[PLAN_EVENING_RUSH] = Plan(pt.get_child("plans.evening-rush"));
            _plans[PLAN_WEEKEND] = Plan(pt.get_child("plans.weekend"));
            _plans[PLAN_NIGHT] = Plan(pt.get_child("plans.night"));
            _plans[PLAN_CUSTOM] = Plan(pt.get_child("plans.custom"));

        }


private:
    PlanType _plans[PLAN_NUM];



};

#endif // TIMETABLE_H_INCLUDED
