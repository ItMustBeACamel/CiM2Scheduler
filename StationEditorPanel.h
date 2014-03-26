#ifndef STATIONEDITORPANEL_H
#define STATIONEDITORPANEL_H

//(*Headers(StationEditorPanel)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/grid.h>
//*)

class StationEditorPanel: public wxPanel
{
	public:

		StationEditorPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~StationEditorPanel();

		//(*Declarations(StationEditorPanel)
		wxGrid* gdTimetable;
		wxPanel* panTimetable;
		//*)


	protected:

		//(*Identifiers(StationEditorPanel)
		static const long ID_TIMETABLE_GRID;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(StationEditorPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
