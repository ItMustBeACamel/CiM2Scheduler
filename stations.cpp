#include "stations.h"
#include "lines.h"
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/property_tree/exceptions.hpp>

//using namespace Station;


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

Station::Station(const Serializable::PropertyTree& pt)
{
    deserialize(pt);
}

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



Serializable::PropertyTree Station::serialize() const
{
    PropertyTree pt;

     pt.put("id", _id);
     pt.put("name", _name);

     return pt;
}

void Station::deserialize(const Serializable::PropertyTree& pt)
{
    _id = pt.get<ID>("id");
    _name = pt.get<std::string>("name", std::string("station"));
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
    _instance = 0;
}

const StationList& Stations::getStationsList() const
{
    return _list;
}

Station& Stations::addStation(const Station& newStation)
{
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

Serializable::PropertyTree Stations::serialize() const
{
    PropertyTree pt;

    pt.put("id-counter", _idCounter);

    BOOST_FOREACH(const Station& i, _list)
    {
        pt.add_child("stations.station", i.serialize());
    }

    IDStack stackCopy(_idStack);

    while(stackCopy.size() > 0)
    {
        pt.add("id-stack.id", stackCopy.top());
        stackCopy.pop();
    }

    return pt;
}

void Stations::deserialize(const Serializable::PropertyTree& pt)
{
        _idCounter = pt.get<Station::ID>("id-counter");

        boost::optional<PropertyTree> stationsTree;
        stationsTree = pt.get_child_optional("stations");

        if(stationsTree)
        {
            for(PropertyTree::iterator i = stationsTree.get().begin(); i != stationsTree.get().end(); ++i)
            {
                _list.push_back(Station((*i).second));
            }
        }


        boost::optional<PropertyTree> idStackTree;
        idStackTree = pt.get_child_optional("id-stack");

        if(idStackTree)
        {
            for(PropertyTree::reverse_iterator i = idStackTree.get().rbegin(); i != idStackTree.get().rend(); ++i)
            {
                _idStack.push((*i).second.get_value<Station::ID>());
            }
        }
}
