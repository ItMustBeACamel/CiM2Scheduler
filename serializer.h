#ifndef SERIALIZER_H_INCLUDED
#define SERIALIZER_H_INCLUDED

#include "stations.h"
#include "lines.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#pragma GCC diagnostic pop

class Serializer
{
    public:
    typedef boost::property_tree::ptree PropertyTree;

    static PropertyTree serializeSchedules()
    {
        PropertyTree pt;

        pt.add_child("save.stations", Stations::instance()->serialize());
        pt.add_child("save.lines", Lines::instance()->serialize());

        return pt;
    }

    static void deserializeSchedule(const PropertyTree& pt)
    {
        Stations::destroy();
        Lines::destroy();
        Stations::instance()->deserialize(pt.get_child("save.stations"));
        Lines::instance()->deserialize(pt.get_child("save.lines"));
    }

    static void loadScheduleFromFile(const std::string& filename)
    {
        PropertyTree pt;
        read_xml(filename, pt);

        deserializeSchedule(pt);
    }

    static void saveScheduleToFile(const std::string& filename)
    {
        write_xml(filename, serializeSchedules());
    }

};


#endif // SERIALIZER_H_INCLUDED
