#ifndef TIMESTAMP_H_INCLUDED
#define TIMESTAMP_H_INCLUDED

#include "utils.h"

#include <string>

//some macros for better code readability
#define H_PER_DAY   24
#define M_PER_H     60
#define M_PER_DAY   1440


#define TIME_SLICES_PER_DAY 288 // the resolution of the time system in slices per day

#define TIME_RESOLUTION TIME_SLICES_PER_DAY // deprecated

#define TIME_SLICE_LENGTH (M_PER_DAY / TIME_SLICES_PER_DAY) // length of a time slice in minutes
#define TIME_SLICES_PER_HOUR (M_PER_H / TIME_SLICE_LENGTH)

struct Time
{
    // typedefs
    typedef int ValueType;
    typedef ValueType HourType;
    typedef ValueType MinuteType;

    // Constructors

    Time();
    explicit Time(ValueType t);
    Time(HourType hour, MinuteType minute);
    explicit Time(const std::string& str);
    explicit Time(char const*const str);

    // Operators

    Time operator+(const Time& x)const;
    Time& operator+=(const Time& x);
    Time operator-(const Time& x)const;
    Time& operator-=(const Time& x);
    const bool operator==(const Time& x)const;
    const bool operator!=(const Time& x)const;
    const bool operator>(const Time& x)const;
    const bool operator<(const Time& x)const;
    const bool operator>=(const Time& x)const;
    const bool operator<=(const Time& x)const;
    Time& operator=(const Time& x);
    Time& operator++();
    Time& operator--();
    Time operator++(int);
    Time operator--(int);

    std::string toString()const;
    void parse(const char* str);
    void parse(const std::string& str);
    HourType getHour() const;
    MinuteType getMinute() const;
    Time& makeDaytime();


    ValueType time;
};

typedef Time DayTime;
typedef Time WeekTime;
typedef Time TimeInterval;
typedef Time TimeOffset;

#endif // TIMESTAMP_H_INCLUDED
