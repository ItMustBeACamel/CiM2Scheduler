#ifndef SERIALIZE_H_INCLUDED
#define SERIALIZE_H_INCLUDED


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/property_tree/ptree.hpp>

#pragma GCC diagnostic pop



class Serializable
{
public:

    virtual ~Serializable()
    {

    }

    typedef boost::property_tree::ptree PropertyTree;

    virtual PropertyTree serialize() const = 0;
    virtual void deserialize(const PropertyTree& pt) = 0;

};


#endif // SERIALIZE_H_INCLUDED
