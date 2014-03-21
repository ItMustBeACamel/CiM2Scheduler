#include "stations.h"
#include "lines.h"
#include <sstream>

// Station






// static members
Stations* Stations::_instance = 0;

// Constructors
Station::Station(const char* n)
    : _name(n), _id(NO_STATION)
{   }

Station::Station(const std::string& n)
    : _name(n), _id(NO_STATION)
{   }

Station::~Station()
{

}

// Operators

bool Station::operator==(const Station& x) const
{
    return(_id == x._id);
}

// member functions

const Station::ID& Station::getID() const
{
    return _id;
}

void Station::setName(const std::string& n)
{
    _name = std::string(n);
}
void Station::setName(char const * const n)
{
    _name = std::string(n);
}

std::string& Station::getName()
{
    return _name;
}
const std::string& Station::getName() const
{
    return _name;
}




// Stations
//-----------------------------------------------------------------------------------------

Stations::Stations()
    : _idCounter(1)
{   }

Stations* Stations::instance()
{
    if(!_instance) _instance = new Stations;
    return _instance;
}

void Stations::destroy()
{
    if(_instance) delete _instance;
}

const StationList& Stations::getStationsList() const
{
    return _list;
}

Station& Stations::addStation(const Station& newStation)
{
    //newStation._id = getNextFreeID();
    _list.push_back(newStation);

    Station& s = _list.back();
    s._id = getNextFreeID();
    return s;
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
