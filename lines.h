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



class Line;

class Line
{
    friend class Lines;

public:
    typedef unsigned int ID;
    typedef unsigned int LineNumber;

    struct Stop
    {
        typedef TimeOffset TimeStampType;
        Stop() : station(0), time(0) {}
        Stop(Station::ID s, const TimeStampType& t)
            : station(s), time(t)
        {   }
        Station::ID station;
        TimeStampType time;
    };
    typedef std::vector<Stop> StopList;

    explicit Line(const char* n);
    explicit Line(const std::string& n);
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
