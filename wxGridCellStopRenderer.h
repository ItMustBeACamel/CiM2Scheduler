#ifndef WXGRIDCELLSTOPRENDERER_H_INCLUDED
#define WXGRIDCELLSTOPRENDERER_H_INCLUDED

// WX DEPENDENCIES
#include <wx/grid.h>
#include <wx/dc.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>

// STL DEPENDENCIES
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// PROJECT DEPENDENCIES

#include "wxGridStopTable.h"

// CONSTANTS DEFINITIONS

#define F_RIM_NUMBER    0x1
#define F_RIM_ICON      0x2
#define F_RIM_TIME      0x4
#define F_RIM_PLAN      0x8

#define F_RIM_STANDARD (F_RIM_NUMBER | F_RIM_ICON | F_RIM_TIME)

#define RI_SUBITEM_INTERSPACE 1

typedef unsigned int RenderItemFlags;

class wxGridCellStopRenderer : public wxGridCellRenderer
{
public:
    typedef wxGridStopTable::ItemList InputItemList;
    typedef InputItemList::value_type InputItemType;
    typedef InputItemType::StopType::PlanNameType PlanNameType;

private:
    struct RenderItem
    {
    public:
        typedef Line::IconID IconID;

        // Constructor

        RenderItem(const InputItemType& item,
                   const int& border = 1,
                   const bool& marked = false,
                   wxImageList* imageList = 0 );

        // public members

        wxSize getNumberSize(wxDC& dc);
        wxSize getIconSize(wxDC& dc);
        wxSize getTimeSize(wxDC& dc);
        wxSize getSize(wxDC& dc, const RenderItemFlags& flags=F_RIM_STANDARD);
        void Draw(wxDC& dc, int x, const int& y, const RenderItemFlags& flags=F_RIM_STANDARD);

        // private members
    private:
        std::string     _number;
        IconID          _icon;
        std::string     _time;
        wxImageList*    _imageList;
        wxBitmap        _bitmap;
        int             _border;
        bool            _marked;


    };
    typedef std::vector<RenderItem> RenderItemList;

public:

    // Constructors
    wxGridCellStopRenderer(wxImageList* imageList = 0);

    // public members
    virtual wxGridCellRenderer * Clone () const;

    virtual void Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected);

    virtual wxSize 	GetBestSize (wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col);

    void setImageList(wxImageList* imageList);
    void setCurrentPlan(const PlanNameType& plan);
    void setCurrentStop(StopAtStation* stop);

private:

    RenderItemList getRenderItems(InputItemList* input);

    wxImageList* _imageList;
    PlanNameType _currentPlan;
    StopAtStation* _currentStop;

};


#endif // WXGRIDCELLSTOPRENDERER_H_INCLUDED
