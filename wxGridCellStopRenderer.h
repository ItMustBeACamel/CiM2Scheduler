#ifndef WXGRIDCELLSTOPRENDERER_H_INCLUDED
#define WXGRIDCELLSTOPRENDERER_H_INCLUDED

#include <wx/grid.h>
#include <wx/dc.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <string>
#include <vector>
#include <sstream>

#include "wxGridStopTable.h"

class wxGridCellStopRenderer : public wxGridCellRenderer
{

private:
    struct RenderItem
    {
        RenderItem()
        : number(0), numberWidth(0), icon(0), iconWidth(0), time(0), timeWidth(0), plan(0), planWidth(0)
        {

        }
        int getWidth()
        {
            return numberWidth + iconWidth + timeWidth + planWidth;
        }

        std::string number;
        int numberWidth;
        wxBitmap icon;
        int iconWidth;
        std::string time;
        int timeWidth;
        std::string plan;
        int planWidth;
    };
    typedef std::vector<RenderItem> RenderItemList;
    typedef std::vector<wxGridStopTable::Item> InputItemList;


public:

    wxGridCellStopRenderer(wxImageList* imageList = 0)
    : wxGridCellRenderer(), _imageList(imageList)
    {

    }

    virtual wxGridCellRenderer * 	Clone () const
    {
        return new wxGridCellStopRenderer();
    }

    virtual void Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected)
    {
        InputItemList* input = (InputItemList*)grid.GetTable()->GetValueAsCustom(row, col, STOP_ITEM_LIST);
        RenderItemList renderItems;

        for(InputItemList::iterator i = input->begin(); i != input->end(); ++i)
        {
            std::stringstream ss;
            RenderItem newItem;

            ss << Lines::instance()->getLine((*i).line).getNumber() << "|";
            newItem.number = ss.str();
            newItem.numberWidth = dc.GetTextExtent(newItem.number).GetWidth();
            ss.str().clear();

            ss << (*i).stop.weekTime.getMinute();
            newItem.time = ss.str();
            newItem.timeWidth = dc.GetTextExtent(newItem.time).GetWidth();
            ss.str().clear();

            if(Lines::instance()->getLine((*i).line).getIcon() != -1 && _imageList != 0)
            {
                newItem.icon = _imageList->GetBitmap(Lines::instance()->getLine((*i).line).getIcon());
                newItem.iconWidth = newItem.icon.GetWidth();
            }

            renderItems.push_back(newItem);
        }

        dc.DrawRectangle(rect);

        int cursor = 0;
        for(RenderItemList::iterator i = renderItems.begin(); i != renderItems.end(); ++i)
        {
            wxRect itemRect(rect.x, rect.y, (*i).getWidth(),rect.GetHeight());
            dc.DrawRectangle(itemRect);
            dc.DrawText((*i).number, rect.x, rect.y);

        }



    }

    virtual wxSize 	GetBestSize (wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col)
    {
        return wxSize(10,10);

    }

private:

    wxImageList* _imageList;

};


#endif // WXGRIDCELLSTOPRENDERER_H_INCLUDED
