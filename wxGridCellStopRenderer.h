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
#define F_RIM_PLAN      0x4

typedef unsigned int RenderItemFlags;

class wxGridCellStopRenderer : public wxGridCellRenderer
{
public:
    typedef wxGridStopTable::ItemList InputItemList;
    typedef InputItemList::value_type InputItemType;

private:
    struct RenderItem
    {
    public:
        typedef Line::IconID IconID;

        RenderItem(const InputItemType& item, const int& border = 1, wxImageList* imageList = 0 )
            : _icon(Lines::instance()->getLine(item.line).getIcon()),
              _imageList(imageList),
              _bitmap(wxBitmap()),
              _border(border)
        {
            std::stringstream ss;

            ss << "#" << Lines::instance()->getLine(item.line).getNumber();
            _number = ss.str();
            ss.str(std::string());
            ss.clear();

            ss << item.stop.weekTime.getMinute();
            _time = ss.str();
            ss.str(std::string());
            ss.clear();

            if(_icon != -1 && _imageList != 0)
            {
                _bitmap = _imageList->GetBitmap(_icon);
            }
            else
                _number += " ";
        }

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

        wxSize getSize(wxDC& dc)
        {
            wxSize numberSize = getNumberSize(dc);
            wxSize iconSize = getIconSize(dc);
            wxSize timeSize = getTimeSize(dc);
            wxSize result;

            result.SetWidth( _border * 2 + numberSize.GetWidth() + iconSize.GetWidth() + timeSize.GetWidth());
            result.SetHeight(std::max(std::max(numberSize.GetHeight(), iconSize.GetHeight()), timeSize.GetHeight()) + _border * 2);

            return result;
        }

        void Draw(wxDC& dc, const int& x, const int& y)
        {
            wxSize itemSize = getSize(dc);

            wxSize numberSize = getNumberSize(dc);
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.SetPen(*wxBLACK_PEN);
            dc.DrawText(_number, x + _border, y + itemSize.GetHeight() / 2 - numberSize.GetHeight() / 2);

            wxSize iconSize = getIconSize(dc);
            if(_icon != -1 && _imageList != 0)
            {
                dc.DrawBitmap(_bitmap, x + _border + numberSize.GetWidth(), y + itemSize.GetHeight() / 2 - iconSize.GetHeight() / 2, true);
            }

            wxSize timeSize = getTimeSize(dc);

            dc.DrawText(_time, x + _border + numberSize.GetWidth() + iconSize.GetWidth(), y + itemSize.GetHeight() / 2 - timeSize.GetHeight() / 2);


            dc.DrawRectangle(wxPoint(x, y), itemSize);

        }


    private:
        std::string     _number;
        IconID          _icon;
        std::string     _time;
        wxImageList*    _imageList;
        wxBitmap        _bitmap;
        int             _border;


    };
    typedef std::vector<RenderItem> RenderItemList;

public:

    wxGridCellStopRenderer(wxImageList* imageList = 0)
        : wxGridCellRenderer(), _imageList(imageList)
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
            renderItems.push_back(RenderItem((*i), 1, _imageList));
        }
        return renderItems;
    }

    virtual void Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected)
    {
        wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

        InputItemList* input = (InputItemList*)grid.GetTable()->GetValueAsCustom(row, col, STOP_ITEM_LIST);
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
        RenderItemList renderItems = getRenderItems(input);

        wxSize result;
        //int x = 0;
        for(RenderItemList::iterator i = renderItems.begin(); i != renderItems.end(); ++i)
        {
            wxSize itemSize = (*i).getSize(dc);

            //result.IncTo(itemSize);
            result.y = std::max(result.y, itemSize.y);
            result.x += itemSize.x + 3;

            //(*i).Draw(dc, rect.x + x, rect.y + rect.height / 2 - (*i).getSize(dc).GetHeight() / 2);
            //x+= (*i).getSize(dc).GetWidth() + 3;
        }



        return result;

    }

    void setImageList(wxImageList* imageList)
    {
        _imageList = imageList;
    }

private:

    wxImageList* _imageList;

};


#endif // WXGRIDCELLSTOPRENDERER_H_INCLUDED
