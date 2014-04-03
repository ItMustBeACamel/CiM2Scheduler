#include "lines.h"

// STL DEPENDENCIES
#include <sstream>
#include <cassert>
#include <stdexcept>

// BOOST DEPENDENCIES
#include <boost/foreach.hpp>

// CONSTANT DEFINITION

#define FIRST_ID 1

// Line::Stop -----------------------------------------------------------------------------

// constructors

Line::Stop::Stop()
    : station(NO_STATION), time(0)
{
}

Line::Stop::Stop(Station::ID s, const TimeStampType& t)
    : station(s), time(t)
{   }

Line::Stop::Stop(const Serializable::PropertyTree& pt)
{
    deserialize(pt);
}

// destructor


// operators

//********************************************************************************
/** \brief operator
 *
 * \detail sorts for station-ID. Sorts for time if station-IDs are equal.
 *
 */
const bool Line::Stop::operator>(const Line::Stop& x)const
{
    if(station == x.station)
        return time > x.time;
    else
        return station > x.station;
}

const bool Line::Stop::operator<(const Line::Stop& x)const
{
    if(station == x.station)
        return time < x.time;
    else
        return station < x.station;
}

const bool Line::Stop::operator==(const Line::Stop& x)const
{
    return station == x.station && time == x.time;
}

const bool Line::Stop::operator!=(const Line::Stop& x)const
{
    return station != x.station || time != x.time;
}

// members

// serialization

Serializable::PropertyTree Line::Stop::serialize() const
{
    PropertyTree pt;

    pt.put("station", station);
    pt.put("time", time.time);

    return pt;
}

void Line::Stop::deserialize(const Serializable::PropertyTree& pt)
{
    station = pt.get<Station::ID>("station");
    time = TimeStampType(pt.get<TimeStampType::ValueType>("time"));
}



// Line -----------------------------------------------------------------------------------

// Cosntructors

Line::Line(const char* name, const LineNumber& number, const IconID& icon)
    : _name(name), _id(0), _number(number), _icon(icon)
{ }

Line::Line(const std::string& name, const LineNumber& number, const IconID& icon)
    : _name(name), _id(0), _number(number), _icon(icon)
{   }

Line::Line(const PropertyTree& pt)
{
    deserialize(pt);
}

// destructor

Line::~Line()
{

}

// public members

//********************************************************************************
/** \brief returns LineID.
 *
 * \return the ID of the line
 *
 */
const Line::ID& Line::getID() const
{
    return _id;
}

//********************************************************************************
/** \brief Returns the icon used to display this line in editors
 *
 * \return Currently set iconID
 *
 */
Line::IconID& Line::getIcon()
{
    return _icon;
}

//********************************************************************************
/** \brief Const version of getIcon()
 *
 *
 */
const Line::IconID& Line::getIcon() const
{
    return _icon;
}

//********************************************************************************
/** \brief Sets the icon used to display this line in editors
 *
 * \param IconID
 *
 */
void Line::SetIcon(Line::IconID icon)
{
    _icon = icon;
}

//********************************************************************************
/** \brief Returns the number used to display the Line in editors
 *
 * \return Number
 *
 */
Line::LineNumber& Line::getNumber()
{
    return _number;
}

//********************************************************************************
/** \brief Returns the number used to display the Line in editors (const version)
 *
 * \return Number
 *
 */
const Line::LineNumber& Line::getNumber() const
{
    return _number;
}

//********************************************************************************
/** \brief Sets the number used to display the Line in editors
 *
 * \param New number to be used
 *
 */
void Line::SetNumber(Line::LineNumber number)
{
    _number = number;
}

//********************************************************************************
/** \brief Sets the name used to display the Line in editors
 *
 * \param std::string with new name
 *
 */
void Line::setName(const std::string& n)
{
    _name = std::string(n);
}

//********************************************************************************
/** \brief Sets the name used to display the Line in editors
 *
 * \param char array with new name
 *
 */
void Line::setName(char const * const n)
{
    _name = std::string(n);
}

//********************************************************************************
/** \brief Returns the name used to display the Line in editors
 *
 * \return string containing the name
 *
 */
std::string& Line::getName()
{
    return _name;
}

//********************************************************************************
/** \brief Returns the name used to display the Line in editors (const version)
 *
 * \return string containing the name
 *
 */
const std::string& Line::getName() const
{
    return _name;
}

//********************************************************************************
/** \brief Adds a Stop to the Line
 *
 * \param[in] station StationID of the station at which the line stops
 * \param[in] time time offset
 * \return pointer to the newly added stop or null if station is invalid or not existent
 *
 */
Line::Stop* Line::addStop(const Station::ID& station, const Line::Stop::TimeStampType& time)
{
    return addStop(Stop(station, time));
}

//********************************************************************************
/** \brief Adds a Stop to the Line
 *
 * \param[in] stop which should get copied into the stop-list
 * \return pointer to the newly added stop or null if stationID is invalid.
 * \details The Stop gets copied into the stop-list
 *
 */
Line::Stop* Line::addStop(const Line::Stop& stop)
{
    if(stop.station!=NO_STATION && Stations::instance()->stationExists(stop.station))
    {
        _list.push_back(stop);
        return &(_list.back());
    }
    else
        return 0;

}

//********************************************************************************
/** \brief deletes all stops at the given station
 *
 * \param[in] station StationID
 * \details removes all stops that contain the given StationID. Use it to when deleting stations
 *
 */
void Line::deleteStops(const Station::ID& station) // deletes all stops at given station
{
    for(StopList::iterator i = _list.begin(); i != _list.end(); ++i)
    {
        if((*i).station == station) i = _list.erase(i);
    }
}

//********************************************************************************
/** \brief returns a list of all the stops of this line
 *
 * \return const reference to the stop-list
 *
 */
const Line::StopList& Line::getStopsList() const
{
    return _list;
}

//********************************************************************************
/** \brief Removes all stops from the line
 */
void Line::clearStops()
{
    _list.clear();
}

//********************************************************************************
/** \brief Returns the timetable of this line
 *
 * \return reference to the timetable
 *
 */
Timetable& Line::getTimetable()
{
    return _timetable;
}

//********************************************************************************
/** \brief Returns the timetable for this line (const version)
 *
 * \return reference to the timetable
 *
 */
const Timetable& Line::getTimetable()const
{
    return _timetable;
}

//********************************************************************************
/** \brief Sets the timetable of this line
 *
 * \param[in] new timetable for this line
 *
 */
void Line::setTimetable(const Timetable& tt)
{
    _timetable = tt;
}

//********************************************************************************
/** \brief used for serialization
 *
 *
 */
Serializable::PropertyTree Line::serialize() const
{
    PropertyTree pt;

    pt.put("id", _id);
    pt.put("number", _number);
    pt.put("name", _name);
    pt.put("icon", _icon);
    pt.put_child("timetable", _timetable.serialize());

    BOOST_FOREACH(const Stop& stop, _list)
    pt.add_child("stops.stop", stop.serialize());
    return pt;
}

//********************************************************************************
/** \brief used for serialization
 *
 *
 */
void Line::deserialize(const Serializable::PropertyTree& pt)
{
    _id = pt.get<ID>("id");
    _number = pt.get<LineNumber>("number", 0);
    _name = pt.get<std::string>("name");
    _icon = pt.get<IconID>("icon");

    _timetable = Timetable(pt.get_child("timetable"));

    boost::optional<PropertyTree> stops;
    stops = pt.get_child_optional("stops");

    if(stops)
    {
        for(PropertyTree::iterator stop = stops.get().begin(); stop != stops.get().end(); ++stop)
            _list.push_back(Stop((*stop).second));
    }
}


// #########################################################################################
// Lines -----------------------------------------------------------------------------------
// #########################################################################################

// constructors

Lines::Lines()
    : _idCounter(FIRST_ID)
{

}

// destructor

Lines::~Lines()
{

}

// public members

//********************************************************************************
/** \brief Returns the next free line-ID
 *
 * \return next free line-ID
 *
 */
Line::ID    Lines::peekNextFreeID() const
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

//********************************************************************************
/** \brief adds a new Line
 *
 * \param[in] newLine reference to line that should be added
 * \return reference to the newly added line
 * \detail the line is copied, assigned to the next free line-id and added to the line-list.
 *
 */
Line& Lines::addLine(const Line& newLine)
{
    _list.push_back(newLine);

    Line line = _list.back();
    _list.back()._id = getNextFreeID();
    return _list.back();
}

//********************************************************************************
/** \brief returns the line with the line-ID
 *
 * \param[in] id id of the searched line
 * \return reference to the line if existent
 * \throws std::invalid_argument if line does not exist
 *
 */
Line& Lines::getLine(Line::ID id)
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

//********************************************************************************
/** \brief returns the line with the line-ID (const version)
 *
 * \param[in] id id of the searched line
 * \return const reference to the line if existent
 * \throws std::invalid_argument if line does not exist
 *
 */
const Line& Lines::getLine(Line::ID id)const
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

//********************************************************************************
/** \brief returns a list of all lines
 *
 * \return const reference to a list of all the lines
 *
 */
const Lines::LineList& Lines::getLinesList() const
{
    return _list;
}

//********************************************************************************
/** \brief returns the list of all lines
 *
 * \return reference to the lines list
 *
 */
Lines::LineList& Lines::getLinesList()
{
    return _list;
}

//********************************************************************************
/** \brief deletes all stops at the given station
 *
 * \param[in] station station-ID
 * \detail deletes stops in all lines by calling Line::deleteStops(const Station::ID&) . Gets called by Stations::deleteStation(Station::ID)
 *
 */
void Lines::deleteStops(Station::ID station) // deletes all stops at given station in all lines
{
    LineList::iterator i = _list.begin();
    while(i != _list.end())
    {
        (*i).deleteStops(station);
        ++i;
    }
}

// serialization

//********************************************************************************
/** \brief used for serialization
 */
Serializable::PropertyTree Lines::serialize() const
{
    PropertyTree pt;

    pt.put("id-counter", _idCounter);

    BOOST_FOREACH(const Line& i, _list)
    {
        pt.add_child("lines.line", i.serialize());
    }

    IDStack stackCopy(_idStack);

    while(stackCopy.size() > 0)
    {
        pt.add("id-stack.id", stackCopy.top());
        stackCopy.pop();
    }
    return pt;
}

//********************************************************************************
/** \brief used for serialization
 */
void Lines::deserialize(const Serializable::PropertyTree& pt)
{
    //using boost::property_tree::ptree;
    _idCounter = pt.get<Line::ID>("id-counter");

    boost::optional<PropertyTree> idLinesTree;
    idLinesTree = pt.get_child_optional("lines");

    if(idLinesTree)
    {
        for(PropertyTree::iterator i = idLinesTree.get().begin(); i != idLinesTree.get().end(); ++i)
        {
            _list.push_back(Line((*i).second));
        }
    }



    boost::optional<PropertyTree> idStackTree;
    idStackTree = pt.get_child_optional("id-stack");

    if(idStackTree)
    {
        for(PropertyTree::reverse_iterator i = idStackTree.get().rbegin(); i != idStackTree.get().rend(); ++i)
        {
            _idStack.push((*i).second.get_value<Line::ID>());
        }
    }

}

// private members

Line::ID Lines::getNextFreeID()
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

void Lines::freeID(Line::ID id)
{
    _idStack.push(id);
}

// static members

//********************************************************************************
/** \brief Returns the singleton instance
 *
 * \return pointer to singleton instance
 *
 */
Lines* Lines::instance()
{
    if(!_instance) _instance = new Lines;
    return _instance;
}

//********************************************************************************
/** \brief destroys the singleton instance
 */
void Lines::destroy()
{
    if(_instance) delete _instance;
    _instance = 0;
}

Lines* Lines::_instance = 0;



