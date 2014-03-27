#ifndef TIMETABLE_VIEW_H_INCLUDED
#define TIMETABLE_VIEW_H_INCLUDED

#include "timetable.h"
#include <list>

class TimetableView
{
public:
    typedef Timetable TimeTableType;
    typedef TimeOffset TimeOffsetType;
    typedef TimeTableType::DayTimeType DayTimeType;
    typedef TimeTableType::IntervalType IntervalType;
    typedef WeekTime WeekTimeType;
    typedef DayName DayNameType;

    struct StopListEntry
    {
        typedef TimeTableType::PlanName PlanNameType;
        StopListEntry(const PlanNameType& p, const DayNameType& day, const WeekTimeType& t)
            : plan(p), day(day), weekTime(t)
        {

        }

        const bool operator>(const StopListEntry& x)const
        {
            if(weekTime == x.weekTime)
                return plan > x.plan;
            else
                return weekTime>x.weekTime;
        }
        const bool operator<(const StopListEntry& x)const
        {
            if(weekTime == x.weekTime)
                return plan < x.plan;
            else
                return weekTime<x.weekTime;
        }

        PlanNameType plan;
        DayNameType day;
        WeekTimeType weekTime;
    };
    typedef StopListEntry::PlanNameType PlanNameType;
    typedef std::list<StopListEntry> StopList;

    TimetableView(const TimeTableType& timeTable)
    : _timetable(timeTable), _offset(0)
    {

    }

    TimetableView(const TimeTableType& timeTable, const TimeOffsetType& offset)
    : _timetable(timeTable), _offset(offset)
    {

    }

    void setOffset(const TimeOffsetType& offset)
    {
        _offset = offset;
    }

    StopList getStopList()
    {
        StopList stopList;

        for(PlanNameType nPlan = 0; nPlan < (Timetable::PlanName)PLAN_NUM; ++nPlan)
        {
            Timetable::Plan plan(_timetable.getPlan(nPlan));

            DayTimeType planStart = plan.getStartTime();
            DayTimeType planEnd = plan.getEndTime();

            IntervalType planInterval = plan.getInterval();
            if(planInterval == IntervalType(0)) continue;

            for(DayName day = 0; day < DAY_NUM; ++day)
            {
                if(plan.activeAtDay(day))
                {
                    WeekTimeType dayStart(dayBegin(day));
                    WeekTimeType dayPlanStart(dayStart+planStart);
                    WeekTimeType dayPlanEnd;
                    if(planEnd < planStart)
                        dayPlanEnd = WeekTimeType(dayEnd(day)) + planEnd;
                    else
                        dayPlanEnd = dayPlanStart + (planEnd - planStart);

                    for(WeekTimeType t = dayPlanStart; (t <= dayPlanEnd) /*&& (t < weekEnd())*/; t+=planInterval)
                    {
                        WeekTimeType newTime(normalize(t+_offset));

                        stopList.push_back(StopListEntry(nPlan, day, newTime));
                    } // for t
                }// if plan
            }// for day
        }


        stopList.sort();
        return stopList;
    }

    WeekTimeType getPlanStart(const PlanNameType& plan, const DayName& day)
    {
        assert(day < DAY_NUM);
        return normalize(dayBegin(day) + _timetable.getPlan(plan).getStartTime() + _offset);
    }

    WeekTimeType getPlanEnd(const PlanNameType& plan, const DayName& day)
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

    bool isWithinPlan(const WeekTimeType& time, const PlanNameType& plan, const DayName& day)
    {
        WeekTimeType planStart = getPlanStart(plan, day);
        WeekTimeType planEnd = getPlanEnd(plan, day);
        if(!_timetable.getPlan(plan).activeAtDay(day)) return false;


        if(planStart <= planEnd /*&& planStart != planEnd*/)
        {
            return (time <= planEnd && time >= planStart);
        }
        else
            return (time >= planStart || time <= planEnd);
    }



private:
    TimeTableType _timetable;
    TimeOffsetType _offset;

};






#endif // TIMETABLE_VIEW_H_INCLUDED
