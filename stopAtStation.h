#ifndef STOPATSTATION_H_INCLUDED
#define STOPATSTATION_H_INCLUDED

#include "lines.h"

struct StopAtStation
{
    typedef Line::ID LineIDType;
    typedef Line::Stop  StopType;
    StopAtStation(const LineIDType& lineID, const StopType& st)
        : line(lineID), stop(st)
    {

    }

    const bool operator>(const StopAtStation& x)const
    {
        const Line& thisLine = Lines::instance()->getLine(line);
        const Line& otherLine = Lines::instance()->getLine(x.line);

        if(thisLine.getNumber() == otherLine.getNumber())
            return stop > x.stop;
        else
            return thisLine.getNumber() > otherLine.getNumber();
    }

    const bool operator<(const StopAtStation& x)const
    {
        const Line& thisLine = Lines::instance()->getLine(line);
        const Line& otherLine = Lines::instance()->getLine(x.line);

        if(thisLine.getNumber() == otherLine.getNumber())
            return stop < x.stop;
        else
            return thisLine.getNumber() < otherLine.getNumber();
    }

    const bool operator==(const StopAtStation& x) const
    {
        return line == x.line && stop == x.stop;
    }

    const LineIDType line;
    const StopType stop;
};

#endif // STOPATSTATION_H_INCLUDED
