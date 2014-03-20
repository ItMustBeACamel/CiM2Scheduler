#ifndef STATIONS_H_INCLUDED
#define STATIONS_H_INCLUDED

#include<list>
#include<string>
#include<stack>
#include <stdexcept>

#define NO_STATION -1

class Stations;

class Station
{
    friend class Stations;

public:
    typedef long ID;

    explicit Station(const char* n);
    explicit Station(const std::string& n);
    ~Station();

    // operators
    bool operator==(const Station& x) const
    {
        return(_id == x._id);
    }

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

private:
    std::string _name;
    ID _id;
};

typedef std::list<Station> StationList;

class Stations
{
    friend class Station;
public:

    static Stations* instance()
    {
        if(!_instance) _instance = new Stations;
        return _instance;
    }

    static void destroy()
    {
        if(_instance) delete _instance;
    }

    const StationList& getStationsList() const
    {
        return _list;
    }

    Station::ID peekNextFreeID() const;

    Station& addStation(const Station& newStation)
    {
        //newStation._id = getNextFreeID();
        _list.push_back(newStation);

        Station& s = _list.back();
        s._id = getNextFreeID();
        return s;
    }

    Station& getStation(Station::ID id);
    const Station& getStation(Station::ID id) const;

    bool deleteStation(Station::ID id);

private:

    Station::ID getNextFreeID();
    void freeID(Station::ID id);

    Stations()
        : _idCounter(1)
    {   }

    static Stations* _instance;
    //----------------------------------
    StationList _list;
    Station::ID _idCounter;
    std::stack<Station::ID> _idStack;
};


#endif // STATIONS_H_INCLUDED
