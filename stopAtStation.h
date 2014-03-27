#ifndef STOPATSTATION_H_INCLUDED
#define STOPATSTATION_H_INCLUDED

#include "lines.h"

struct StopAtStation
{
    typedef Line const * const LinePtrType;
    typedef Line::Stop const * const StopPtrType;
    StopAtStation(const LinePtrType& pLine, const StopPtrType& pStop)
        : line(pLine), stop(pStop)
    {

    }

    const bool operator>(const StopAtStation& x)const
    {
        if(line->getNumber() == x.line->getNumber())
            return *stop > *x.stop;
        else
            return line->getNumber() > x.line->getNumber();
    }

    const bool operator<(const StopAtStation& x)const
    {
        if(line->getNumber() == x.line->getNumber())
            return *stop < *x.stop;
        else
            return line->getNumber() < x.line->getNumber();
    }
    const LinePtrType line;
    const StopPtrType stop;
};

#endif // STOPATSTATION_H_INCLUDED
