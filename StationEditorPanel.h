#ifndef STATIONEDITORPANEL_H
#define STATIONEDITORPANEL_H

//(*Headers(StationEditorPanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/spinbutt.h>
//*)

#include "wxGridStopTable.h"
#include "wxGridCellStopRenderer.h"

class StationEditorPanel: public wxPanel
{
public:
    typedef wxGridStopTable::StationStopType StationStopType;
    typedef Timetable::PlanName Plan;

    StationEditorPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~StationEditorPanel();

    //(*Declarations(StationEditorPanel)
    wxRadioBox* rbPlan;
    wxGrid* gdTimetable;
    wxStaticText* StaticText2;
    wxPanel* Panel1;
    wxStaticText* StaticText1;
    wxStaticText* StaticText3;
    wxPanel* panTimetable;
    wxSpinButton* SpinButton1;
    wxSpinButton* SpinButton2;
    wxTextCtrl* TextCtrl2;
    wxTextCtrl* TextCtrl1;
    wxPanel* Panel2;
    wxSpinButton* SpinButton3;
    wxTextCtrl* TextCtrl3;
    //*)

    wxGridStopTable* _stopTable;
    wxGridCellStopRenderer* _renderer;

    void setImageList(wxImageList* imageList);

    StationStopType* addStop(const StationStopType& stop);

    void setCurrentStop(StationStopType* stop);

protected:

    //(*Identifiers(StationEditorPanel)
    static const long ID_RADIOBOX1;
    static const long ID_PANEL2;
    static const long ID_STATICTEXT1;
    static const long ID_TEXTCTRL1;
    static const long ID_SPINBUTTON1;
    static const long ID_STATICTEXT2;
    static const long ID_TEXTCTRL2;
    static const long ID_SPINBUTTON2;
    static const long ID_STATICTEXT3;
    static const long ID_TEXTCTRL3;
    static const long ID_SPINBUTTON3;
    static const long ID_PANEL3;
    static const long ID_TIMETABLE_GRID;
    static const long ID_PANEL1;
    //*)

private:

    Plan _currentPlan;
    StationStopType* _currentStop;

    //(*Handlers(StationEditorPanel)
    void OnrbPlanSelect(wxCommandEvent& event);
    void OnscStartChange(wxSpinEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
