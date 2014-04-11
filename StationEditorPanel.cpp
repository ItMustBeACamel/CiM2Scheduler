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
	wxBoxSizer* bsSelect;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	bsSelect = new wxBoxSizer(wxVERTICAL);
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
	bsSelect->Add(rbPlan, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	Panel1->SetSizer(bsSelect);
	bsSelect->Fit(Panel1);
	bsSelect->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	Panel2 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Start Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	txtStart = new wxTextCtrl(Panel2, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer3->Add(txtStart, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	sbStart = new wxSpinButton(Panel2, ID_SPINBUTTON1, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS|wxSP_WRAP, _T("ID_SPINBUTTON1"));
	sbStart->SetRange(0, 100);
	BoxSizer3->Add(sbStart, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer3->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("End Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer3->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	txtEnd = new wxTextCtrl(Panel2, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer3->Add(txtEnd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	sbEnd = new wxSpinButton(Panel2, ID_SPINBUTTON2, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS|wxSP_WRAP, _T("ID_SPINBUTTON2"));
	sbEnd->SetRange(0, 100);
	BoxSizer3->Add(sbEnd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer3->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	txtInterval = new wxTextCtrl(Panel2, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer3->Add(txtInterval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	sbInterval = new wxSpinButton(Panel2, ID_SPINBUTTON3, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS|wxSP_WRAP, _T("ID_SPINBUTTON3"));
	sbInterval->SetRange(0, 100);
	BoxSizer3->Add(sbInterval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel2->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel2);
	BoxSizer3->SetSizeHints(Panel2);
	BoxSizer1->Add(Panel2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	panTimetable = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	bsTimetable = new wxBoxSizer(wxHORIZONTAL);
	gdTimetable = new wxGrid(panTimetable,ID_TIMETABLE_GRID,wxDefaultPosition,wxDefaultSize,wxWANTS_CHARS,_T("ID_TIMETABLE_GRID"));
	bsTimetable->Add(gdTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	panTimetable->SetSizer(bsTimetable);
	bsTimetable->Fit(panTimetable);
	bsTimetable->SetSizeHints(panTimetable);
	BoxSizer1->Add(panTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&StationEditorPanel::OnrbPlanSelect);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&StationEditorPanel::OntxtStartTextEnter);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&StationEditorPanel::OnsbStartChange);
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&StationEditorPanel::OntxtEndTextEnter);
	Connect(ID_SPINBUTTON2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&StationEditorPanel::OnsbEndChange);
	Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&StationEditorPanel::OntxtIntervalTextEnter);
	Connect(ID_SPINBUTTON3,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&StationEditorPanel::OnsbIntervalChangeUp);
	Connect(ID_SPINBUTTON3,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&StationEditorPanel::OnsbIntervalChangeDown);
	//*)

	Connect(ID_TIMETABLE_GRID, wxEVT_GRID_CELL_CHANGED,(wxObjectEventFunction)&StationEditorPanel::OngdTimetableChanged);

	_stopTable = new wxGridStopTable();
	_renderer = new wxGridCellStopRenderer;
	gdTimetable->SetDefaultRenderer(_renderer);
	gdTimetable->SetTable(_stopTable, true);

    //wxGridCellBoolRenderer* boolRenderer = new wxGridCellBoolRenderer;
	gdTimetable->SetCellRenderer(0,0, new wxGridCellBoolRenderer);
	gdTimetable->SetCellRenderer(0,1, new wxGridCellBoolRenderer);
	gdTimetable->SetCellRenderer(0,2, new wxGridCellBoolRenderer);
	gdTimetable->SetCellRenderer(0,3, new wxGridCellBoolRenderer);
	gdTimetable->SetCellRenderer(0,4, new wxGridCellBoolRenderer);
	gdTimetable->SetCellRenderer(0,5, new wxGridCellBoolRenderer);
	gdTimetable->SetCellRenderer(0,6, new wxGridCellBoolRenderer);

	gdTimetable->SetCellEditor(0,0, new wxGridCellBoolEditor);
	gdTimetable->SetCellEditor(0,1, new wxGridCellBoolEditor);
	gdTimetable->SetCellEditor(0,2, new wxGridCellBoolEditor);
	gdTimetable->SetCellEditor(0,3, new wxGridCellBoolEditor);
	gdTimetable->SetCellEditor(0,4, new wxGridCellBoolEditor);
	gdTimetable->SetCellEditor(0,5, new wxGridCellBoolEditor);
	gdTimetable->SetCellEditor(0,6, new wxGridCellBoolEditor);

	gdTimetable->SetRowLabelSize(30);

	//gdTimetable->AutoSize();
    sbStart->SetRange(0, TIME_SLICES_PER_DAY-1);
    sbEnd->SetRange(0, TIME_SLICES_PER_DAY-1);

    refresh();


}

StationEditorPanel::~StationEditorPanel()
{
	//(*Destroy(StationEditorPanel)
	//*)
}


void StationEditorPanel::refresh()
{
    if(_currentStop == 0)
    {
        rbPlan->Disable();
        sbStart->Disable();
        sbEnd->Disable();
        sbInterval->Disable();
        txtStart->Disable();
        txtEnd->Disable();
        txtInterval->Disable();
    }
    else
    {
        rbPlan->Enable();
        sbStart->Enable();
        sbEnd->Enable();
        sbInterval->Enable();
        txtStart->Enable();
        txtEnd->Enable();
        txtInterval->Enable();

        Line& line = Lines::instance()->getLine(_currentStop->line);
        TimeOffset offset = _currentStop->stop.time;
        sbStart->SetValue((line.getTimetable().getPlan(_currentPlan).getStartTime() + offset).makeDaytime().time);
        sbEnd->SetValue((line.getTimetable().getPlan(_currentPlan).getEndTime() + offset).makeDaytime().time);

        txtStart->SetValue(Time(sbStart->GetValue()).toString());
        txtEnd->SetValue(Time(sbEnd->GetValue()).toString());
        txtInterval->SetValue((line.getTimetable().getPlan(_currentPlan).getInterval()).toString());
    }
    //gdTimetable->ForceRefresh();
    gdTimetable->AutoSize();
    bsTimetable->Layout();

}

StationEditorPanel::StationStopType* StationEditorPanel::addStop(const StationEditorPanel::StationStopType& stop)
{
    return _stopTable->addStop(stop);
}

void StationEditorPanel::setCurrentStop(StationEditorPanel::StationStopType* stop)
{
    _currentStop = stop;
    _renderer->setCurrentStop(_currentStop);
    _stopTable->setCurrentStop(_currentStop);
}

void StationEditorPanel::setImageList(wxImageList* imageList)
{
    _renderer->setImageList(imageList);

}

void StationEditorPanel::OnrbPlanSelect(wxCommandEvent& event)
{
    _currentPlan = event.GetInt();
    _renderer->setCurrentPlan(_currentPlan);
    _stopTable->setCurrentPlan(_currentPlan);
    refresh();
    gdTimetable->ForceRefresh();
}

void StationEditorPanel::OnsbStartChange(wxSpinEvent& event)
{
    txtStart->SetValue(Time(event.GetValue()).toString());

    Line& line = Lines::instance()->getLine(_currentStop->line);
    TimeOffset offset = _currentStop->stop.time;

    line.getTimetable().getPlan(_currentPlan).setStartTime((Time(event.GetValue()) - offset).makeDaytime());
    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
    //gdTimetable->ForceRefresh();
}

void StationEditorPanel::OnsbEndChange(wxSpinEvent& event)
{
    txtEnd->SetValue(Time(event.GetValue()).toString());

    Line& line = Lines::instance()->getLine(_currentStop->line);
    TimeOffset offset = _currentStop->stop.time;

    line.getTimetable().getPlan(_currentPlan).setEndTime((Time(event.GetValue()) - offset).makeDaytime());
    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
    //gdTimetable->ForceRefresh();
}

void StationEditorPanel::OnsbIntervalChangeUp(wxSpinEvent& event)
{
    Line& line = Lines::instance()->getLine(_currentStop->line);

    TimeInterval interval(txtInterval->GetValue());
    interval++;
    txtInterval->SetValue(interval.toString());

    line.getTimetable().getPlan(_currentPlan).setInterval(interval);

    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
}

void StationEditorPanel::OnsbIntervalChangeDown(wxSpinEvent& event)
{
    Line& line = Lines::instance()->getLine(_currentStop->line);

    TimeInterval interval(txtInterval->GetValue());
    interval--;
    if(interval.time < 0) interval = TimeInterval(0);
    txtInterval->SetValue(interval.toString());

    line.getTimetable().getPlan(_currentPlan).setInterval(interval);

    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
}

void StationEditorPanel::OngdTimetableChanged(wxGridEvent& event)
{
    //gdTimetable->AutoSize();
    refresh();

}

void StationEditorPanel::OntxtStartTextEnter(wxCommandEvent& event)
{
    Line& line = Lines::instance()->getLine(_currentStop->line);
    Time offset = _currentStop->stop.time;

    Time newTime;
    newTime.parse(event.GetString());

    line.getTimetable().getPlan(_currentPlan).setStartTime((newTime - offset).makeDaytime());
    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
}

void StationEditorPanel::OntxtEndTextEnter(wxCommandEvent& event)
{
    Line& line = Lines::instance()->getLine(_currentStop->line);
    Time offset = _currentStop->stop.time;

    Time newTime;
    newTime.parse(event.GetString());

    line.getTimetable().getPlan(_currentPlan).setEndTime((newTime - offset).makeDaytime());
    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
}

void StationEditorPanel::OntxtIntervalTextEnter(wxCommandEvent& event)
{
    Line& line = Lines::instance()->getLine(_currentStop->line);

    Time newTime;
    newTime.parse(event.GetString());

    line.getTimetable().getPlan(_currentPlan).setInterval(newTime);
    _stopTable->refresh();
    refresh();
    //gdTimetable->AutoSize();
}
