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

    struct StopListEntry
    {
        typedef TimeTableType::PlanName PlanNameType;
        StopListEntry(const PlanNameType& p, const WeekTimeType& t)
            : plan(p), weekTime(t)
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
        WeekTimeType weekTime;
    };
    typedef StopListEntry::PlanNameType PlanNameType;
    typedef std::list<StopListEntry> StopList;

    TimetableView(const TimeTableType& timeTable)
    : _timetable(timeTable), _offset(0)
    {

    }

    StopList operator()(const TimeOffsetType& offset)
    {
        _offset = offset;

        StopList stopList;

        for(PlanNameType nPlan = 0; nPlan < (Timetable::PlanName)PLAN_NUM; ++nPlan)
        {
            Timetable::Plan plan(_timetable.getPlan(nPlan));

            DayTimeType planStart = plan.getStartTime();
            DayTimeType planEnd = plan.getEndTime();

            IntervalType planInterval = plan.getInterval();
            if(planInterval == IntervalType(0)) continue;

            //DayFlags dayFlag = F_DAY_MON_TO_THU;

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

                    for(WeekTimeType t = dayPlanStart; (t <= dayPlanEnd) && (t < weekEnd()); t+=planInterval)
                    {
                        WeekTimeType newTime(normalize(t+_offset));

                        stopList.push_back(StopListEntry(nPlan, newTime));

                        if(day == DAY_MON_TO_THU && t >= dayEnd(day))
                        {
                            WeekTimeType wrappedTime(t);
                            wrappedTime.makeDaytime();
                            wrappedTime+= _offset;
                            stopList.push_back(StopListEntry(nPlan, wrappedTime));
                        }

                    }
                }
                //dayFlag = dayFlag << 1;
            }
        }
        stopList.sort();
        return stopList;

    }



private:
    TimeTableType _timetable;
    TimeOffsetType _offset;

};






#endif // TIMETABLE_VIEW_H_INCLUDED
