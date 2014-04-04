#ifndef WXGRIDCELLSTOPRENDERER_H_INCLUDED
#define WXGRIDCELLSTOPRENDERER_H_INCLUDED

#include <wx/grid.h>
#include <wx/dc.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "wxGridStopTable.h"

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


        wxSize getNumberSize(wxDC& dc)
        {
            return dc.GetTextExtent(_number);
        }

        wxSize getIconSize(wxDC& dc)
        {
            return (_icon == -1 || _imageList == 0) ? wxSize() : _bitmap.GetSize();
        }

        wxSize getTimeSize(wxDC& dc)
        {
            return dc.GetTextExtent(_time);
        }

        wxSize getSize(wxDC& dc, const RenderItemFlags& flags=F_RIM_STANDARD)
        {
            wxSize result(_border * 2 + RI_SUBITEM_INTERSPACE, _border * 2);

            if(flags & F_RIM_NUMBER)
            {
                wxSize numberSize = getNumberSize(dc);
                result.x += numberSize.x + RI_SUBITEM_INTERSPACE;
                result.y = std::max(result.y, numberSize.y);
            }

            if(flags & F_RIM_ICON && _icon != -1 && _imageList != 0)
            {
                wxSize iconSize = getIconSize(dc);
                result.x += iconSize.x + RI_SUBITEM_INTERSPACE;
                result.y = std::max(result.y, iconSize.y);
            }

            if(flags & F_RIM_TIME)
            {
                wxSize timeSize = getTimeSize(dc);
                result.x += timeSize.x + RI_SUBITEM_INTERSPACE;
                result.y = std::max(result.y, timeSize.y);
            }
            return result;
        }

        void Draw(wxDC& dc, int x, const int& y, const RenderItemFlags& flags=F_RIM_STANDARD)
        {
            wxSize itemSize = getSize(dc, flags);

            dc.SetPen(*wxBLACK_PEN);

            dc.SetBackgroundMode(wxPENSTYLE_TRANSPARENT);
            dc.SetTextForeground(*wxBLACK);

            if(_marked)
                dc.SetBrush(*wxYELLOW_BRUSH);
            else
                dc.SetBrush(*wxWHITE_BRUSH);

            dc.DrawRectangle(wxPoint(x, y), itemSize);
            x+=_border + RI_SUBITEM_INTERSPACE;

            if(flags & F_RIM_NUMBER)
            {
                wxSize numberSize = getNumberSize(dc);

                dc.DrawText(_number, x, y + itemSize.GetHeight() / 2 - numberSize.GetHeight() / 2);
                x+=numberSize.GetWidth()+RI_SUBITEM_INTERSPACE;
            }

            if(flags & F_RIM_ICON)
            {
                wxSize iconSize = getIconSize(dc);
                if(_icon != -1 && _imageList != 0)
                {
                    dc.DrawBitmap(_bitmap, x, y + itemSize.GetHeight() / 2 - iconSize.GetHeight() / 2, true);
                    x+=iconSize.GetWidth()+RI_SUBITEM_INTERSPACE;
                }
            }

            if(flags & F_RIM_TIME)
            {
                wxSize timeSize = getTimeSize(dc);

                dc.DrawText(_time, x, y + itemSize.GetHeight() / 2 - timeSize.GetHeight() / 2);
                x+=timeSize.GetWidth()+RI_SUBITEM_INTERSPACE;
            }
        }


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

    wxGridCellStopRenderer(wxImageList* imageList = 0)
        : wxGridCellRenderer(), _imageList(imageList), _currentPlan(0), _currentStop(0)
    {

    }

    virtual wxGridCellRenderer * Clone () const
    {
        return new wxGridCellStopRenderer();
    }

    RenderItemList getRenderItems(InputItemList* input)
    {
        RenderItemList renderItems;
        for(InputItemList::iterator i = input->begin(); i != input->end(); ++i)
        {
            bool marked = false;
            if(_currentStop != 0)
            {
                if((*i).stop.plan == _currentPlan && (*i).stationStop == *_currentStop)
                {
                    marked = true;
                }
            }

            renderItems.push_back(RenderItem((*i), 1, marked, _imageList));
        }
        return renderItems;
    }

    virtual void Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected)
    {
        wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

        InputItemList* input = (InputItemList*)grid.GetTable()->GetValueAsCustom(row, col, STOP_ITEM_LIST);
        if(input == 0) return;

        RenderItemList renderItems = getRenderItems(input);

        int x = 0;
        for(RenderItemList::iterator i = renderItems.begin(); i != renderItems.end(); ++i)
        {
            (*i).Draw(dc, rect.x + x, rect.y + rect.height / 2 - (*i).getSize(dc).GetHeight() / 2);
            x+= (*i).getSize(dc).GetWidth() + 3;
        }
    }

    virtual wxSize 	GetBestSize (wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col)
    {
        InputItemList* input = (InputItemList*)grid.GetTable()->GetValueAsCustom(row, col, STOP_ITEM_LIST);
        if(input == 0) return wxSize(0,0);
        RenderItemList renderItems = getRenderItems(input);

        wxSize result;
        //int x = 0;
        for(RenderItemList::iterator i = renderItems.begin(); i != renderItems.end(); ++i)
        {
            wxSize itemSize = (*i).getSize(dc);

            //result.IncTo(itemSize);
            result.y = std::max(result.y, itemSize.y);
            result.x += itemSize.x + 3;
        }



        return result;

    }

    void setImageList(wxImageList* imageList)
    {
        _imageList = imageList;
    }

    void setCurrentPlan(const PlanNameType& plan)
    {
        _currentPlan = plan;
    }

    void setCurrentStop(StopAtStation* stop)
    {
        _currentStop = stop;
    }

private:

    wxImageList* _imageList;
    PlanNameType _currentPlan;
    StopAtStation* _currentStop;

};


#endif // WXGRIDCELLSTOPRENDERER_H_INCLUDED
