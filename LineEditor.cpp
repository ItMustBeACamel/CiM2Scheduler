#include "LineEditor.h"
#include <sstream>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>

//(*InternalHeaders(LineEditor)
#include <wx/intl.h>
#include <wx/string.h>
//*)



int wxCALLBACK StopCompareFuncASC(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    if(TimeOffset(((wxListItem*)item1)->GetText().c_str()) < TimeOffset(((wxListItem*) item2)->GetText().c_str()))
        return 1;

    if(TimeOffset(((wxListItem*) item1)->GetText().c_str()) < TimeOffset(((wxListItem*) item2)->GetText().c_str()))
        return -1;
    return 0;
}

//(*IdInit(LineEditor)
const long LineEditor::ID_STATICTEXT1 = wxNewId();
const long LineEditor::ID_TEXTCTRL1 = wxNewId();
const long LineEditor::ID_STATICTEXT2 = wxNewId();
const long LineEditor::ID_TEXTCTRL2 = wxNewId();
const long LineEditor::ID_PANEL5 = wxNewId();
const long LineEditor::ID_PANEL2 = wxNewId();
const long LineEditor::ID_CUSTOM1 = wxNewId();
const long LineEditor::ID_LISTVIEW1 = wxNewId();
const long LineEditor::ID_BUTTON7 = wxNewId();
const long LineEditor::ID_BUTTON6 = wxNewId();
const long LineEditor::ID_PANEL10 = wxNewId();
const long LineEditor::ID_PANEL8 = wxNewId();
const long LineEditor::ID_LISTVIEW2 = wxNewId();
const long LineEditor::ID_BUTTON5 = wxNewId();
const long LineEditor::ID_BUTTON3 = wxNewId();
const long LineEditor::ID_BUTTON4 = wxNewId();
const long LineEditor::ID_PANEL11 = wxNewId();
const long LineEditor::ID_PANEL9 = wxNewId();
const long LineEditor::ID_PANEL7 = wxNewId();
const long LineEditor::ID_PANEL3 = wxNewId();
const long LineEditor::ID_BUTTON1 = wxNewId();
const long LineEditor::ID_BUTTON2 = wxNewId();
const long LineEditor::ID_PANEL4 = wxNewId();
const long LineEditor::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LineEditor,wxDialog)
	//(*EventTable(LineEditor)
	//*)
END_EVENT_TABLE()

LineEditor::LineEditor(Line& line, wxWindow* parent, wxImageList* imageList, wxWindowID id)
    :_line(line), _imageList(imageList)
{
	//(*Initialize(LineEditor)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer9;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	Panel5 = new wxPanel(Panel2, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel5, ID_STATICTEXT1, _("#"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer5->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtNumber = new wxTextCtrl(Panel5, ID_TEXTCTRL1, _("1000"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer5->Add(txtNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(Panel5, ID_STATICTEXT2, _("Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
	BoxSizer5->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtName = new wxTextCtrl(Panel5, ID_TEXTCTRL2, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer5->Add(txtName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel5->SetSizer(BoxSizer5);
	BoxSizer5->Fit(Panel5);
	BoxSizer5->SetSizeHints(Panel5);
	BoxSizer4->Add(Panel5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(BoxSizer4);
	BoxSizer4->Fit(Panel2);
	BoxSizer4->SetSizeHints(Panel2);
	BoxSizer2->Add(Panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	panMiddle = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	panTimetable = new TimeTablePanel(_line.getTimetable(),panMiddle,ID_CUSTOM1,wxDefaultPosition,wxDefaultSize);
	BoxSizer6->Add(panTimetable, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7 = new wxPanel(panMiddle, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	Panel8 = new wxPanel(Panel7, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel8, _("Stops"));
	lvStops = new wxListView(Panel8, ID_LISTVIEW1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW1"));
	StaticBoxSizer2->Add(lvStops, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel10 = new wxPanel(Panel8, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	btEditStop = new wxButton(Panel10, ID_BUTTON7, _("edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	BoxSizer8->Add(btEditStop, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btRemoveStop = new wxButton(Panel10, ID_BUTTON6, _("-->"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	BoxSizer8->Add(btRemoveStop, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel10->SetSizer(BoxSizer8);
	BoxSizer8->Fit(Panel10);
	BoxSizer8->SetSizeHints(Panel10);
	StaticBoxSizer2->Add(Panel10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel8->SetSizer(StaticBoxSizer2);
	StaticBoxSizer2->Fit(Panel8);
	StaticBoxSizer2->SetSizeHints(Panel8);
	BoxSizer7->Add(Panel8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel9 = new wxPanel(Panel7, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel9, _("Stations"));
	lvStations = new wxListView(Panel9, ID_LISTVIEW2, wxDefaultPosition, wxDefaultSize, wxLC_LIST, wxDefaultValidator, _T("ID_LISTVIEW2"));
	StaticBoxSizer1->Add(lvStations, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel11 = new wxPanel(Panel9, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	btStopAtStation = new wxButton(Panel11, ID_BUTTON5, _("<--"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	BoxSizer9->Add(btStopAtStation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btAddStation = new wxButton(Panel11, ID_BUTTON3, _("add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer9->Add(btAddStation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btEditStation = new wxButton(Panel11, ID_BUTTON4, _("edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer9->Add(btEditStation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel11->SetSizer(BoxSizer9);
	BoxSizer9->Fit(Panel11);
	BoxSizer9->SetSizeHints(Panel11);
	StaticBoxSizer1->Add(Panel11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel9->SetSizer(StaticBoxSizer1);
	StaticBoxSizer1->Fit(Panel9);
	StaticBoxSizer1->SetSizeHints(Panel9);
	BoxSizer7->Add(Panel9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(BoxSizer7);
	BoxSizer7->Fit(Panel7);
	BoxSizer7->SetSizeHints(Panel7);
	BoxSizer6->Add(Panel7, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	panMiddle->SetSizer(BoxSizer6);
	BoxSizer6->Fit(panMiddle);
	BoxSizer6->SetSizeHints(panMiddle);
	BoxSizer2->Add(panMiddle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(Panel1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	btOK = new wxButton(Panel4, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer3->Add(btOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btCancel = new wxButton(Panel4, ID_BUTTON2, _("cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer3->Add(btCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel4);
	BoxSizer3->SetSizeHints(Panel4);
	BoxSizer2->Add(Panel4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel1);
	BoxSizer2->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_BEGIN_LABEL_EDIT,(wxObjectEventFunction)&LineEditor::OnlvStopsBeginLabelEdit);
	Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_END_LABEL_EDIT,(wxObjectEventFunction)&LineEditor::OnlvStopsEndLabelEdit);
	Connect(ID_LISTVIEW1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&LineEditor::OnlvStopsItemSelect);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LineEditor::OnbtEditStopClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LineEditor::OnbtRemoveStopClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LineEditor::OnbtStopAtStationClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LineEditor::OnbtAddStationClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LineEditor::OnbtOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LineEditor::OnbtCancelClick);
	//*)

    //if(_imageList)
    //    bcbIconSelect->Append("blah", _imageList->GetBitmap(0));

	wxListItem colStation;
	wxListItem colTime;

	colStation.SetText("Station");
	colStation.SetId(0);

	colTime.SetText("Time");
	colTime.SetId(1);

	lvStops->InsertColumn(1,colStation);
	lvStops->InsertColumn(0,colTime);

    std::stringstream ss;
    ss << _line.getNumber();
	txtNumber->SetValue(ss.str());
	txtName->SetValue(_line.getName());

	const StationList& stations = Stations::instance()->getStationsList();

	for(StationList::const_iterator i = stations.begin(); i != stations.end(); ++i )
    {
        long itemIndex = lvStations->InsertItem(lvStations->GetItemCount(), (*i).getName());
        lvStations->SetItemData(itemIndex,(*i).getID());
    }



    long itemIndex = lvStops->InsertItem(0, "+0:00");
        lvStops->SetItem(itemIndex, 1, "line schedule");
        wxFont font = lvStops->GetItemFont(itemIndex);
        font.MakeItalic();
        lvStops->SetItemFont(itemIndex, font);

    const Line::StopList& stops = _line.getStopsList();
	for(Line::StopList::const_iterator i = stops.begin(); i != stops.end(); ++i )
    {
        try
        {
            wxString t(std::string("+") + (*i).time.toString());
            const Station& station = Stations::instance()->getStation((*i).station);

            long itemIndex = lvStops->InsertItem(lvStations->GetItemCount(), t);
            lvStops->SetItemData(itemIndex, station.getID());
            lvStops->SetItem(itemIndex, 1, station.getName());
            //lvStops->SetItem
        }
        catch(std::invalid_argument& e)
        {
            wxMessageBox(e.what());
        }
    }

    //lvStops->SortItems(StopCompareFuncASC, 0);


}

LineEditor::~LineEditor()
{
	//(*Destroy(LineEditor)
	//*)
}

void LineEditor::apply()
{
    _line.setTimetable(panTimetable->getTimetable());
    _line.clearStops();
    for(long i = 1; i < lvStops->GetItemCount(); ++i)
    {
        TimeOffset t;
        const Station& station = Stations::instance()->getStation((Station::ID)lvStops->GetItemData(i));
        t.parse(lvStops->GetItemText(i).c_str());
        _line.addStop(station.getID(), t);
    }

}

void LineEditor::OnbtOKClick(wxCommandEvent& event)
{
    apply();
    EndDialog(LE_RC_OK);
}

void LineEditor::OnbtCancelClick(wxCommandEvent& event)
{

    EndDialog(LE_RC_CANCEL);
}

void LineEditor::OnbtStopAtStationClick(wxCommandEvent& event)
{
    for(long i = lvStations->GetFirstSelected(); -1 != i; i = lvStations->GetNextSelected(i))
    {
        try
        {
            //lvStops->GetItemText(lvStops->GetItemCount()-1);
            TimeOffset offset(lvStops->GetItemText(lvStops->GetItemCount()-1));
            ++offset;

            const Station& station = Stations::instance()->getStation((Station::ID)lvStations->GetItemData(i));

            long itemIndex = lvStops->InsertItem(lvStops->GetItemCount(), std::string("+") + offset.toString());
            lvStops->SetItem(itemIndex, 1, station.getName());
            lvStops->SetItemData(itemIndex, station.getID());
        }
        catch( std::invalid_argument& e)
        {
            wxMessageBox(e.what());
        }
    }

}

void LineEditor::OnbtAddStationClick(wxCommandEvent& event)
{
    Station::ID nextID = Stations::instance()->peekNextFreeID();
    std::stringstream ss;
    ss << "Station " << nextID;
    wxString name = wxGetTextFromUser("Name for the new station:", "scheduler", ss.str(), this);
    if(!name.empty())
    {
        //Station NewStation(std::string(name.c_str()));
        Station& station = Stations::instance()->addStation(Station(std::string(name.c_str())));

        long itemIndex = lvStations->InsertItem(lvStations->GetItemCount(), station.getName());
        lvStations->SetItemData(itemIndex, station.getID());
    }
    else
        return;
}

void LineEditor::OnbtRemoveStopClick(wxCommandEvent& event)
{
    for(long i = lvStops->GetFirstSelected(); -1 != i; i = lvStops->GetFirstSelected())
    {
        lvStops->DeleteItem(i);
    }
}

void LineEditor::OnlvStopsEndLabelEdit(wxListEvent& event)
{
    if(event.IsEditCancelled()) return;
    TimeOffset t;
    std::string s(event.GetText());
    t.parse(s);

    lvStops->SetItemText(event.GetItem().GetId(),std::string("+") + t.toString());
    panTimetable->setOffset(t);
    panTimetable->refresh();
    event.Veto();

}

void LineEditor::OnlvStationsItemSelect(wxListEvent& event)
{

}

void LineEditor::OnlvStopsItemSelect(wxListEvent& event)
{
    panTimetable->setOffset(TimeOffset(event.GetText()));
    panTimetable->refresh();
}

void LineEditor::OnlvStationsBeginLabelEdit(wxListEvent& event)
{

}

void LineEditor::OnlvStopsBeginLabelEdit(wxListEvent& event)
{
    if(event.GetIndex() == 0) event.Veto();
}

void LineEditor::OnbtEditStopClick(wxCommandEvent& event)
{
    long index = lvStops->GetFirstSelected();
    if(index >= 0)
        lvStops->EditLabel(index);
}
