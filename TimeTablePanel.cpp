#include "TimeTablePanel.h"
#include <list>
#include <sstream>



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
const long TimeTablePanel::ID_GRID1 = wxNewId();
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
    BoxSizer2->Add(rbPlans, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Start time:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtBegin = new wxTextCtrl(Panel2, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer3->Add(txtBegin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sbBegin = new wxSpinButton(Panel2, ID_SPINBUTTON1, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS|wxSP_WRAP, _T("ID_SPINBUTTON1"));
    sbBegin->SetRange(0, 100);
    BoxSizer3->Add(sbBegin, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("End time:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer3->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtEnd = new wxTextCtrl(Panel2, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer3->Add(txtEnd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sbEnd = new wxSpinButton(Panel2, ID_SPINBUTTON2, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS|wxSP_WRAP, _T("ID_SPINBUTTON2"));
    sbEnd->SetRange(0, 100);
    BoxSizer3->Add(sbEnd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Interval:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtInterval = new wxTextCtrl(Panel2, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer3->Add(txtInterval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sbInterval = new wxSpinButton(Panel2, ID_SPINBUTTON3, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL|wxSP_ARROW_KEYS|wxSP_WRAP, _T("ID_SPINBUTTON3"));
    sbInterval->SetRange(0, 100);
    BoxSizer3->Add(sbInterval, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(BoxSizer3);
    BoxSizer3->Fit(Panel2);
    BoxSizer3->SetSizeHints(Panel2);
    BoxSizer1->Add(Panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    gdTimetable = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
    gdTimetable->CreateGrid(25,4);
    gdTimetable->EnableEditing(false);
    gdTimetable->EnableGridLines(true);
    gdTimetable->SetRowLabelSize(20);
    gdTimetable->SetColLabelValue(0, _("Monday-Thursday"));
    gdTimetable->SetColLabelValue(1, _("Friday"));
    gdTimetable->SetColLabelValue(2, _("Saturday"));
    gdTimetable->SetColLabelValue(3, _("Sunday"));
    gdTimetable->SetRowLabelValue(0, _("x"));
    gdTimetable->SetRowLabelValue(1, _("0"));
    gdTimetable->SetRowLabelValue(2, _("1"));
    gdTimetable->SetRowLabelValue(3, _("2"));
    gdTimetable->SetRowLabelValue(4, _("3"));
    gdTimetable->SetRowLabelValue(5, _("4"));
    gdTimetable->SetRowLabelValue(6, _("5"));
    gdTimetable->SetRowLabelValue(7, _("6"));
    gdTimetable->SetRowLabelValue(8, _("7"));
    gdTimetable->SetRowLabelValue(9, _("8"));
    gdTimetable->SetRowLabelValue(10, _("9"));
    gdTimetable->SetRowLabelValue(11, _("10"));
    gdTimetable->SetRowLabelValue(12, _("11"));
    gdTimetable->SetRowLabelValue(13, _("12"));
    gdTimetable->SetRowLabelValue(14, _("13"));
    gdTimetable->SetRowLabelValue(15, _("14"));
    gdTimetable->SetRowLabelValue(16, _("15"));
    gdTimetable->SetRowLabelValue(17, _("16"));
    gdTimetable->SetRowLabelValue(18, _("17"));
    gdTimetable->SetRowLabelValue(19, _("18"));
    gdTimetable->SetRowLabelValue(20, _("19"));
    gdTimetable->SetRowLabelValue(21, _("20"));
    gdTimetable->SetRowLabelValue(22, _("21"));
    gdTimetable->SetRowLabelValue(23, _("22"));
    gdTimetable->SetRowLabelValue(24, _("23"));
    gdTimetable->SetDefaultCellFont( gdTimetable->GetFont() );
    gdTimetable->SetDefaultCellTextColour( gdTimetable->GetForegroundColour() );
    BoxSizer1->Add(gdTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&TimeTablePanel::OnrbPlansSelect);
    Connect(ID_SPINBUTTON1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&TimeTablePanel::OnsbBeginChange);
    Connect(ID_SPINBUTTON2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&TimeTablePanel::OnsbEndChange);
    Connect(ID_SPINBUTTON3,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&TimeTablePanel::OnsbIntervalChangeUp);
    Connect(ID_SPINBUTTON3,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&TimeTablePanel::OnsbIntervalChangeDown);
    Connect(ID_GRID1,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&TimeTablePanel::OngdTimetableCellLeftClick);
    gdTimetable->Connect(wxEVT_SIZE,(wxObjectEventFunction)&TimeTablePanel::OngdTimetableResize,0,this);
    //*)
    _currentPlan = (PlanLabel)rbPlans->GetSelection();
    gdTimetable->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    sbBegin->SetMax(TIME_RESOLUTION-1);
    sbEnd->SetMax(TIME_RESOLUTION-1);

    refresh();
}

TimeTablePanel::~TimeTablePanel()
{
    //(*Destroy(TimeTablePanel)
    //*)
}

void TimeTablePanel::refresh()
{
    DayTimeType startTime = _timetable.getPlan(_currentPlan).getStartTime();
    DayTimeType endTime = _timetable.getPlan(_currentPlan).getEndTime();
    IntervalType interval = _timetable.getPlan(_currentPlan).getInterval();
    //startTime.normalize();
    //end.normalize();

    txtBegin->SetLabel((startTime + _offset).toString());
    if(_offset != TimeOffsetType(0))
        txtBegin->SetBackgroundColour(*wxRED);
    else
        txtBegin->SetBackgroundColour(*wxWHITE);
    sbBegin->SetValue(startTime.time);

    txtEnd->SetLabel((endTime + _offset).toString());
    if(_offset != TimeOffsetType(0))
        txtEnd->SetBackgroundColour(*wxRED);
    else
        txtEnd->SetBackgroundColour(*wxWHITE);
    sbEnd->SetValue(endTime.time);

    txtInterval->SetLabel(interval.toString());



    gdTimetable->ClearGrid();

    for(int i = 0; i < gdTimetable->GetCols(); ++i)
    {
        if(_timetable.getPlan(_currentPlan).activeAtDays(1 << i))
            gdTimetable->SetCellValue(0, i, "x");
    }

    for(int col = 0; col < gdTimetable->GetCols(); ++col)
    {
        for(int row = 1; row < gdTimetable->GetRows(); ++row)
        {
            gdTimetable->SetCellBackgroundColour(row, col, *wxWHITE);
        }
    }



    TimetableView timetableView(_timetable);
    typedef TimetableView::StopList StopList;
    //typedef TimetableView::StopList::value_type StopType;
    timetableView.setOffset(TimeOffsetType(0));

/*
    for(DayName day = 0; day < DAY_NUM; ++day)
    {
        if(!_timetable.getPlan(_currentPlan).activeAtDay(day)) continue;
        for(int col = 0; col < gdTimetable->GetCols(); ++col)
        {
            for(int row = 1; row < gdTimetable->GetRows(); ++row)
            {
                WeekTimeType cellStartTime(dayBegin(col).time + (row-1) * TIME_SLICES_PER_HOUR);
                WeekTimeType cellEndTime = cellStartTime + TimeOffsetType(TIME_SLICES_PER_HOUR - 1);
                WeekTimeType planStart = timetableView.getPlanStart(_currentPlan, day);
                WeekTimeType planEnd = timetableView.getPlanEnd(_currentPlan, day);
                if(planEnd < planStart) planEnd = --weekEnd();
                if(cellStartTime <= planEnd && cellEndTime >= planStart)
                {
                    gdTimetable->SetCellBackgroundColour(row, col, *wxYELLOW);
                }
                else
                {
                    if(day == DAY_MON_TO_THU && _timetable.getPlan(_currentPlan).getEndTime() < _timetable.getPlan(_currentPlan).getStartTime())
                        if(cellStartTime <= _timetable.getPlan(_currentPlan).getEndTime() ||  cellEndTime <= _timetable.getPlan(_currentPlan).getEndTime())
                            gdTimetable->SetCellBackgroundColour(row, col, *wxYELLOW);

                }



            }
        }
    }
*/

    for(DayName day = 0; day < DAY_NUM; ++day)
    {
        if(!_timetable.getPlan(_currentPlan).activeAtDay(day)) continue;
        for(int col = 0; col < gdTimetable->GetCols(); ++col)
        {
            for(int row = 1; row < gdTimetable->GetRows(); ++row)
            {
                WeekTimeType cellStartTime(dayBegin(col).time + (row-1) * TIME_SLICES_PER_HOUR);
                WeekTimeType cellEndTime = cellStartTime + TimeOffsetType(TIME_SLICES_PER_HOUR - 1);

                if(timetableView.isWithinPlan(cellStartTime, _currentPlan, day) || timetableView.isWithinPlan(cellEndTime, _currentPlan, day))
                {
                    gdTimetable->SetCellBackgroundColour(row, col, *wxYELLOW);
                }

            }
        }
    }

    timetableView.setOffset(_offset);


    if(_offset != TimeOffsetType(0))
    {
        for(DayName day = 0; day < DAY_NUM; ++day)
        {
            if(!_timetable.getPlan(_currentPlan).activeAtDay(day)) continue;
            for(int col = 0; col < gdTimetable->GetCols(); ++col)
            {
                for(int row = 1; row < gdTimetable->GetRows(); ++row)
                {
                    WeekTimeType cellStartTime(dayBegin(col).time + (row-1) * TIME_SLICES_PER_HOUR);
                    WeekTimeType cellEndTime = cellStartTime + TimeOffsetType(TIME_SLICES_PER_HOUR - 1);

                    if(timetableView.isWithinPlan(cellStartTime, _currentPlan, day) || timetableView.isWithinPlan(cellEndTime, _currentPlan, day))
                    {
                        gdTimetable->SetCellBackgroundColour(row, col, *wxRED);
                    }

                }
            }
        }
    }

    StopList stopList = timetableView.getStopList();


    for(StopList::iterator i = stopList.begin(); i != stopList.end(); ++i)
    {

        int col = getDayFromWeekTime((*i).weekTime);

        DayTimeType dayTime((*i).weekTime.makeDaytime());

        int row = dayTime.getHour() + 1;

        std::stringstream ss;
        ss << gdTimetable->GetCellValue(row,col) << " " << dayTime.getMinute();
        gdTimetable->SetCellValue(row,col, ss.str());
    }

}

void TimeTablePanel::setOffset(const TimeTablePanel::TimeOffsetType& off)
{
    _offset = off;
}

TimeTablePanel::TimeOffsetType& TimeTablePanel::getOffset()
{
    return _offset;
}

const TimeTablePanel::TimeOffsetType& TimeTablePanel::getOffset()const
{
    return _offset;

}

void TimeTablePanel::OnrbPlansSelect(wxCommandEvent& event)
{
    _currentPlan = (PlanLabel)rbPlans->GetSelection();
    refresh();
}

void TimeTablePanel::OngdTimetableResize(wxSizeEvent& event)
{
    for(int i = 0; i < gdTimetable->GetCols(); ++i)

        gdTimetable->SetColumnWidth(i,(event.GetSize().GetWidth() - gdTimetable->GetColLabelSize()) / 4);
    gdTimetable->ForceRefresh();
}

void TimeTablePanel::OnsbBeginChange(wxSpinEvent& event)
{
    _timetable.getPlan(_currentPlan).setStartTime(DayTimeType(event.GetValue()));
    refresh();
}

void TimeTablePanel::OnsbEndChange(wxSpinEvent& event)
{
    _timetable.getPlan(_currentPlan).setEndTime(DayTimeType(event.GetValue()));
    refresh();
}

void TimeTablePanel::OngdTimetableCellLeftClick(wxGridEvent& event)
{
    if(event.GetRow() == 0)
    {
        _timetable.getPlan(_currentPlan).toggleDays( 1 << event.GetCol());
        refresh();
    }
    event.Allow();

}

void TimeTablePanel::OnsbIntervalChangeUp(wxSpinEvent& event)
{
    ++_timetable.getPlan(_currentPlan).getInterval();
    refresh();

}

void TimeTablePanel::OnsbIntervalChangeDown(wxSpinEvent& event)
{
    --_timetable.getPlan(_currentPlan).getInterval();
    refresh();
}
