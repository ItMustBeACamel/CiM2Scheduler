#include "StationEditorPanel.h"



//(*InternalHeaders(StationEditorPanel)




//(*IdInit(StationEditorPanel)
















BEGIN_EVENT_TABLE(StationEditorPanel,wxPanel)
	//(*EventTable(StationEditorPanel)
	//*)
END_EVENT_TABLE()

StationEditorPanel::StationEditorPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    : _currentPlan(0), _currentStop(0)
{
	//(*Initialize(StationEditorPanel)




































































	_stopTable = new wxGridStopTable();
	_renderer = new wxGridCellStopRenderer;
	gdTimetable->SetDefaultRenderer(_renderer);
	gdTimetable->SetTable(_stopTable, true);

	//gdTimetable->AutoSize();



}

StationEditorPanel::~StationEditorPanel()
{
	//(*Destroy(StationEditorPanel)
	//*)
}

StationEditorPanel::StationStopType* StationEditorPanel::addStop(const StationEditorPanel::StationStopType& stop)
{
    return _stopTable->addStop(stop);
}

void StationEditorPanel::setCurrentStop(StationEditorPanel::StationStopType* stop)
{
    _currentStop = stop;
    _renderer->setCurrentStop(_currentStop);
}

void StationEditorPanel::setImageList(wxImageList* imageList)
{
    _renderer->setImageList(imageList);

}

void StationEditorPanel::OnrbPlanSelect(wxCommandEvent& event)
{
    _currentPlan = event.GetInt();
    _renderer->setCurrentPlan(_currentPlan);
    gdTimetable->ForceRefresh();
}