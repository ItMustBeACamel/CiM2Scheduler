/***************************************************************
 * Name:      CiMScheduleMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-03-16
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef CIMSCHEDULEMAIN_H
#define CIMSCHEDULEMAIN_H



//(*Headers(CiMScheduleFrame)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include "./wximages/CiMScheduleMain_ilIcons.xpm"
#include <wx/panel.h>
#include "StationEditorPanel.h"
#include <wx/imaglist.h>
#include "./wximages/CiMScheduleMain_ilIconSmall.xpm"
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <list>

#include "stopAtStation.h"


class CiMScheduleFrame: public wxFrame
{
    public:
        CiMScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CiMScheduleFrame();

    private:
        typedef StopAtStation Stop;

        void refreshStationsList();
        void refreshLinesList();
        void refreshStopList();

        //(*Handlers(CiMScheduleFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbtAddStationClick(wxCommandEvent& event);
        void OnbtDelStationClick(wxCommandEvent& event);
        void OnbtEditStationClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnlvStationsEndLabelEdit(wxListEvent& event);
        void OnmiNewLineSelected(wxCommandEvent& event);
        void OnbtEditLineClick(wxCommandEvent& event);
        void OnlvStationsItemSelect(wxListEvent& event);
        void OnlvStopsItemSelect(wxListEvent& event);
        void OnlvStopsItemDeselect(wxListEvent& event);
        void OnlvStationsItemDeselect(wxListEvent& event);
        void OnmiSaveSelected(wxCommandEvent& event);
        void OnmiOpenSelected(wxCommandEvent& event);
        void OnmiSaveAsSelected(wxCommandEvent& event);
        void OnmiNewSelected(wxCommandEvent& event);
        void OnbtDeleteLineClick(wxCommandEvent& event);
        void OnbtToggleHiddenClick(wxCommandEvent& event);
        void OnmiViewLinesSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(CiMScheduleFrame)
        static const long ID_LV_STATIONS;
        static const long ID_PANEL5;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_PANEL6;
        static const long ID_PANEL2;
        static const long ID_CUSTOM1;
        static const long ID_PANEL3;
        static const long ID_LISTVIEW2;
        static const long ID_PANEL7;
        static const long ID_BUTTON6;
        static const long ID_PANEL8;
        static const long ID_PANEL4;
        static const long ID_PANEL1;
        static const long ID_LISTVIEW1;
        static const long ID_BUTTON4;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_PANEL10;
        static const long ID_PANEL9;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM_OPEN;
        static const long ID_MENU_SAVE;
        static const long ID_MENUITEM5;
        static const long idMenuQuit;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(CiMScheduleFrame)
        wxBoxSizer* sizMain;
        wxButton* btAddStation;
        wxButton* btDeleteLine;
        wxMenuItem* miOpen;
        wxListView* lvStations;
        wxMenuItem* miSave;
        wxPanel* Panel4;
        wxListView* lvLines;
        wxMenu* Menu3;
        wxButton* btDelStation;
        wxMenuItem* miNewLine;
        wxPanel* Panel1;
        wxButton* btAddLine;
        wxPanel* Panel6;
        wxPanel* panMiddle;
        wxPanel* Panel3;
        wxButton* btEditLine;
        wxImageList* ilIconSmall;
        wxListView* lvStops;
        wxStatusBar* StatusBar1;
        wxPanel* panRight;
        wxPanel* MainPanel;
        StationEditorPanel* panStationEditor;
        wxMenuItem* miNew;
        wxPanel* panLines;
        wxPanel* Panel2;
        wxMenuItem* miViewLines;
        wxMenuItem* miSaveAs;
        wxButton* btEditStation;
        wxButton* btToggleHidden;
        wxImageList* ilIcons;
        wxMenu* Menu4;
        wxPanel* panLeft;
        //*)

        wxString _filename;

        DECLARE_EVENT_TABLE()
};

#endif // CIMSCHEDULEMAIN_H
