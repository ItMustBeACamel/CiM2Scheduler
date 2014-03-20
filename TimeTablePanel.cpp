#include "TimeTablePanel.h"

//(*InternalHeaders(TimeTablePanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(TimeTablePanel)
const long TimeTablePanel::ID_RADIOBOX1 = wxNewId();
const long TimeTablePanel::ID_PANEL1 = wxNewId();
const long TimeTablePanel::ID_STATICTEXT1 = wxNewId();
const long TimeTablePanel::ID_TEXTCTRL1 = wxNewId();
const long TimeTablePanel::ID_SPINBUTTON1 = wxNewId();
const long TimeTablePanel::ID_STATICTEXT2 = wxNewId();
const long TimeTablePanel::ID_TEXTCTRL2 = wxNewId();
const long TimeTablePanel::ID_SPINBUTTON2 = wxNewId();
const long TimeTablePanel::ID_STATICTEXT3 = wxNewId();
const long TimeTablePanel::ID_TEXTCTRL3 = wxNewId();
const long TimeTablePanel::ID_SPINBUTTON3 = wxNewId();
const long TimeTablePanel::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TimeTablePanel,wxPanel)
	//(*EventTable(TimeTablePanel)
	//*)
END_EVENT_TABLE()

TimeTablePanel::TimeTablePanel(Timetable& timetable, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    : _timetable(timetable), _currentPlan(PLAN_WEEKDAY), _offset(0)
{
	//(*Initialize(TimeTablePanel)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	wxString __wxRadioBoxChoices_1[6] =
	{
		_("Weekday"),
		_("Morning Rush"),
		_("Evening Rush"),
		_("Weekend"),
		_("Night"),
		_("Custom")
	};
	rbPlans = new wxRadioBox(Panel1, ID_RADIOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 6, __wxRadioBoxChoices_1, 1, wxRA_VERTICAL, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rbPlans->SetSelection(0);
	BoxSizer2->Add(rbPlans, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel1);
	BoxSizer2->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Start time:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtBegin = new wxTextCtrl(Panel2, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer3->Add(txtBegin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sbBegin = new wxSpinButton(Panel2, ID_SPINBUTTON1, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
	sbBegin->SetRange(0, 100);
	BoxSizer3->Add(sbBegin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("End time:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer3->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtEnd = new wxTextCtrl(Panel2, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer3->Add(txtEnd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sbEnd = new wxSpinButton(Panel2, ID_SPINBUTTON2, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON2"));
	sbEnd->SetRange(0, 100);
	BoxSizer3->Add(sbEnd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Interval:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtInterval = new wxTextCtrl(Panel2, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer3->Add(txtInterval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sbInterval = new wxSpinButton(Panel2, ID_SPINBUTTON3, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON3"));
	sbInterval->SetRange(0, 100);
	BoxSizer3->Add(sbInterval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel2);
	BoxSizer3->SetSizeHints(Panel2);
	BoxSizer1->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&TimeTablePanel::OnrbPlansSelect);
	//*)
	_currentPlan = (PlanName)rbPlans->GetSelection();

	refresh();
}

TimeTablePanel::~TimeTablePanel()
{
	//(*Destroy(TimeTablePanel)
	//*)
}

void TimeTablePanel::refresh()
{
    txtBegin->SetLabel(_timetable.getPlan(_currentPlan).getBegin().toString());
    txtEnd->SetLabel(_timetable.getPlan(_currentPlan).getEnd().toString());
    txtInterval->SetLabel(_timetable.getPlan(_currentPlan).getInterval().toString());
}

void TimeTablePanel::setOffset(const TimeStamp& off)
{
    _offset = off;
}

TimeStamp& TimeTablePanel::getOffset()
{
    return _offset;
}

const TimeStamp& TimeTablePanel::getOffset()const
{
    return _offset;

}

void TimeTablePanel::OnrbPlansSelect(wxCommandEvent& event)
{
    _currentPlan = (PlanName)rbPlans->GetSelection();
    refresh();
}
