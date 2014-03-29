#ifndef LINES_H_INCLUDED
#define LINES_H_INCLUDED

#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include "stations.h"
#include "timestamp.h"
#include "timetable.h"
#include <stdexcept>

#define IID_NO_ICON  -1
#define IID_BUS       0
#define IID_TROLLEY   1
#define IID_TRAM      2
#define IID_METRO     3
#define IID_BOAT      4
#define IID_MONORAIL  5

class Line;

class Line
{
    friend class Lines;

public:
    typedef unsigned int ID;
    typedef unsigned int LineNumber;
    typedef int IconID;

    struct Stop
    {
        typedef TimeOffset TimeStampType;
        Stop() : station(0), time(0) {}
        Stop(Station::ID s, const TimeStampType& t)
            : station(s), time(t)
        {   }

        const bool operator>(const Stop& x)const
        {
            if(station == x.station)
                return time > x.time;
            else
                return station > x.station;
        }

        const bool operator<(const Stop& x)const
        {
            if(station == x.station)
                return time < x.time;
            else
                return station < x.station;
        }

        const bool operator==(const Stop& x)const
        {
            return station == x.station && time == x.time;
        }

        Station::ID station;
        TimeStampType time;
    };
    typedef std::list<Stop> StopList;

    explicit Line(const char* n, const IconID& icon = IID_NO_ICON);
    explicit Line(const std::string& n, const IconID& icon = IID_NO_ICON);

    ~Line();
    /*
        ID& getID()
        {
            return _id;
        }
    */
    const ID& getID() const
    {
        return _id;
    }

    IconID& getIcon()
    {
        return _icon;
    }
    const IconID& getIcon() const
    {
        return _icon;
    }
    void SetIcon(IconID icon)
    {
        _icon = icon;
    }


    LineNumber& getNumber()
    {
        return _number;
    }
    const LineNumber& getNumber() const
    {
        return _number;
    }
    void SetNumber(LineNumber number)
    {
        _number = number;
    }
    void setName(const std::string& n)
    {
        _name = std::string(n);
    }
    void setName(char const * const n)
    {
        _name = std::string(n);
    }

    std::string& getName()
    {
        return _name;
    }
    const std::string& getName() const
    {
        return _name;
    }

    Stop* addStop(const Station::ID& station, const Stop::TimeStampType& time)
    {
        assert(station!=NO_STATION);
        _list.push_back(Stop(station, time));
        return &(_list.back());
    }

    Stop* addStop(const Stop& stop)
    {
        assert(stop.station!=NO_STATION);
        _list.push_back(stop);
        return &(_list.back());
    }

    void deleteStops(Station::ID station) // deletes all stops at given station
    {
        for(StopList::iterator i = _list.begin(); i != _list.end(); ++i)
        {
            if((*i).station == station) i = _list.erase(i);
        }
    }

    const StopList& getStopsList() const
    {
        return _list;
    }

    void clearStops()
    {
        _list.clear();
    }

    Timetable& getTimetable()
    {
        return _timetable;
    }
    const Timetable& getTimetable()const
    {
        return _timetable;
    }
    void setTimetable(const Timetable& tt)
    {
        _timetable = tt;
    }

private:
    std::string _name;
    ID _id;
    LineNumber _number;
    StopList _list;
    Timetable _timetable;
    IconID _icon;
};

typedef std::list<Line> LineList;

class Lines
{
    friend class Line;
public:

    static Lines* instance()
    {
        if(!_instance) _instance = new Lines;
        return _instance;
    }
    static void destroy();

    Line::ID peekNextFreeID()
    {
        Line::ID newID;
        if(_idStack.empty())
        {
            newID = _idCounter;
        }
        else
        {
            newID = _idStack.top();
        }
        return newID;
    }

    Line& addLine(const Line& newLine)
    {
        //newLine._id = getNextFreeID();
        _list.push_back(newLine);

        Line line = _list.back();
        _list.back()._id = getNextFreeID();
        return _list.back();
    }

    Line& getLine(Line::ID id)
    {
        for(LineList::iterator i = _list.begin(); i != _list.end(); ++i)
        {
            if((*i)._id == id)
            {
                return (*i);
            }
        }
        std::stringstream ss;
        ss << "invalid line-id: " << id;
        throw std::invalid_argument(ss.str());
    }

    const Line& getLine(Line::ID id)const
    {
        for(LineList::const_iterator i = _list.begin(); i != _list.end(); ++i)
        {
            if((*i)._id == id)
            {
                return (*i);
            }

        }
        std::stringstream ss;
        ss << "invalid line-id: " << id;
        throw std::invalid_argument(ss.str());
    }

    const LineList& getLinesList() const
    {
        return _list;
    }

    LineList& getLinesList()
    {
        return _list;
    }

    void deleteStops(Station::ID station) // deletes all stops at given station in all lines
    {
        LineList::iterator i = _list.begin();
        while(i != _list.end())
        {
            (*i).deleteStops(station);
            ++i;
        }
    }

private:
    Lines()
        : _idCounter(1)
    {

    }

    Line::ID getNextFreeID()
    {
        Line::ID newID;
        if(_idStack.empty())
        {
            newID = _idCounter;
            ++_idCounter;
        }
        else
        {
            newID = _idStack.top();
            _idStack.pop();
        }
        return newID;
    }

    void freeID(Line::ID id)
    {
        _idStack.push(id);
    }

    static Lines* _instance;
    LineList _list;
    Line::ID _idCounter;
    std::stack<Line::ID> _idStack;


};



#endif // LINES_H_INCLUDED
