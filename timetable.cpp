#include "timetable.h"

// STL dependencies
#include <stdexcept>

//#############################################################################
// Timetable::Plan
//#############################################################################


// Constructors

//**********************************************************************************
/** \brief standard constructor
 *
 *
 */
Timetable::Plan::Plan()
    :_startTime(0), _endTime(0), _interval(0), _days(F_DAY_NONE)
{    }

//**********************************************************************************
/** \brief initialize constructor
 *
 * \param[in] startTime The time of the day the Plan starts
 * \param[in] endTime The time of the day the Plan ends
 * \param[in] interval the time interval
 * \param[in] daymask The days at which the plan is active (flags)
 *
 */
Timetable::Plan::Plan(const DayTimeType& startTime, const DayTimeType& endTime, const TimeInterval& interval, DayFlags daymask)
    : _startTime(startTime), _endTime(endTime), _interval(interval), _days(daymask)
{
    _startTime.makeDaytime();
    _endTime.makeDaytime();
}

//**********************************************************************************
/** \brief deserialize constructor
 *
 * \param[in] pt PropertyTree from which to construct
 *
 */
Timetable::Plan::Plan(const Serializable::PropertyTree& pt)
{
    deserialize(pt);
}


// public members

//**********************************************************************************
/** \brief sets the start time of the plan
 *
 * \param[in] startTime Time of the day at which the Plan starts
 *
 */
void Timetable::Plan::setStartTime(const Time& startTime)
{
    _startTime = startTime;
    _startTime.makeDaytime();
}

//**********************************************************************************
/** \brief returns the start time of the plan
 *
 * \return Time of the day at which the Plan starts
 *
 */
Time& Timetable::Plan::getStartTime()
{
    return _startTime;
}

//**********************************************************************************
/** \brief returns the start time of the plan (const version)
 *
 * \return Time of the day at which the Plan starts
 *
 */
const Time& Timetable::Plan::getStartTime() const
{
    return _startTime;
}

/** \brief sets the end time of the plan
 *
 * \param[in] endTime Time of the day at which the Plan ends
 *
 */
void Timetable::Plan::setEndTime(const Time& endTime)
{
    _endTime = endTime;
    _endTime.makeDaytime();
}

//**********************************************************************************
/** \brief returns the end time of the plan
 *
 * \return Time of the day at which the Plan ends
 *
 */
Time& Timetable::Plan::getEndTime()
{
    return _endTime;
}

//**********************************************************************************
/** \brief returns the end time of the plan (const version)
 *
 * \return Time of the day at which the Plan ends
 *
 */
const Time& Timetable::Plan::getEndTime() const
{
    return _endTime;
}

//**********************************************************************************
/** \brief sets the interval of the plan
 *
 * \param[in] new interval
 *
 */
void Timetable::Plan::setInterval(const Time& interval)
{
    _interval = interval;
}

//**********************************************************************************
/** \brief returns the interval of the plan
 *
 * \return interval
 *
 */
Time& Timetable::Plan::getInterval()
{
    return _interval;
}

//**********************************************************************************
/** \brief returns the interval of the plan (const version)
 *
 * \return interval
 *
 */
const Time& Timetable::Plan::getInterval() const
{
    return _interval;
}

//**********************************************************************************
/** \brief returns true if the Plan is active at the given day
 *
 * \param[in] day name of the day
 * \return true if active at given day. False if not
 *
 */
const bool Timetable::Plan::activeAtDay(const DayName& day)const
{
    assert(day < DAY_NUM);
    return _days & (1 << day);
}

//**********************************************************************************
/** \brief returns true if the Plan is active at the given days
 *
 * \param[in] days flags
 * \return true if active at all given days. False if not
 *
 */
const bool Timetable::Plan::activeAtDays(const DayFlags& days)const
{
    return (_days | days) == _days;
}

//**********************************************************************************
/** \brief activate days
 *
 * \param[in] days flags
 * \detail Plans dayflags indicated by days will be set after calling this method
 *
 */
void Timetable::Plan::activateDays(const DayFlags& days)
{
    _days = _days | days;
}

//**********************************************************************************
/** \brief activates day
 *
 * \param[in] day The day to activate
 *
 */
void Timetable::Plan::activateDay(const DayName& day)
{
    activateDays((1 << day));
}

//**********************************************************************************
/** \brief deactivate days
 *
 * \param[in] days mask
 * \detail deactivate the days indicated by mask
 *
 */
void Timetable::Plan::deactivateDays(const DayFlags& days)
{
    _days = _days & ~days;
}

//**********************************************************************************
/** \brief deactivates day
 *
 * \param[in] day The day to deactivate
 *
 */
void Timetable::Plan::deactivateDay(const DayName& day)
{
    deactivateDays((1 << day));
}

//**********************************************************************************
/** \brief toggles the days indicated by mask
 *
 * \param[in] days mask
 *
 */
void Timetable::Plan::toggleDays(const DayFlags& days)
{
    _days = _days ^ days;
}

//**********************************************************************************
/** \brief toggles the given day
 *
 * \param[in] day day to toggle
 *
 */
void Timetable::Plan::toggleDay(const DayName& day)
{
    toggleDays((1 << day));
}

//**********************************************************************************
/** \brief serializes the Plan
 *
 *
 */
Serializable::PropertyTree Timetable::Plan::serialize() const
{
    PropertyTree pt;

    pt.put("start-time", _startTime.time);
    pt.put("end-time", _endTime.time);
    pt.put("interval", _interval.time);
    pt.put("days", _days);
    return pt;
}

//**********************************************************************************
/** \brief deserializes the Plan
 *
 *
 */
void Timetable::Plan::deserialize(const Serializable::PropertyTree& pt)
{
    _startTime = Time(pt.get<Time::ValueType>("start-time", 0));
    _endTime = Time(pt.get<Time::ValueType>("end-time", 0));
    _interval = Time(pt.get<Time::ValueType>("interval", 0));
    _days = pt.get<DayFlags>("days", F_DAY_NONE);
}


//#############################################################################
// Timetable
//#############################################################################

// constructors

//**********************************************************************************
/** \brief standard constructor
 *
 * \detail sets up a standard CiM2 timetable
 */
Timetable::Timetable()
{
    _plans[PLAN_WEEKDAY]        = Plan(Time(6, 0),  Time(22, 0),    Time(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
    _plans[PLAN_MORNING_RUSH]   = Plan(Time(7, 0),  Time(7, 30),    Time(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
    _plans[PLAN_EVENING_RUSH]   = Plan(Time(17, 0), Time(17, 30),   Time(2, 0), F_DAY_MON_TO_THU | F_DAY_FRIDAY);
    _plans[PLAN_WEEKEND]        = Plan(Time(6, 0),  Time(21, 0),    Time(3, 0), F_DAY_SATURDAY | F_DAY_SUNDAY);
    _plans[PLAN_NIGHT]          = Plan(Time(0, 0),  Time(3, 0),     Time(3, 0), F_DAY_EVERY_DAY);
    _plans[PLAN_CUSTOM]         = Plan(Time(0, 0),  Time(0, 0),     Time(0, 0), F_DAY_NONE);
}

//**********************************************************************************
/** \brief deserialize constructor
 *
 */
Timetable::Timetable(const PropertyTree& pt)
{
    deserialize(pt);
}

// public members

//**********************************************************************************
/** \brief returns a plan
 *
 * \param[in] plan plan name
 * \return reference to plan
 * \throw std::invalid_argument if plan-name is invalid
 * \detail should only be used with values of E_PlanLabel
 */
Timetable::Plan& Timetable::getPlan(const PlanName& plan)
{
    if(plan >= PLAN_NUM) throw std::invalid_argument("invalid plan");
    return _plans[plan];
}

//**********************************************************************************
/** \brief returns a plan (const version)
 *
 * \param[in] plan plan name
 * \return const reference to plan
 * \throw std::invalid_argument if plan-name is invalid
 * \detail should only be used with values of E_PlanLabel
 */
const Timetable::Plan& Timetable::getPlan(const PlanName& plan) const
{
    if(plan >= PLAN_NUM) throw std::invalid_argument("invalid plan");
    return _plans[plan];
}

//**********************************************************************************
/** \brief sets a plan
 *
 * \param[in] planName plan name
 * \param[in] plan plan
 * \throw std::invalid_argument if plan-name is invalid
 * \detail should only be used with values of E_PlanLabel
 */
void Timetable::setPlan(const PlanName& planName, const Timetable::Plan& plan)
{
    if(planName >= PLAN_NUM) throw std::invalid_argument("invalid plan name");
    _plans[planName] = plan;
}

//**********************************************************************************
/** \brief returns the last time slice of the week + 1
 *
 */
inline Time Timetable::getEndOfWeek() const
{
    return Time(TIME_SLICES_PER_DAY * DAY_NUM);
}

//**********************************************************************************
/** \brief serializes the timetable
 *
 */
Serializable::PropertyTree Timetable::serialize() const
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

//**********************************************************************************
/** \brief deserializes the timetable
 *
 */
void Timetable::deserialize(const Serializable::PropertyTree& pt)
{
    _plans[PLAN_WEEKDAY] = Plan(pt.get_child("plans.weekday"));
    _plans[PLAN_MORNING_RUSH] = Plan(pt.get_child("plans.morning-rush"));
    _plans[PLAN_EVENING_RUSH] = Plan(pt.get_child("plans.evening-rush"));
    _plans[PLAN_WEEKEND] = Plan(pt.get_child("plans.weekend"));
    _plans[PLAN_NIGHT] = Plan(pt.get_child("plans.night"));
    _plans[PLAN_CUSTOM] = Plan(pt.get_child("plans.custom"));

}
