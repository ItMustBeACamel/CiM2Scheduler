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
#include "stations.h"
#include "lines.h"
//#include "StationEditorPanel.h"

class CiMScheduleFrame: public wxFrame
{
    public:
        CiMScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CiMScheduleFrame();

    private:

        struct Stop
        {
            typedef Line const * const LinePtrType;
            typedef Line::Stop const * const StopPtrType;
            Stop(const LinePtrType& pLine, const StopPtrType& pStop)
                : line(pLine), stop(pStop)
            {

            }

            const bool operator>(const Stop& x)const
            {
                if(line->getNumber() == x.line->getNumber())
                    return *stop > *x.stop;
                else
                    return line->getNumber() > x.line->getNumber();
            }

            const bool operator<(const Stop& x)const
            {
                if(line->getNumber() == x.line->getNumber())
                    return *stop < *x.stop;
                else
                    return line->getNumber() < x.line->getNumber();
            }
            const LinePtrType line;
            const StopPtrType stop;
        };

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
        static const long ID_BUTTON5;
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
        static const long idMenuQuit;
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(CiMScheduleFrame)
        wxButton* btAddStation;
        wxPanel* Panel5;
        wxButton* btDeleteLine;
        wxListView* lvStations;
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
        wxButton* Button6;
        wxButton* Button5;
        wxButton* btEditLine;
        wxImageList* ilIconSmall;
        wxListView* lvStops;
        wxStatusBar* StatusBar1;
        wxPanel* panRight;
        wxPanel* MainPanel;
        StationEditorPanel* panStationEditor;
        wxPanel* Panel2;
        wxButton* btEditStation;
        wxImageList* ilIcons;
        wxPanel* panLeft;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CIMSCHEDULEMAIN_H
