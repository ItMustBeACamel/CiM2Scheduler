#ifndef TIMETABLEPANEL_H
#define TIMETABLEPANEL_H

#include "timetable.h"
#include "timetable_view.h"

//(*Headers(TimeTablePanel)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
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
	    typedef TimetableView TimetableViewType;
	    typedef TimetableViewType::WeekTimeType WeekTimeType;
	    typedef TimetableType::PlanName PlanNameType;

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
		wxPanel* Panel3;
		wxSpinButton* sbEnd;
		wxPanel* Panel2;
		wxCheckListBox* clbOptions;
		//*)

		void refresh();
		void refreshLayout();
		void setOffset(const TimeOffset& off);
		TimeOffset& getOffset();
		const TimeOffset& getOffset()const;
		void setCollapsed(const bool collapsed);
		const bool isCollapsed();
		Timetable& getTimetable();


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
		static const long ID_CHECKLISTBOX1;
		static const long ID_PANEL3;
		//*)

	private:
        Timetable _timetable;
        PlanNameType _currentPlan;
        TimeOffset _offset;
        bool _collapsed;
        int _gridWidth;

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
		void OnclbOptionsToggled(wxCommandEvent& event);
		void OnsbIntervalChange(wxSpinEvent& event);
		void OntxtBeginTextEnter(wxCommandEvent& event);
		void OntxtEndTextEnter(wxCommandEvent& event);
		void OntxtIntervalTextEnter(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
