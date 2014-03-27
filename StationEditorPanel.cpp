#include "StationEditorPanel.h"

#include "wxGridCellStopRenderer.h"

//(*InternalHeaders(StationEditorPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(StationEditorPanel)
const long StationEditorPanel::ID_TIMETABLE_GRID = wxNewId();
const long StationEditorPanel::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(StationEditorPanel,wxPanel)
	//(*EventTable(StationEditorPanel)
	//*)
END_EVENT_TABLE()

StationEditorPanel::StationEditorPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(StationEditorPanel)
	wxBoxSizer* bsTimetable;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	panTimetable = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	bsTimetable = new wxBoxSizer(wxHORIZONTAL);
	gdTimetable = new wxGrid(panTimetable,ID_TIMETABLE_GRID,wxDefaultPosition,wxDefaultSize,0,_T("ID_TIMETABLE_GRID"));
	bsTimetable->Add(gdTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	panTimetable->SetSizer(bsTimetable);
	bsTimetable->Fit(panTimetable);
	bsTimetable->SetSizeHints(panTimetable);
	BoxSizer1->Add(panTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)

	_stopTable = new wxGridStopTable();
	gdTimetable->SetDefaultRenderer(new wxGridCellStopRenderer);
	gdTimetable->SetTable(_stopTable, true);


	//gdTimetable->AutoSize();



}

StationEditorPanel::~StationEditorPanel()
{
	//(*Destroy(StationEditorPanel)
	//*)
}

