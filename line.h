#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include<string>

class Line
{
public:
    Line(const unsigned int& n, const char* name="line")
        : _number(n), _name(name)
    {

    }

    std::string& getName()
    {
        return _name;
    }

private:
    std::string _name;
    unsigned int _number;


};


#endif // LINE_H_INCLUDED
