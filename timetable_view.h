#ifndef TIMETABLE_VIEW_H_INCLUDED
#define TIMETABLE_VIEW_H_INCLUDED

#include "timetable.h"

class TimetableView
{
public:
    typedef Timetable TimeTableType;
    typedef TimeOffset TimeOffsetType;
    typedef WeekTime WeekTimeType;

    struct StopListEntry
    {
        typedef TimeTableType::PlanType PlanType;
        StopListEntry(const PlanType& p, const WeekTimeType& t)
        : plan(p), WeekTime(t)
        {

        }

        PlanType plan;
        WeekTimeType weekTime;
    };
    typedef std::list<StopListEntry> StopList;

    TimetableView(const TimeTableType& timeTable)
    : _timetable(timeTable), _offset(0)
    {

    }

    StopList operator(const TimeOffsetType& offset)
    {
        _offset = offset;

        StopList stopList;

        for(Timetable::PlanName nPlan = 0; nPlan < (Timetable::PlanName)PLAN_NUM; ++nPlan)
        {
            Timetable::Plan plan(_timetable.getPlan(nPlan));

            DayTimeType planStart = plan.getStartTime();
            DayTimeType planEnd = plan.getEndTime();

            IntervalType planInterval = plan.getInterval();
            if(planInterval == IntervalType(0)) continue;

            DayFlags dayFlag = F_DAY_MON_TO_THU;

            for(unsigned int day = 0; day < DAY_NUM; ++day)
            {
                if(plan.activeAtDays(dayFlag))
                {


                    WeekTimeType dayStart(dayBegin(day));
                    WeekTimeType dayPlanStart(dayStart+planStart);
                    WeekTimeType dayPlanEnd;
                    if(planEnd < planStart)
                        dayPlanEnd = WeekTimeType(dayEnd(day)) + planEnd;
                    else
                        dayPlanEnd = dayPlanStart + (planEnd - planStart);

                    for(WeekTimeType t = dayPlanStart; (t <= dayPlanEnd) && (t < _timetable.getEndOfWeek()); t+=planInterval)
                    {
                        timeList.push_back(t);
                        if(dayFlag == F_DAY_MON_TO_THU && t >= WeekTimeType(TIME_RESOLUTION))
                            timeList.push_back(t-WeekTimeType(TIME_RESOLUTION));
                    }
                }
                dayFlag = dayFlag << 1;
            }

        }



private:
    TimeTableType _timetable;
    TimeOffsetType _offset;

};



#endif // TIMETABLE_VIEW_H_INCLUDED
