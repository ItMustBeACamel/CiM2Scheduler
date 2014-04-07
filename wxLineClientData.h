#ifndef WXLINECLIENTDATA_H_INCLUDED
#define WXLINECLIENTDATA_H_INCLUDED


// PROJECT DEPENDENCIES
#include "lines.h"

// WX DEPENDENCIES
#include <wx/clntdata.h>

class wxLineClientData : public wxClientData
{
    public:
    // constructor
    wxLineClientData(const Line::ID& lineID = 0)
        : wxClientData(), _line(lineID)
    {

    }

    const Line::ID& GetData() const
    {
        return _line;
    }

    Line::ID& GetData()
    {
        return _line;
    }

    void SetData(const Line::ID& lineID)
    {
        _line = lineID;
    }

private:
    Line::ID _line;



};




#endif // WXLINECLIENTDATA_H_INCLUDED
