#ifndef WXGRIDSTOPTABLE_H_INCLUDED
#define WXGRIDSTOPTABLE_H_INCLUDED

#include <wx/grid.h>
#include <list>
#include <vector>
#include <sstream>
#include "timetable.h"
#include "timestamp.h"
#include "lines.h"
#include "stopAtStation.h"
#include "timetable_view.h"

#define STOP_ITEM_LIST (wxString("stop item"))


class wxGridStopTable : public wxGridTableBase
{
public:
    typedef StopAtStation StationStopType;
    typedef std::list<StationStopType> StationStopList;
    typedef Timetable::PlanName PlanNameType;

    struct Item
    {
        typedef Line::ID LineIDType;
        typedef TimetableView::StopListEntry StopType;

        Item(/*const LineIDType& ln, */const StopType& s, StationStopType ss)
        : /*line(ln),*/ stop(s), stationStop(ss)
        {

        }

        bool operator>(const Item& x) const
        {
            return stop.weekTime > x.stop.weekTime;
        }

        bool operator<(const Item& x) const
        {
            return stop.weekTime < x.stop.weekTime;
        }

        Line::ID getLine()const
        {
            return stationStop.line;
        }

        //LineIDType line;
        StopType stop;
        StationStopType stationStop;
    };
    typedef std::list<Item> ItemList;
    typedef std::vector<ItemList> CellList;

    wxGridStopTable()
        : wxGridTableBase()/*, _rows(H_PER_DAY+1), _cols(DAY_NUM)*/, _cells(DAY_NUM * H_PER_DAY /*_rows * _cols*/), _currentStop(0), _currentPlan(0)
    {

    }

    virtual int GetNumberRows()
    {
        return H_PER_DAY + 1;
    }

    virtual int GetNumberCols()
    {
        return DAY_NUM;
    }

    virtual void SetValue (int row, int col, const wxString& value )
    {

    }

    virtual wxString GetValue (int row, int col)
    {
        if(row == 0)
        {
            return "xxx";
        }
        else
        {
            ItemList items = getCell(row-1, col);

            wxString str;
            std::stringstream ss;
            for(ItemList::iterator i = items.begin(); i != items.end(); ++i)
            {
                if(!ss.str().empty())
                    ss << " ";
                ss << (*i).stop.weekTime.getMinute();
            }

            return ss.str();

        }


    }

    virtual void * 	GetValueAsCustom (int row, int col, const wxString &typeName)
    {
        if(typeName == STOP_ITEM_LIST)
        {
            if(row >= 1 && row < GetNumberRows() && col >= 0 && col < GetNumberCols())
            {
                return (void*) &getCell(row - 1, col);
            }
            else return (void*)0;

        }
        else
            return wxGridTableBase::GetValueAsCustom(row, col, typeName);
    }

    virtual bool CanGetValueAs (int row, int col, const wxString &typeName)
    {
        if(typeName == wxGRID_VALUE_BOOL && row == 0)
            return true;

        if(typeName == STOP_ITEM_LIST && row != 0)
            return true;

        return false;
    }

    virtual bool 	CanSetValueAs (int row, int col, const wxString &typeName)
    {
        if(typeName == wxGRID_VALUE_BOOL && row == 0)
            return true;

        if(typeName == STOP_ITEM_LIST && row != 0)
            return true;

        return false;
    }

    virtual bool GetValueAsBool (int row, int col)
    {
        if(row == 0)
        {
            if(_currentStop != 0)
            {
                Line line = Lines::instance()->getLine(_currentStop->line);
                return line.getTimetable().getPlan(_currentPlan).activeAtDay(col);
            }

        }

        return false;
    }

    virtual void SetValueAsBool (int row, int col, bool value)
    {
        if(row == 0)
        {
            if(_currentStop != 0)
            {
                Line& line = Lines::instance()->getLine(_currentStop->line);

                if (value == true)
                    if(col <= DAY_THURSDAY)
                        line.getTimetable().getPlan(_currentPlan).activateDays(F_DAY_MON_TO_THU);
                    else
                        line.getTimetable().getPlan(_currentPlan).activateDay(col);
                else
                {
                    if(col <= DAY_THURSDAY)
                        line.getTimetable().getPlan(_currentPlan).deactivateDays(F_DAY_MON_TO_THU);
                    else
                        line.getTimetable().getPlan(_currentPlan).deactivateDay(col);
                }

                refresh();
            }

        }

    }


    StationStopType* addStop(const StationStopType& stop)
    {
        _stopList.push_back(stop);
        return &_stopList.back();
    }

    void clearStopList()
    {
        _stopList.clear();
    }

    void refresh()
    {
        ItemList newItems;

        for(StationStopList::iterator stop = _stopList.begin(); stop != _stopList.end(); ++stop)
        {
            try
            {
                const Line& line = Lines::instance()->getLine((*stop).line);

                TimetableView view(line.getTimetable(), (*stop).stop.time);

                TimetableView::StopList viewStopList = view.getStopList();

                for(TimetableView::StopList::iterator viewItem = viewStopList.begin(); viewItem != viewStopList.end(); ++viewItem)
                {
                    newItems.push_back(Item(/*line.getID(),*/ (*viewItem), (*stop)));
                }
            }
            catch(...)
            {

            }
        }

        _cells = CellList(DAY_NUM * H_PER_DAY);

        for(ItemList::iterator item = newItems.begin(); item != newItems.end(); ++item)
        {
            _cells[(*item).stop.weekTime.getHour()].push_back((*item));
        }

        for(int i = 0; i < (DAY_NUM * H_PER_DAY); ++i)
            _cells[i].sort();


    }

    virtual wxString GetRowLabelValue (int row)
    {
        if(row == 0) return "x";
        std::stringstream ss;
        ss << row-1;
        return ss.str();
    }

    virtual wxString GetColLabelValue (int col)
    {
        std::string labels[] =
        {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"
        };


        return labels[col];
    }

    void setCurrentPlan(const PlanNameType& plan)
    {
        _currentPlan = plan;
    }

    void setCurrentStop(StationStopType* stop)
    {
        _currentStop = stop;
    }

private:

    ItemList& getCell(const int& row, const int& col)
    {
        return _cells[col * H_PER_DAY + row];
    }

    //int _rows;
    //int _cols;
    StationStopList _stopList;
    CellList _cells;
    StationStopType* _currentStop;
    PlanNameType _currentPlan;


};


#endif // WXGRIDSTOPTABLE_H_INCLUDED
