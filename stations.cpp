#include "stations.h"

// PROJECT DEPENDENCIES
#include "lines.h"

// STL_DEPENDENCIES
#include <sstream>
#include <stdexcept>

// BOOST DEPENDENCIES
#include <boost/foreach.hpp>
#include <boost/property_tree/exceptions.hpp>

// CONSTANT DEFINITION

#define FIRST_ID 1

// Station

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

//***************************************************************************************
/** \brief Returns the stationID
 *
 * \return const reference to the stationID
 *
 */
const Station::ID& Station::getID() const
{
    return _id;
}

//***************************************************************************************
/** \brief Sets the name of the station
 *
 * \param[in] string containing the new name
 *
 */
void Station::setName(const std::string& n)
{
    _name = std::string(n);
}

//***************************************************************************************
/** \brief Sets the name of the station
 *
 * \param[in] char array containing the new name
 *
 */
void Station::setName(char const * const n)
{
    _name = std::string(n);
}

//***************************************************************************************
/** \brief Returns the name of the station
 *
 * \return string reference containing the name of the station
 *
 */
std::string& Station::getName()
{
    return _name;
}

//***************************************************************************************
/** \brief Returns the name of the station (const version)
 *
 * \return const string reference containing the name of the station
 *
 */
const std::string& Station::getName() const
{
    return _name;
}


//***************************************************************************************
/** \brief used for serialization
 */
Serializable::PropertyTree Station::serialize() const
{
    PropertyTree pt;

    pt.put("id", _id);
    pt.put("name", _name);

    return pt;
}

//***************************************************************************************
/** \brief used for serialization
 */
void Station::deserialize(const Serializable::PropertyTree& pt)
{
    _id = pt.get<ID>("id");
    _name = pt.get<std::string>("name", std::string("station"));
}


// Stations
//-----------------------------------------------------------------------------------------

Stations::Stations()
    : _idCounter(FIRST_ID)
{   }

//***************************************************************************************
/** \brief returns a list of all stations
 *
 * \return const list of all stations
 *
 */
const StationList& Stations::getStationsList() const
{
    return _list;
}


//***************************************************************************************
/** \brief adds a new station
 *
 * \param[in] newStation station to add
 * \return reference to the newly added station
 *
 * \detail a copy of the given station is added to the station list. ID will be replaced by next free ID
 *
 */
Station& Stations::addStation(const Station& newStation)
{
    _list.push_back(newStation);

    Station& s = _list.back();
    s._id = getNextFreeID();
    return s;
}

//***************************************************************************************
/** \brief returns next free stationID
 *
 * \return next free stationID
 *
 */
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

//***************************************************************************************
/** \brief reserves the next free stationID and returns it
 *
 * \return the next free stationID
 * \detail reserves the next free ID. Use it to assign an ID when adding a new Station to the station-list
 *
 */
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

//***************************************************************************************
/** \brief returns the station with the given ID
 *
 * \param[in] id id of the station to find
 * \return reference to the found station
 *
 * \throws std::invalid_argument when ID invalid/not found
 *
 */
Station& Stations::getStation(Station::ID id)
{
    if(id == NO_STATION) throw std::invalid_argument("invalid station-id: NO_STATION");
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

//***************************************************************************************
/** \brief returns the station with the given ID (const version)
 *
 * \param[in] id id of the station to find
 * \return const reference to the found station
 *
 * \throws std::invalid_argument when ID invalid/not found
 *
 */
const Station& Stations::getStation(Station::ID id) const
{
    if(id == NO_STATION) throw std::invalid_argument("invalid station-id: NO_STATION");
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

//***************************************************************************************
/** \brief deletes the station with the given ID
 *
 * \param[in] id id of the station to delete
 * \return true when station found and deleted, false when ID is invalid
 * \detail deletes the station with the given ID and calls Lines::deleteStops(Station::ID) to delete all stops at this station
 *
 */
const bool Stations::deleteStation(Station::ID id)
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

//***************************************************************************************
/** \brief returns true if the station exists
 *
 * \param[in] station id of the station to find
 * \return true when station is found in list. Otherwise false.
 *
 */
const bool Stations::stationExists(const Station::ID& station) const
{
    for(StationList::const_iterator i = _list.begin(); i != _list.end(); ++i)
    {
        if((*i)._id == station)
        {
            return true;
        }
    }
    return false;

}

//***************************************************************************************
/** \brief frees a stationID
 *
 * \param[in] the ID to be freed
 * \detail makes a stationID available for assignment. Used when deleting stations
 *
 */
void Stations::freeID(Station::ID id)
{
    _idStack.push(id);
}

//***************************************************************************************
/** \brief used for serialization
 */
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

//***************************************************************************************
/** \brief used for serialization
 */
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

// static members
Stations* Stations::_instance = 0;

//***************************************************************************************
/** \brief returns a pointer to the singleton instance
 *
 * \return pointer to instance
 *
 */
Stations* Stations::instance()
{
    if(!_instance) _instance = new Stations;
    return _instance;
}

//***************************************************************************************
/** \brief destroys the singleton instance
 */
void Stations::destroy()
{
    if(_instance) delete _instance;
    _instance = 0;
}
