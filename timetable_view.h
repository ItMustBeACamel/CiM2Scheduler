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

        StopListEntry(const PlanNameType& p, const DayNameType& d, const WeekTimeType& t);

        const bool operator>(const StopListEntry& x)const;
        const bool operator<(const StopListEntry& x)const;

        PlanNameType plan;
        DayNameType day;
        WeekTimeType weekTime;
    };
    typedef StopListEntry::PlanNameType PlanNameType;
    typedef std::list<StopListEntry> StopList;

    TimetableView(const Timetable& timeTable, const Time& offset = Time(0));

    void setOffset(const Time& offset);

    StopList getStopList();

    WeekTimeType getPlanStart(const PlanNameType& plan, const DayName& day);
    WeekTimeType getPlanEnd(const PlanNameType& plan, const DayName& day);

    bool isWithinPlan(const WeekTimeType& time, const PlanNameType& plan, const DayName& day);




private:
    Timetable _timetable;
    Time _offset;

};






#endif // TIMETABLE_VIEW_H_INCLUDED
