#ifndef TIMESTAMP_H_INCLUDED
#define TIMESTAMP_H_INCLUDED


#include <string>
#include <sstream>

#define TIME_SLICE 5 // in minutes


struct TimeStamp
{
    typedef int TimeType;
    typedef TimeType HourType;
    typedef TimeType MinuteType;

    explicit TimeStamp()
        : time(0)
    {   }
    explicit TimeStamp(TimeType t)
        : time(t)
    {   }

    TimeStamp(HourType hour, MinuteType minute)
        : time(hour * 60 / TIME_SLICE + minute / TIME_SLICE)
    {   }

    // operators

    TimeStamp operator+(const TimeStamp& x)const
    {
        return TimeStamp(time+x.time);
    }
    TimeStamp& operator+=(const TimeStamp& x)
    {
        time+=x.time;
        return *this;
    }
    TimeStamp operator-(const TimeStamp& x)const
    {
        return TimeStamp(time-x.time);
    }

    TimeStamp& operator-=(const TimeStamp& x)
    {
        time-=x.time;
        return *this;
    }
    const bool operator==(const TimeStamp& x)const
    {
        return(time==x.time);
    }
    const bool operator!=(const TimeStamp& x)const
    {
        return(time!=x.time);
    }

    std::string toString()const
    {
        HourType hour = GetHour();
        HourType minute = GetMinute();
        std::stringstream ss;
        if(hour < 10) ss << 0;
        ss << hour << ":";
        if(minute < 10) ss << 0;
        ss << minute;
        return ss.str();
    }

    void parse(const char* str)
    {
        parse(std::string(str));
    }
    void parse(const std::string& str)
    {
        std::stringstream ss;
        TimeType h = 0;
        TimeType m = 0;
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

        if(m > 59) m = 59;

        time = h * 12 + m / 5;
        return;
    }

    HourType GetHour() const
    {
        return time / (60 / TIME_SLICE);
    }

    MinuteType GetMinute() const
    {
        return ((time %(60 / TIME_SLICE)) * TIME_SLICE);
    }

    TimeStamp& normalize()
    {
        TimeType day = (24 * 60) / TIME_SLICE;

        while(time > day)
            time -= day;
        return *this;
    }

    TimeType time;
};


#endif // TIMESTAMP_H_INCLUDED
