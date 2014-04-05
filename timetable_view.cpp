#include "timetable_view.h"

//###################################################################################
// TimetableView::StopListEntry
//###################################################################################

// Constructor

//*************************************************************************************************************
/** \brief constructor
 *
 * \param p plan to which the stop belongs
 * \param d day at which the plan started
 * \param t time of the week
 *
 */

TimetableView::StopListEntry::StopListEntry(const Timetable::PlanName& p, const DayName& d, const Time& t)
    : plan(p), day(d), weekTime(t)
{

}

// Operators

//*************************************************************************************************************
/** \brief sorting operator
 *
 * \return sorting order 1. plan 2. time
 *
 */
const bool TimetableView::StopListEntry::operator>(const TimetableView::StopListEntry& x)const
{
    if(weekTime == x.weekTime)
        return plan > x.plan;
    else
        return weekTime>x.weekTime;
}

//*************************************************************************************************************
/** \brief sorting operator
 *
 * \return sorting order 1. plan 2. time
 *
 */
const bool TimetableView::StopListEntry::operator<(const TimetableView::StopListEntry& x)const
{
    if(weekTime == x.weekTime)
        return plan < x.plan;
    else
        return weekTime<x.weekTime;
}

//###################################################################################
// TimetableView
//###################################################################################

// Constructors

//*************************************************************************************************************
/** \brief Constructor
 *
 * \param timeTable the timetable to make a view from
 * \param offset time offset
 *
 */
TimetableView::TimetableView(const Timetable& timeTable, const Time& offset)
    : _timetable(timeTable), _offset(offset)
{

}

// public members

//*************************************************************************************************************
/** \brief Constructor
 *
 * \param offset the offset to set
 * \return void
 *
 */
void TimetableView::setOffset(const Time& offset)
{
    _offset = offset;
}

// public members

//*************************************************************************************************************
/** \brief returns a list of all stops
 *
 * \return list of stops
 *
 */
TimetableView::StopList TimetableView::getStopList()
{
    StopList stopList;

    for(Timetable::PlanName nPlan = 0; nPlan < (Timetable::PlanName)PLAN_NUM; ++nPlan)
    {
        Timetable::Plan plan(_timetable.getPlan(nPlan));

        Time planStart = plan.getStartTime();
        Time planEnd = plan.getEndTime();

        Time planInterval = plan.getInterval();
        if(planInterval == Time(0)) continue;

        for(DayName day = 0; day < DAY_NUM; ++day)
        {
            if(plan.activeAtDay(day))
            {
                Time dayStart(dayBegin(day));
                Time dayPlanStart(dayStart+planStart);
                Time dayPlanEnd;
                if(planEnd < planStart)
                    dayPlanEnd = Time(dayEnd(day)) + planEnd;
                else
                    dayPlanEnd = dayPlanStart + (planEnd - planStart);

                for(Time t = dayPlanStart; (t <= dayPlanEnd); t+=planInterval)
                {
                    Time newTime(normalize(t+_offset));

                    stopList.push_back(StopListEntry(nPlan, day, newTime));
                } // for t
            }// if plan
        }// for day
    }


    stopList.sort();
    return stopList;
}

//*************************************************************************************************************
/** \brief returns the time of the week at which the plan starts at a given day
 *
 * \param plan name of the plan
 * \param day day of the week
 * \return time of the week
 *
 */
Time TimetableView::getPlanStart(const Timetable::PlanName& plan, const DayName& day)
{
    assert(day < DAY_NUM);
    return normalize(dayBegin(day) + _timetable.getPlan(plan).getStartTime() + _offset);
}

//*************************************************************************************************************
/** \brief returns the time of the week at which the plan ends at a given day
 *
 * \param plan name of the plan
 * \param day day of the week
 * \return time of the week
 *
 */
Time TimetableView::getPlanEnd(const Timetable::PlanName& plan, const DayName& day)
{
    assert(day < DAY_NUM);

    if((_timetable.getPlan(plan).getEndTime()) < (_timetable.getPlan(plan).getStartTime()))
    {
        if(day+1 >= DAY_NUM)
            return normalize((weekBegin() + _timetable.getPlan(plan).getEndTime() + _offset));
        else
        return normalize(dayBegin(day+1) + _timetable.getPlan(plan).getEndTime() + _offset);

    }
    else
        return normalize(dayBegin(day) + _timetable.getPlan(plan).getEndTime() + _offset);
}

//*************************************************************************************************************
/** \brief returns true if the given time of the week is within the given plan
 *
 * \param plan name of the plan
 * \param day day of the week
 * \return true or false
 *
 */
bool TimetableView::isWithinPlan(const Time& time, const Timetable::PlanName& plan, const DayName& day)
{
    Time planStart = getPlanStart(plan, day);
    Time planEnd = getPlanEnd(plan, day);
    if(!_timetable.getPlan(plan).activeAtDay(day)) return false;


    if(planStart <= planEnd)
    {
        return (time <= planEnd && time >= planStart);
    }
    else
        return (time >= planStart || time <= planEnd);
}
