#include "wxGridCellStopRenderer.h"

//###################################################################################################
// wxGridCellStopRenderer::RenderItem
//###################################################################################################


// Constructors

//*****************************************************************************************************
/** \brief constructor
 *
 * \param item item to be rendered
 * \param border border
 * \param marked whether the item shall be drawn with a yellow background
 * \param imageList pointer to an wxImageList which contains the icons or null if there is none
 *
 */
wxGridCellStopRenderer::RenderItem::RenderItem(const wxGridCellStopRenderer::InputItemType& item,
                                               const int& border,
                                               //const bool& marked,
                                               const wxColor& backgColor,
                                               const wxColor& bordColor,
                                               wxImageList* imageList)
    : _icon(Lines::instance()->getLine(item.getLine()).getIcon()),
      _imageList(imageList), _bitmap(wxBitmap()),
      _border(border), _backgroundColor(backgColor), _borderColor(bordColor)//, _marked(marked)
{
    std::stringstream ss;
    try
    {
        ss << "#" << Lines::instance()->getLine(item.getLine()).getNumber();
        _number = ss.str();
    }
    catch(std::invalid_argument& e)
    {
        _number = "err#";
    }

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

//*****************************************************************************************************
/** \brief returns the size of the number part of a rendered item
 *
 * \param dc the device context you intend to render to
 * \return the size
 *
 */
wxSize wxGridCellStopRenderer::RenderItem::getNumberSize(wxDC& dc)
{
    return dc.GetTextExtent(_number);
}

//*****************************************************************************************************
/** \brief returns the size of the icon part of a rendered item
 *
 * \param dc the device context you intend to render to
 * \return the size
 *
 */
wxSize wxGridCellStopRenderer::RenderItem::getIconSize(wxDC& dc)
{
    return (_icon == -1 || _imageList == 0) ? wxSize() : _bitmap.GetSize();
}

//*****************************************************************************************************
/** \brief returns the size of the time part of a rendered item
 *
 * \param dc the device context you intend to render to
 * \return the size
 *
 */
wxSize wxGridCellStopRenderer::RenderItem::getTimeSize(wxDC& dc)
{
    return dc.GetTextExtent(_time);
}

//*****************************************************************************************************
/** \brief returns the size of a rendered item
 *
 * \param dc the device context you intend to render to
 * \param flags the subitems you want to draw (number, icon, time etc.)
 * \return the size
 *
 */
wxSize wxGridCellStopRenderer::RenderItem::getSize(wxDC& dc, const RenderItemFlags& flags)
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

//*****************************************************************************************************
/** \brief Draws a render-item to a device context
 *
 * \param dc the device context you intend to render to
 * \param x,y where to draw
 * \param flags the subitems you want to draw (number, icon, time etc.)
 * \return void
 *
 */
void wxGridCellStopRenderer::RenderItem::Draw(wxDC& dc, int x, const int& y, const RenderItemFlags& flags)
{
    wxSize itemSize = getSize(dc, flags);

    wxPen borderPen(_borderColor);
    wxBrush rectBrush(_backgroundColor);

    dc.SetBackgroundMode(wxPENSTYLE_TRANSPARENT);
    dc.SetTextForeground(*wxBLACK);

    /*
    if(_marked)
        dc.SetBrush(*wxYELLOW_BRUSH);
    else
        dc.SetBrush(*wxWHITE_BRUSH);
    */

    dc.SetPen(borderPen);
    dc.SetBrush(rectBrush);
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


//###################################################################################################
// wxGridCellStopRenderer
//###################################################################################################

// Constructor

//*****************************************************************************************************
/** \brief Constructor
 *
 * \param imageList the image list containing the icons or null if none available
 *
 */
wxGridCellStopRenderer::wxGridCellStopRenderer(wxImageList* imageList)
        : wxGridCellRenderer(), _imageList(imageList), _currentPlan(0), _currentStop(0)
{

}

// public members

//*****************************************************************************************************
/** \brief clones the renderer
 *
 * \return pointer to the clone
 * \bug this does not actually work yet :D
 *
 */
wxGridCellRenderer * wxGridCellStopRenderer::Clone () const
{
    return new wxGridCellStopRenderer(_imageList);
}

//*****************************************************************************************************
/** \brief draws a cell
 *
 * \param grid reference to the grid
 * \param attr cell attributes
 * \param dc device context to draw to
 * \param rect rectangle indicating the cell boundaries
 * \param row the row of the cell
 * \param col the column of the cell
 * \param isSelected true if the cell is selected by the user
 * \return void
 * \detail this gets automatically called by the grid class.
 *
 */
void wxGridCellStopRenderer::Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected)
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

//*****************************************************************************************************
/** \brief returns the ideal size of a cell
 *
 * \param grid reference to the grid
 * \param attr cell attributes
 * \param dc device context to draw to
 * \param rect rectangle indicating the cell boundaries
 * \param row the row of the cell
 * \param col the column of the cell
 * \return the size
 * \detail this gets automatically called by the grid class.
 *
 */
wxSize 	wxGridCellStopRenderer::GetBestSize (wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col)
{
    InputItemList* input = (InputItemList*)grid.GetTable()->GetValueAsCustom(row, col, STOP_ITEM_LIST);
    if(input == 0) return wxSize(0,0);
    RenderItemList renderItems = getRenderItems(input);

    wxSize result;
    //int x = 0;
    for(RenderItemList::iterator i = renderItems.begin(); i != renderItems.end(); ++i)
    {
        wxSize itemSize = (*i).getSize(dc);

        result.y = std::max(result.y, itemSize.y);
        result.x += itemSize.x + 3;
    }
    return result;

}

//*****************************************************************************************************
/** \brief sets the image list to be used by the renderer to draw icons
 *
 * \param imageList pointer to an image list or null to use none
 * \return void
 *
 */
void wxGridCellStopRenderer::setImageList(wxImageList* imageList)
{
    _imageList = imageList;
}

//*****************************************************************************************************
/** \brief sets the currently marked plan
 *
 * \param plan plan that should be marked
 * \return void
 *
 */
void wxGridCellStopRenderer::setCurrentPlan(const PlanNameType& plan)
{
    _currentPlan = plan;
}

//*****************************************************************************************************
/** \brief sets the currently marked stop
 *
 * \param stop stop that should be marked
 * \return void
 *
 */
void wxGridCellStopRenderer::setCurrentStop(StopAtStation* stop)
{
    _currentStop = stop;
}

// private members

//*****************************************************************************************************
/** \brief retrieves input items and makes render items out of them
 *
 * \param input list of input items usually from the same cell
 * \return a list of render items
 *
 */
wxGridCellStopRenderer::RenderItemList wxGridCellStopRenderer::getRenderItems(InputItemList* input)
{
    RenderItemList renderItems;
    for(InputItemList::iterator i = input->begin(); i != input->end(); ++i)
    {
        if(!(*i).stationStop.hidden)
        {
            wxColor backgroundColor = *wxWHITE;
            wxColor borderColor = *wxBLACK;

            //bool marked = false;
            if(_currentStop != 0)
            {
                if((*i).stationStop == *_currentStop)
                    borderColor = *wxRED;

                if((*i).stop.plan == _currentPlan)
                {
                    if((*i).stationStop == *_currentStop)
                        backgroundColor = *wxYELLOW;
                    else
                        backgroundColor = *wxLIGHT_GREY;
                    //marked = true;
                }
            }
            renderItems.push_back(RenderItem((*i), 1, backgroundColor, borderColor, _imageList));
        }
    }
    return renderItems;
}
