#include "lines.h"

Lines* Lines::_instance = 0;



Line::Line(const char* n)
    : _name(n), _id(0), _number(0)
{ }

Line::Line(const std::string& n)
    : _name(n), _id(0), _number(0)
    {   }

Line::~Line()
{
    //Lines::instance()->freeID(_id);
}
