#ifndef LINEEDITOR_H
#define LINEEDITOR_H

#include "lines.h"

//(*Headers(LineEditor)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "TimeTablePanel.h"
//*)

enum LE_RC
{
    LE_RC_OK,
    LE_RC_CANCEL
};

class LineEditor: public wxDialog
{
	public:

		LineEditor(Line& line, wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~LineEditor();

		//(*Declarations(LineEditor)
		wxButton* btOK;
		wxButton* btRemoveStop;
		wxButton* btAddStation;
		wxPanel* Panel5;
		wxTextCtrl* txtNumber;
		wxListView* lvStations;
		TimeTablePanel* panTimetable;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxButton* btStopAtStation;
		wxPanel* Panel11;
		wxPanel* Panel9;
		wxPanel* Panel8;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxPanel* panMiddle;
		wxButton* btCancel;
		wxPanel* Panel7;
		wxListView* lvStops;
		wxTextCtrl* txtName;
		wxPanel* Panel2;
		wxPanel* Panel10;
		wxButton* btEditStation;
		//*)

	protected:

		//(*Identifiers(LineEditor)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_PANEL5;
		static const long ID_PANEL2;
		static const long ID_CUSTOM1;
		static const long ID_LISTVIEW1;
		static const long ID_BUTTON6;
		static const long ID_PANEL10;
		static const long ID_PANEL8;
		static const long ID_LISTVIEW2;
		static const long ID_BUTTON5;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_PANEL11;
		static const long ID_PANEL9;
		static const long ID_PANEL7;
		static const long ID_PANEL3;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_PANEL4;
		static const long ID_PANEL1;
		//*)

	private:
	    Line& _line;
	    void apply();

		//(*Handlers(LineEditor)
		void OnListView1BeginDrag(wxListEvent& event);
		void OnbtOKClick(wxCommandEvent& event);
		void OnbtCancelClick(wxCommandEvent& event);
		void OnbtStopAtStationClick(wxCommandEvent& event);
		void OnbtAddStationClick(wxCommandEvent& event);
		void OnbtRemoveStopClick(wxCommandEvent& event);
		void OnlvStopsEndLabelEdit(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
