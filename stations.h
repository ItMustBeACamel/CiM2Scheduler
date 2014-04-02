#ifndef STATIONS_H_INCLUDED
#define STATIONS_H_INCLUDED

#include<list>
#include<string>
#include<stack>
#include <stdexcept>

#include "serializable.h"

#define NO_STATION -1

class Stations;

class Station : public Serializable
{
    friend class Stations;

public:
    typedef long ID;

    explicit Station(const Serializable::PropertyTree& pt);
    explicit Station(const char* n);
    explicit Station(const std::string& n);
    virtual ~Station();

    // operators
    bool operator==(const Station& x) const;

    // member-functions

    const ID& getID() const;

    void setName(const std::string& n);

    void setName(char const * const n);

    std::string& getName();

    const std::string& getName() const;

    virtual PropertyTree serialize() const;
    virtual void deserialize(const PropertyTree& pt);

private:
    std::string _name;
    ID _id;
};

typedef std::list<Station> StationList;

class Stations: public Serializable
{
    friend class Station;
public:

    static Stations* instance();
    static void destroy();
    const StationList& getStationsList() const;
    Station::ID peekNextFreeID() const;
    Station& addStation(const Station& newStation);
    Station& getStation(Station::ID id);
    const Station& getStation(Station::ID id) const;
    bool deleteStation(Station::ID id);

    // inherited from Serializable
    virtual PropertyTree serialize() const;
    virtual void deserialize(const PropertyTree& pt);

private:
    typedef std::stack<Station::ID> IDStack;

    Station::ID getNextFreeID();
    void freeID(Station::ID id);

    Stations();
    virtual ~Stations()
    {

    }

    static Stations* _instance;
    //----------------------------------
    StationList _list;
    Station::ID _idCounter;
    IDStack _idStack;
};


#endif // STATIONS_H_INCLUDED
