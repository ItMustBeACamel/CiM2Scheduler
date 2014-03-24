#include "timestamp.h"

#include <sstream>


// Constructors

Time::Time()
    : time(0)
{   }

Time::Time(ValueType t)
    : time(t)
{   }

Time::Time(HourType hour, MinuteType minute)
    : time(hour * TIME_SLICES_PER_HOUR + minute / TIME_SLICE_LENGTH)
{   }

Time::Time(const std::string& str)
{
    parse(str);
}

Time::Time(char const*const str)
{
    parse(str);
}

// Operators

Time Time::operator+(const Time& x)const
{
    return Time(time+x.time);
}

Time& Time::operator+=(const Time& x)
{
    time+=x.time;
    return *this;
}

Time Time::operator-(const Time& x)const
{
    return Time(time-x.time);
}

Time& Time::operator-=(const Time& x)
{
    time-=x.time;
    return *this;
}

const bool Time::operator==(const Time& x)const
{
    return(time==x.time);
}

const bool Time::operator!=(const Time& x)const
{
    return(time!=x.time);
}

const bool Time::operator>(const Time& x)const
{
    return(time>x.time);
}

const bool Time::operator<(const Time& x)const
{
    return(time<x.time);
}

const bool Time::operator>=(const Time& x)const
{
    return(time>=x.time);
}

const bool Time::operator<=(const Time& x)const
{
    return(time<=x.time);
}

Time& Time::operator=(const Time& x)
{
    time = x.time;
    return *this;
}

Time& Time::operator++()
{
    ++time;
    return *this;
}

Time& Time::operator--()
{
    --time;
    return *this;
}

Time Time::operator++(int)
{
    Time temp(*this);
    ++time;
    return temp;
}

Time Time::operator--(int)
{
    Time temp(*this);
    --time;
    return temp;
}

// other

std::string Time::toString()const
{
    HourType hour = getHour();
    HourType minute = getMinute();
    std::stringstream ss;
    //if(hour < 10) ss << 0;
    ss << hour << ":";
    if(minute < 10) ss << 0;
    ss << minute;
    return ss.str();
}

void Time::parse(const char* str)
{
    parse(std::string(str));
}
void Time::parse(const std::string& str)
{
    std::stringstream ss;
    HourType h = 0;
    MinuteType m = 0;
    bool swapped = false;

    for(unsigned int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4'
                || c == '5' || c == '6' || c == '7' || c == '8'|| c == '9' )
        {
            ss << c;
        }
        else
        {
            if(c == ':' && swapped == false)
            {
                ss >> h;
                ss.clear();
                swapped = true;
            }
        }
    }

    ss >> m;

    //if(m > 59) m = 59;

    h+= m / M_PER_H;
    m = m % M_PER_H;

    time = h * TIME_SLICES_PER_HOUR + m / TIME_SLICE_LENGTH;
    return;
}

Time::HourType Time::getHour() const
{
    return time / TIME_SLICES_PER_HOUR;
}

Time::MinuteType Time::getMinute() const
{
    return ((time % TIME_SLICES_PER_HOUR) * TIME_SLICE_LENGTH);
}

Time& Time::makeDaytime()
{
    time = time % TIME_SLICES_PER_DAY;
    return *this;
}
