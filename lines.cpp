#include "lines.h"

Lines* Lines::_instance = 0;

void Lines::destroy()
{
    if(_instance) delete _instance;
    _instance = 0;
}

Line::Line(const char* n, const IconID& icon)
    : _name(n), _id(0), _number(0), _icon(icon)
{ }

Line::Line(const std::string& n, const IconID& icon)
    : _name(n), _id(0), _number(0), _icon(icon)
    {   }

Line::~Line()
{
    //Lines::instance()->freeID(_id);
}
