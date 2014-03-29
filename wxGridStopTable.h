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
        : wxGridTableBase(), _rows(H_PER_DAY), _cols(DAY_NUM), _cells(_rows * _cols)
    {

    }

    virtual int GetNumberRows()
    {
        return _rows;
    }

    virtual int GetNumberCols()
    {
        return _cols;
    }

    virtual void SetValue (int row, int col, const wxString& value )
    {

    }

    virtual wxString GetValue (int row, int col)
    {
        ItemList items = getCell(row, col);

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

    virtual void * 	GetValueAsCustom (int row, int col, const wxString &typeName)
    {
        if(typeName == STOP_ITEM_LIST)
        {
            if(row >= 0 && row < GetNumberRows() && col >= 0 && col < GetNumberCols())
            {
                return (void*) &getCell(row, col);
            }
            else return (void*)0;

        }
        else
            return wxGridTableBase::GetValueAsCustom(row, col, typeName);
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

        _cells = CellList(_rows * _cols);

        for(ItemList::iterator item = newItems.begin(); item != newItems.end(); ++item)
        {
            _cells[(*item).stop.weekTime.getHour()].push_back((*item));
        }

        for(int i = 0; i < (_rows * _cols); ++i)
            _cells[i].sort();


    }

    virtual wxString 	GetRowLabelValue (int row)
    {
        std::stringstream ss;
        ss << row;
        return ss.str();
    }

    virtual wxString 	GetColLabelValue (int col)
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

private:

    ItemList& getCell(const int& row, const int& col)
    {
        return _cells[col * H_PER_DAY + row];
    }

    int _rows;
    int _cols;
    StationStopList _stopList;
    CellList _cells;


};


#endif // WXGRIDSTOPTABLE_H_INCLUDED
