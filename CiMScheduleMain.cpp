/***************************************************************
 * Name:      CiMScheduleMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2014-03-16
 * Copyright:  ()
 * License:
 **************************************************************/

#include "CiMScheduleMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/log.h>

#include<sstream>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include "LineEditor.h"
#include "stations.h"
#include "lines.h"
#include "serializer.h"

//(*InternalHeaders(CiMScheduleFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CiMScheduleFrame)
const long CiMScheduleFrame::ID_LV_STATIONS = wxNewId();
const long CiMScheduleFrame::ID_PANEL5 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON1 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON2 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON3 = wxNewId();
const long CiMScheduleFrame::ID_PANEL6 = wxNewId();
const long CiMScheduleFrame::ID_PANEL2 = wxNewId();
const long CiMScheduleFrame::ID_CUSTOM1 = wxNewId();
const long CiMScheduleFrame::ID_PANEL3 = wxNewId();
const long CiMScheduleFrame::ID_LISTVIEW2 = wxNewId();
const long CiMScheduleFrame::ID_PANEL7 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON5 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON6 = wxNewId();
const long CiMScheduleFrame::ID_PANEL8 = wxNewId();
const long CiMScheduleFrame::ID_PANEL4 = wxNewId();
const long CiMScheduleFrame::ID_PANEL1 = wxNewId();
const long CiMScheduleFrame::ID_LISTVIEW1 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON4 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON7 = wxNewId();
const long CiMScheduleFrame::ID_BUTTON8 = wxNewId();
const long CiMScheduleFrame::ID_PANEL10 = wxNewId();
const long CiMScheduleFrame::ID_PANEL9 = wxNewId();
const long CiMScheduleFrame::ID_MENUITEM2 = wxNewId();
const long CiMScheduleFrame::ID_MENUITEM_OPEN = wxNewId();
const long CiMScheduleFrame::ID_MENU_SAVE = wxNewId();
const long CiMScheduleFrame::ID_MENUITEM5 = wxNewId();
const long CiMScheduleFrame::idMenuQuit = wxNewId();
const long CiMScheduleFrame::ID_MENUITEM1 = wxNewId();
const long CiMScheduleFrame::idMenuAbout = wxNewId();
const long CiMScheduleFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CiMScheduleFrame,wxFrame)
    //(*EventTable(CiMScheduleFrame)
    //*)
END_EVENT_TABLE()

CiMScheduleFrame::CiMScheduleFrame(wxWindow* parent,wxWindowID id)
: _filename(wxString())
{
    //(*Initialize(CiMScheduleFrame)
    wxBoxSizer* BoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxBoxSizer* BoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;
    wxMenuBar* MenuBar;

    Create(parent, wxID_ANY, _("Cities in Motion2 Scheduler"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    MainPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    panLeft = new wxPanel(MainPanel, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, panLeft, _("Stations"));
    Panel1 = new wxPanel(panLeft, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    lvStations = new wxListView(Panel1, ID_LV_STATIONS, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_ALIGN_LEFT|wxLC_EDIT_LABELS, wxDefaultValidator, _T("ID_LV_STATIONS"));
    BoxSizer3->Add(lvStations, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer3);
    BoxSizer3->Fit(Panel1);
    BoxSizer3->SetSizeHints(Panel1);
    StaticBoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2 = new wxPanel(panLeft, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    btAddStation = new wxButton(Panel2, ID_BUTTON1, _("add"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer4->Add(btAddStation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btDelStation = new wxButton(Panel2, ID_BUTTON2, _("delete"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer4->Add(btDelStation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btEditStation = new wxButton(Panel2, ID_BUTTON3, _("edit"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer4->Add(btEditStation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(BoxSizer4);
    BoxSizer4->Fit(Panel2);
    BoxSizer4->SetSizeHints(Panel2);
    StaticBoxSizer1->Add(Panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panLeft->SetSizer(StaticBoxSizer1);
    StaticBoxSizer1->Fit(panLeft);
    StaticBoxSizer1->SetSizeHints(panLeft);
    BoxSizer2->Add(panLeft, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panMiddle = new wxPanel(MainPanel, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    panStationEditor = new StationEditorPanel(panMiddle,ID_CUSTOM1,wxDefaultPosition,wxDefaultSize);
    BoxSizer8->Add(panStationEditor, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panMiddle->SetSizer(BoxSizer8);
    BoxSizer8->Fit(panMiddle);
    BoxSizer8->SetSizeHints(panMiddle);
    BoxSizer2->Add(panMiddle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panRight = new wxPanel(MainPanel, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, panRight, _("Stops"));
    Panel3 = new wxPanel(panRight, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    lvStops = new wxListView(Panel3, ID_LISTVIEW2, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTVIEW2"));
    BoxSizer5->Add(lvStops, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(BoxSizer5);
    BoxSizer5->Fit(Panel3);
    BoxSizer5->SetSizeHints(Panel3);
    StaticBoxSizer2->Add(Panel3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel4 = new wxPanel(panRight, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    Button5 = new wxButton(Panel4, ID_BUTTON5, _("delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer6->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button6 = new wxButton(Panel4, ID_BUTTON6, _("edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer6->Add(Button6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel4->SetSizer(BoxSizer6);
    BoxSizer6->Fit(Panel4);
    BoxSizer6->SetSizeHints(Panel4);
    StaticBoxSizer2->Add(Panel4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panRight->SetSizer(StaticBoxSizer2);
    StaticBoxSizer2->Fit(panRight);
    StaticBoxSizer2->SetSizeHints(panRight);
    BoxSizer2->Add(panRight, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MainPanel->SetSizer(BoxSizer2);
    BoxSizer2->Fit(MainPanel);
    BoxSizer2->SetSizeHints(MainPanel);
    BoxSizer1->Add(MainPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel5 = new wxPanel(this, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel5, _("Lines"));
    lvLines = new wxListView(Panel5, ID_LISTVIEW1, wxDefaultPosition, wxDefaultSize, wxLC_ICON, wxDefaultValidator, _T("ID_LISTVIEW1"));
    StaticBoxSizer3->Add(lvLines, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel6 = new wxPanel(Panel5, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    btAddLine = new wxButton(Panel6, ID_BUTTON4, _("add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer7->Add(btAddLine, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btEditLine = new wxButton(Panel6, ID_BUTTON7, _("edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer7->Add(btEditLine, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btDeleteLine = new wxButton(Panel6, ID_BUTTON8, _("delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer7->Add(btDeleteLine, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel6->SetSizer(BoxSizer7);
    BoxSizer7->Fit(Panel6);
    BoxSizer7->SetSizeHints(Panel6);
    StaticBoxSizer3->Add(Panel6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel5->SetSizer(StaticBoxSizer3);
    StaticBoxSizer3->Fit(Panel5);
    StaticBoxSizer3->SetSizeHints(Panel5);
    BoxSizer1->Add(Panel5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MenuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    miNew = new wxMenuItem(Menu1, ID_MENUITEM2, _("New"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(miNew);
    Menu1->AppendSeparator();
    miOpen = new wxMenuItem(Menu1, ID_MENUITEM_OPEN, _("Open"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(miOpen);
    Menu1->AppendSeparator();
    miSave = new wxMenuItem(Menu1, ID_MENU_SAVE, _("Save"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(miSave);
    miSaveAs = new wxMenuItem(Menu1, ID_MENUITEM5, _("Save as..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(miSaveAs);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    miNewLine = new wxMenuItem(Menu3, ID_MENUITEM1, _("New line"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(miNewLine);
    MenuBar->Append(Menu3, _("Lines"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ilIcons = new wxImageList(32, 32, 7);
    ilIcons->Add(wxBitmap(ilIcons_0_XPM));
    ilIcons->Add(wxBitmap(ilIcons_1_XPM));
    ilIcons->Add(wxBitmap(ilIcons_2_XPM));
    ilIcons->Add(wxBitmap(ilIcons_3_XPM));
    ilIcons->Add(wxBitmap(ilIcons_4_XPM));
    ilIcons->Add(wxBitmap(ilIcons_5_XPM));
    ilIconSmall = new wxImageList(16, 16, 7);
    ilIconSmall->Add(wxBitmap(ilIconSmall_0_XPM));
    ilIconSmall->Add(wxBitmap(ilIconSmall_1_XPM));
    ilIconSmall->Add(wxBitmap(ilIconSmall_2_XPM));
    ilIconSmall->Add(wxBitmap(ilIconSmall_3_XPM));
    ilIconSmall->Add(wxBitmap(ilIconSmall_4_XPM));
    ilIconSmall->Add(wxBitmap(ilIconSmall_5_XPM));
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_LV_STATIONS,wxEVT_COMMAND_LIST_END_LABEL_EDIT,(wxObjectEventFunction)&CiMScheduleFrame::OnlvStationsEndLabelEdit);
    Connect(ID_LV_STATIONS,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnlvStationsItemSelect);
    Connect(ID_LV_STATIONS,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnlvStationsItemDeselect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CiMScheduleFrame::OnbtAddStationClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CiMScheduleFrame::OnbtDelStationClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CiMScheduleFrame::OnbtEditStationClick);
    Connect(ID_LISTVIEW2,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnlvStopsItemSelect);
    Connect(ID_LISTVIEW2,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnlvStopsItemDeselect);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CiMScheduleFrame::OnmiNewLineSelected);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CiMScheduleFrame::OnbtEditLineClick);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnmiNewSelected);
    Connect(ID_MENUITEM_OPEN,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnmiOpenSelected);
    Connect(ID_MENU_SAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnmiSaveSelected);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnmiSaveAsSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnQuit);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnmiNewLineSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CiMScheduleFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&CiMScheduleFrame::OnClose);
    //*)

    this->lvLines->AssignImageList(ilIcons, wxIMAGE_LIST_NORMAL);
    this->lvStops->AssignImageList(ilIconSmall, wxIMAGE_LIST_SMALL);

    panStationEditor->setImageList(ilIconSmall);



}

CiMScheduleFrame::~CiMScheduleFrame()
{
    Lines::destroy();
    Stations::destroy();
    //(*Destroy(CiMScheduleFrame)
    //*)
}

void CiMScheduleFrame::refreshStationsList()
{
    lvStations->ClearAll();

    const StationList& stations = Stations::instance()->getStationsList();

    for(StationList::const_iterator i = stations.begin(); i != stations.end(); ++i )
    {
        long itemIndex = lvStations->InsertItem(lvStations->GetItemCount(), (*i).getName());
        lvStations->SetItemData(itemIndex, (*i).getID());
    }
    refreshStopList();
}

void CiMScheduleFrame::refreshLinesList()
{
    lvLines->ClearAll();


    const LineList& lines = Lines::instance()->getLinesList();

    for(LineList::const_iterator i = lines.begin(); i != lines.end(); ++i )
    {
        long itemIndex = lvLines->InsertItem(lvLines->GetItemCount(), (*i).getName(),(*i).getIcon());
        lvLines->SetItemData(itemIndex, (*i).getID());
    }

}

void CiMScheduleFrame::refreshStopList()
{
    lvStops->ClearAll();
    //lvStops->DeleteAllItems();

    wxListItem colLine;
	wxListItem colTime;

	colLine.SetText("Line");
	colLine.SetId(0);

	colTime.SetText("Time");
	colTime.SetId(1);

    lvStops->InsertColumn(0,colLine);
	lvStops->InsertColumn(1,colTime);

	panStationEditor->_stopTable->clearStopList();

    if(lvStations->GetFirstSelected() != -1)
    {
        Station::ID station = (Station::ID)lvStations->GetItemData(lvStations->GetFirstSelected());

        std::list<Stop> newStops;

        LineList& lines = Lines::instance()->getLinesList();
        for(LineList::iterator line = lines.begin(); line != lines.end(); ++line)
        {
            const Line::StopList& stops = (*line).getStopsList();

            for(Line::StopList::const_iterator stop = stops.begin(); stop != stops.end(); ++stop)
            {
                if((*stop).station == station)
                {
                    newStops.push_back(Stop((*line).getID(), (*stop)));
                }
            }
        }
        newStops.sort();

        for(std::list<Stop>::iterator i = newStops.begin(); i != newStops.end(); ++i )
        {
            const Line& line = Lines::instance()->getLine((*i).line);
            std::stringstream ss;
            ss << line.getNumber();
            long itemIndex = lvStops->InsertItem(lvStops->GetItemCount(), ss.str(), line.getIcon());
            lvStops->SetItem(itemIndex, 1, line.getName());
            lvStops->SetItemPtrData(itemIndex, (wxUIntPtr) panStationEditor->addStop((*i)));

            //this->panStationEditor->_stopTable->addStop((*i));
        }


    }

    panStationEditor->_stopTable->refresh();
    panStationEditor->gdTimetable->AutoSize();
    //panStationEditor->gdTimetable->ForceRefresh();

}

void CiMScheduleFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void CiMScheduleFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void CiMScheduleFrame::OnbtAddStationClick(wxCommandEvent& event)
{
    Station::ID nextID = Stations::instance()->peekNextFreeID();
    std::stringstream ss;
    ss << "Station " << nextID;
    wxString name = wxGetTextFromUser("Name for the new station:", "scheduler", ss.str(), this);
    if(!name.empty())
    {
        //Station NewStation(std::string(name.c_str()));
        Station& station = Stations::instance()->addStation(Station(std::string(name.c_str() )));

        long itemIndex = lvStations->InsertItem(lvStations->GetItemCount(), station.getName());
        lvStations->SetItemData(itemIndex, station.getID());
    }
    else
        return;
}

void CiMScheduleFrame::OnbtDelStationClick(wxCommandEvent& event)
{
    for(long i = lvStations->GetFirstSelected(); -1 != i; i = lvStations->GetFirstSelected())
    {
        try
        {
            const Station& station = Stations::instance()->getStation((Station::ID)lvStations->GetItemData(i));

            Stations::instance()->deleteStation(station.getID());
            lvStations->DeleteItem(i);
        }
        catch(std::invalid_argument& e)
        {
            wxMessageBox(e.what());
        }
    }
    refreshStopList();
}

void CiMScheduleFrame::OnbtEditStationClick(wxCommandEvent& event)
{
    for(long i = lvStations->GetFirstSelected(); -1 != i; i = lvStations->GetNextSelected(i))
    {
        try
        {
            Station& station = Stations::instance()->getStation(*((Station::ID*)lvStations->GetItemData(i)));

            wxString name = wxGetTextFromUser("Name for the station:", "scheduler", station.getName(), this);
            if(!name.empty())
            {
                station.setName(name.c_str());
                lvStations->SetItemText(i,name);
            }
        }
        catch(std::invalid_argument& e)
        {
            wxMessageBox(e.what());
        }
    }

}

void CiMScheduleFrame::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto())
    {

    }
    Destroy();

// since the default event handler does call Destroy(), too
    //Lines::destroy();
    //Stations::destroy();
    //wxFrame::OnCloseWindow(event);

}

void CiMScheduleFrame::OnlvStationsEndLabelEdit(wxListEvent& event)
{
    if(!event.GetText().empty())
    {
        Stations::instance()->getStation((Station::ID)event.GetData()).setName(event.GetText().c_str());
        //((Station*)event.GetData())->setName(event.GetText().c_str());
    }
    else
        event.Veto();
}

void CiMScheduleFrame::OnmiNewLineSelected(wxCommandEvent& event)
{
    Line::ID nextID = Lines::instance()->peekNextFreeID();
    std::stringstream ss;
    ss << "Line " << nextID;

    Line newLine(ss.str());

    LineEditor lineEditor(newLine, this, ilIcons);

    int rc = lineEditor.ShowModal();

    switch(rc)
    {
    case LE_RC_OK:
        Lines::instance()->addLine(newLine);
        break;
    case LE_RC_CANCEL:
    default:
        break;
    }
    refreshStationsList();
    refreshLinesList();
}

void CiMScheduleFrame::OnbtEditLineClick(wxCommandEvent& event)
{

    for(long i = lvLines->GetFirstSelected(); -1 != i; i = lvLines->GetNextSelected(i))
    {
        Line& line = Lines::instance()->getLine((Line::ID)lvLines->GetItemData(i));

        LineEditor lineEditor(line, this, ilIcons);

        lineEditor.ShowModal();

    }
    refreshStationsList();
    refreshLinesList();
}

void CiMScheduleFrame::OnlvStationsItemSelect(wxListEvent& event)
{
    refreshStopList();
}

void CiMScheduleFrame::OnlvStopsItemSelect(wxListEvent& event)
{
    panStationEditor->setCurrentStop(((StationEditorPanel::StationStopType*)event.GetData()));
    panStationEditor->refresh();
    //panStationEditor->_stopTable->refresh();
    panStationEditor->gdTimetable->AutoSize();
}

void CiMScheduleFrame::OnlvStopsItemDeselect(wxListEvent& event)
{
    panStationEditor->setCurrentStop(0);
    panStationEditor->refresh();
}

void CiMScheduleFrame::OnlvStationsItemDeselect(wxListEvent& event)
{
    panStationEditor->setCurrentStop(0);
    refreshStopList();
}

void CiMScheduleFrame::OnmiSaveSelected(wxCommandEvent& event)
{
    if(_filename.IsEmpty())
        OnmiSaveAsSelected(event);
    else
        Serializer::saveScheduleToFile(std::string(_filename));

}

void CiMScheduleFrame::OnmiOpenSelected(wxCommandEvent& event)
{

    wxFileDialog
        openFileDialog(this, _("Open XYZ file"), "", "",
            "scheduler files (*.sched)|*.sched", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    // proceed loading the file chosen by the user;
    try
    {
        Serializer::loadScheduleFromFile(std::string(openFileDialog.GetPath()));
    }
    catch(const boost::property_tree::xml_parser::xml_parser_error& e)
    {
        wxLogMessage("error parsing file");
        return;
    }
    catch(const boost::property_tree::ptree_error& e)
    {
        wxLogMessage("error deserializing data");
        Lines::destroy();
        Stations::destroy();
        refreshLinesList();
        refreshStationsList();
        return;
    }

    _filename = openFileDialog.GetPath();
    SetTitle("Cities in Motion2 Scheduler - " + _filename);

    refreshLinesList();
    refreshStationsList();
}

void CiMScheduleFrame::OnmiSaveAsSelected(wxCommandEvent& event)
{
    wxFileDialog
        saveFileDialog(this, _("Open XYZ file"), "", "",
            "scheduler files (*.sched)|*.sched", wxFD_SAVE);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    // proceed loading the file chosen by the user;
    Serializer::saveScheduleToFile(std::string(saveFileDialog.GetPath()));

    _filename = saveFileDialog.GetPath();
    SetTitle("Cities in Motion2 Scheduler - " + _filename);
}

void CiMScheduleFrame::OnmiNewSelected(wxCommandEvent& event)
{
    _filename = "";
    SetTitle("Cities in Motion2 Scheduler");
    Lines::destroy();
    Stations::destroy();
    refreshLinesList();
    refreshStationsList();
}
