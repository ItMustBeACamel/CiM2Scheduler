#ifndef WXGRIDSTOPTABLE_H_INCLUDED
#define WXGRIDSTOPTABLE_H_INCLUDED


#include <wx/grid.h>


class wxGridStopTable : public wxGridTableBase
{
public:
    wxGridStopTable(const int& rows, const int& cols)
    : wxGridTableBase(), _rows(rows), _cols(cols)
    {

    }

    virtual int GetNumberRows()
    {
        return _rows;
    }

    virtual int GetNumberCols()
    {
        return _cols;
    }

    virtual void SetValue 	(int row, int  	col, const wxString &  	value )
    {

    }

    virtual wxString GetValue 	(int row, int  	col)
    {
        return wxString() + "blah";

    }


private:
    int _rows;
    int _cols;


};


#endif // WXGRIDSTOPTABLE_H_INCLUDED
