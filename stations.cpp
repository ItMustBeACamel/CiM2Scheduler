#include "stations.h"
#include "lines.h"
#include <sstream>



// Stations

Stations* Stations::_instance = 0;


Station::Station(const char* n)
    : _name(n), _id(NO_STATION)
{   }

Station::Station(const std::string& n)
    : _name(n), _id(NO_STATION)
{   }

Station::~Station()
{

}


Station::ID Stations::peekNextFreeID() const
{
    Station::ID newID;
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

Station::ID Stations::getNextFreeID()
{
    Station::ID newID;
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

Station& Stations::getStation(Station::ID id)
{
    for(StationList::iterator i = _list.begin(); i != _list.end(); ++i)
    {
        if((*i)._id == id)
        {
            return (*i);
        }
    }
    std::stringstream ss;
    ss << "invalid station-id: " << id;
    throw std::invalid_argument(ss.str());
}

const Station& Stations::getStation(Station::ID id) const
{
    for(StationList::const_iterator i = _list.begin(); i != _list.end(); ++i)
    {
        if((*i)._id == id)
        {
            return (*i);
        }
    }
    std::stringstream ss;
    ss << "invalid station-id: " << id;
    throw std::invalid_argument(ss.str());
}


bool Stations::deleteStation(Station::ID id)
{
    for(StationList::iterator i = _list.begin(); i != _list.end(); ++i)
    {
        if((*i)._id == id)
        {
            Lines::instance()->deleteStops((*i).getID());
            freeID((*i)._id);
            _list.erase(i);
            return true;
        }
    }
    return false;
}


void Stations::freeID(Station::ID id)
{
    _idStack.push(id);
}
