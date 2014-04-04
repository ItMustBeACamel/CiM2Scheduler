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
 * \param imageList pointer to an wxImageList which contains the icons
 *
 */
wxGridCellStopRenderer::RenderItem::RenderItem(const wxGridCellStopRenderer::InputItemType& item,
                                               const int& border, const bool& marked,
                                               wxImageList* imageList)
    : _icon(Lines::instance()->getLine(item.getLine()).getIcon()),
      _imageList(imageList), _bitmap(wxBitmap()),
      _border(border), _marked(marked)
{
    std::stringstream ss;

    ss << "#" << Lines::instance()->getLine(item.getLine()).getNumber();
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
