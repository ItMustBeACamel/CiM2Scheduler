#ifndef TIMETABLEPANEL_H
#define TIMETABLEPANEL_H

#include "timetable.h"

//(*Headers(TimeTablePanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/spinbutt.h>
//*)

class TimeTablePanel: public wxPanel
{
	public:
	    typedef Timetable TimetableType;
	    typedef TimetableType::DayTimeType DayTimeType;
	    typedef TimetableType::IntervalType IntervalType;
	    typedef TimeOffset TimeOffsetType;
	    typedef WeekTime WeekTimeType;

		TimeTablePanel(Timetable& timetable, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TimeTablePanel();

		//(*Declarations(TimeTablePanel)
		wxGrid* gdTimetable;
		wxTextCtrl* txtBegin;
		wxRadioBox* rbPlans;
		wxStaticText* StaticText2;
		wxSpinButton* sbInterval;
		wxTextCtrl* txtInterval;
		wxSpinButton* sbBegin;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxTextCtrl* txtEnd;
		wxSpinButton* sbEnd;
		wxPanel* Panel2;
		//*)

		void refresh();
		void setOffset(const TimeOffset& off);
		TimeOffset& getOffset();
		const TimeOffset& getOffset()const;


	protected:

		//(*Identifiers(TimeTablePanel)
		static const long ID_RADIOBOX1;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_SPINBUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_SPINBUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_SPINBUTTON3;
		static const long ID_PANEL2;
		static const long ID_GRID1;
		//*)

	private:
        Timetable _timetable;
        PlanName _currentPlan;
        TimeOffset _offset;

		//(*Handlers(TimeTablePanel)
		void OnrbPlansSelect(wxCommandEvent& event);
		void OngdTimetableResize(wxSizeEvent& event);
		void OnsbBeginChangeUp(wxSpinEvent& event);
		void OnsbBeginChangeDown(wxSpinEvent& event);
		void OnsbEndChangeUp(wxSpinEvent& event);
		void OnsbEndChangeDown(wxSpinEvent& event);
		void OnsbBeginChange(wxSpinEvent& event);
		void OnsbEndChange(wxSpinEvent& event);
		void OngdTimetableCellLeftClick(wxGridEvent& event);
		void OnsbIntervalChangeUp(wxSpinEvent& event);
		void OnsbIntervalChangeDown(wxSpinEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
