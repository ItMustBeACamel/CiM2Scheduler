#include "StationEditorPanel.h"



//(*InternalHeaders(StationEditorPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(StationEditorPanel)
const long StationEditorPanel::ID_RADIOBOX1 = wxNewId();
const long StationEditorPanel::ID_PANEL2 = wxNewId();
const long StationEditorPanel::ID_STATICTEXT1 = wxNewId();
const long StationEditorPanel::ID_TEXTCTRL1 = wxNewId();
const long StationEditorPanel::ID_SPINBUTTON1 = wxNewId();
const long StationEditorPanel::ID_STATICTEXT2 = wxNewId();
const long StationEditorPanel::ID_TEXTCTRL2 = wxNewId();
const long StationEditorPanel::ID_SPINBUTTON2 = wxNewId();
const long StationEditorPanel::ID_STATICTEXT3 = wxNewId();
const long StationEditorPanel::ID_TEXTCTRL3 = wxNewId();
const long StationEditorPanel::ID_SPINBUTTON3 = wxNewId();
const long StationEditorPanel::ID_PANEL3 = wxNewId();
const long StationEditorPanel::ID_TIMETABLE_GRID = wxNewId();
const long StationEditorPanel::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(StationEditorPanel,wxPanel)
	//(*EventTable(StationEditorPanel)
	//*)
END_EVENT_TABLE()

StationEditorPanel::StationEditorPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    : _currentPlan(0), _currentStop(0)
{
	//(*Initialize(StationEditorPanel)
	wxBoxSizer* bsTimetable;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	wxString __wxRadioBoxChoices_1[6] =
	{
		_("Weekday"),
		_("Morning Rush"),
		_("Evening Rush"),
		_("Weekend"),
		_("Night"),
		_("Custom")
	};
	rbPlan = new wxRadioBox(Panel1, ID_RADIOBOX1, _("Plan"), wxDefaultPosition, wxDefaultSize, 6, __wxRadioBoxChoices_1, 1, wxRA_VERTICAL, wxDefaultValidator, _T("ID_RADIOBOX1"));
	BoxSizer2->Add(rbPlan, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel1);
	BoxSizer2->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Start Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	TextCtrl1 = new wxTextCtrl(Panel2, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer3->Add(TextCtrl1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SpinButton1 = new wxSpinButton(Panel2, ID_SPINBUTTON1, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
	SpinButton1->SetRange(0, 100);
	BoxSizer3->Add(SpinButton1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer3->Add(0,0,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("End Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer3->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	TextCtrl2 = new wxTextCtrl(Panel2, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer3->Add(TextCtrl2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SpinButton2 = new wxSpinButton(Panel2, ID_SPINBUTTON2, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON2"));
	SpinButton2->SetRange(0, 100);
	BoxSizer3->Add(SpinButton2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer3->Add(0,0,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	TextCtrl3 = new wxTextCtrl(Panel2, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer3->Add(TextCtrl3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SpinButton3 = new wxSpinButton(Panel2, ID_SPINBUTTON3, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON3"));
	SpinButton3->SetRange(0, 100);
	BoxSizer3->Add(SpinButton3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel2->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel2);
	BoxSizer3->SetSizeHints(Panel2);
	BoxSizer1->Add(Panel2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	panTimetable = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	bsTimetable = new wxBoxSizer(wxHORIZONTAL);
	gdTimetable = new wxGrid(panTimetable,ID_TIMETABLE_GRID,wxDefaultPosition,wxDefaultSize,wxWANTS_CHARS,_T("ID_TIMETABLE_GRID"));
	bsTimetable->Add(gdTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	panTimetable->SetSizer(bsTimetable);
	bsTimetable->Fit(panTimetable);
	bsTimetable->SetSizeHints(panTimetable);
	BoxSizer1->Add(panTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&StationEditorPanel::OnrbPlanSelect);
	//*)

	_stopTable = new wxGridStopTable();
	_renderer = new wxGridCellStopRenderer;
	gdTimetable->SetDefaultRenderer(_renderer);
	gdTimetable->SetTable(_stopTable, true);

	//gdTimetable->AutoSize();



}

StationEditorPanel::~StationEditorPanel()
{
	//(*Destroy(StationEditorPanel)
	//*)
}

StationEditorPanel::StationStopType* StationEditorPanel::addStop(const StationEditorPanel::StationStopType& stop)
{
    return _stopTable->addStop(stop);
}

void StationEditorPanel::setCurrentStop(StationEditorPanel::StationStopType* stop)
{
    _currentStop = stop;
    _renderer->setCurrentStop(_currentStop);
}

void StationEditorPanel::setImageList(wxImageList* imageList)
{
    _renderer->setImageList(imageList);

}

void StationEditorPanel::OnrbPlanSelect(wxCommandEvent& event)
{
    _currentPlan = event.GetInt();
    _renderer->setCurrentPlan(_currentPlan);
    gdTimetable->ForceRefresh();
}
