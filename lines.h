#ifndef LINES_H_INCLUDED
#define LINES_H_INCLUDED

// PROJECT DEPENDENCIES
#include "serializable.h"
#include "stations.h"
#include "timestamp.h"
#include "timetable.h"

// STL INCLUDES
#include <list>
#include <string>

//CONSTANTS DEFS
#define IID_NO_ICON  -1
#define IID_BUS       0
#define IID_TROLLEY   1
#define IID_TRAM      2
#define IID_METRO     3
#define IID_BOAT      4
#define IID_MONORAIL  5

// class Line
class Line : public Serializable
{
    friend class Lines;

public:
    typedef unsigned int ID;
    typedef unsigned int LineNumber;
    typedef int IconID;

    struct Stop : public Serializable
    {
        // typedefs
        typedef TimeOffset TimeStampType;

        // constructors
        Stop();
        Stop(Station::ID s, const TimeStampType& t);
        Stop(const PropertyTree& pt);

        // operators
        const bool operator>(const Stop& x)const;
        const bool operator<(const Stop& x)const;
        const bool operator==(const Stop& x)const;
        const bool operator!=(const Stop& x)const;

        // serialization
        virtual PropertyTree serialize() const;
        virtual void deserialize(const PropertyTree& pt);


        Station::ID station;
        TimeStampType time;
    }; // struct Stop

    typedef std::list<Stop> StopList;

    // constructors

    explicit Line(const char* name, const LineNumber& number = 0, const IconID& icon = IID_NO_ICON);
    explicit Line(const std::string& name, const LineNumber& number = 0, const IconID& icon = IID_NO_ICON);

    explicit Line(const PropertyTree& pt);

    // destructor

    ~Line();

    // public members

    const ID& getID() const;

    IconID& getIcon();
    const IconID& getIcon() const;
    void SetIcon(IconID icon);

    LineNumber& getNumber();
    const LineNumber& getNumber() const;
    void SetNumber(LineNumber number);

    void setName(const std::string& n);
    void setName(char const * const n);
    std::string& getName();
    const std::string& getName() const;

    Stop* addStop(const Station::ID& station, const Stop::TimeStampType& time);
    Stop* addStop(const Stop& stop);

    void deleteStops(const Station::ID& station); // deletes all stops at given station
    const StopList& getStopsList() const;
    void clearStops();

    Timetable& getTimetable();
    const Timetable& getTimetable()const;
    void setTimetable(const Timetable& tt);

    // serializing

    virtual PropertyTree serialize() const;
    virtual void deserialize(const PropertyTree& pt);

private:
    std::string _name;
    ID _id;
    LineNumber _number;
    StopList _list;
    Timetable _timetable;
    IconID _icon;
}; // class Line



class Lines : public Serializable
{
    friend class Line;
public:
    // public typedefs
    typedef std::list<Line> LineList;

    // static members

    static Lines* instance();
    static void destroy();

    // public members

    Line::ID peekNextFreeID() const;

    Line& addLine(const Line& newLine);
    Line& getLine(Line::ID id);
    const Line& getLine(Line::ID id)const;

    const LineList& getLinesList() const;
    LineList& getLinesList();

    void deleteStops(Station::ID station); // deletes all stops at given station in all lines

    // serialization

    Serializable::PropertyTree serialize() const;
    void deserialize(const Serializable::PropertyTree& pt);


private:
    typedef std::stack<Line::ID> IDStack;

    // constructors
    Lines();

    // destructor
    virtual ~Lines();

    //private members
    Line::ID getNextFreeID();
    void freeID(Line::ID id);


    static Lines* _instance;
    LineList _list;
    Line::ID _idCounter;
    IDStack _idStack;

}; // class Lines



#endif // LINES_H_INCLUDED
