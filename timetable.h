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

        // constructors

        Plan();
        Plan(const DayTimeType& startTime, const DayTimeType& endTime, const TimeInterval& interval, DayFlags daymask);
        Plan(const PropertyTree& pt);

        void setStartTime(const Time& startTime);
        Time& getStartTime();
        const Time& getStartTime() const;

        void setEndTime(const Time& endTime);
        Time& getEndTime();
        const Time& getEndTime() const;

        void setInterval(const Time& interval);
        Time& getInterval();
        const Time& getInterval() const;

        const bool activeAtDay(const DayName& day) const;
        const bool activeAtDays(const DayFlags& days)const;

        void activateDays(const DayFlags& days);
        void activateDay(const DayName& day);

        void deactivateDays(const DayFlags& days);
        void deactivateDay(const DayName& day);

        void toggleDays(const DayFlags& days);
        void toggleDay(const DayName& day);

        virtual PropertyTree serialize() const;
        virtual void deserialize(const PropertyTree& pt);


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

    // Constructors
    Timetable();
    Timetable(const PropertyTree& pt);

    // public members

    Plan& getPlan(const PlanName& plan);
    const Plan& getPlan(const PlanName& plan) const;

    inline Time getEndOfWeek() const;


    virtual PropertyTree serialize() const;
    virtual void deserialize(const PropertyTree& pt);

private:
    PlanType _plans[PLAN_NUM];



};

#endif // TIMETABLE_H_INCLUDED
