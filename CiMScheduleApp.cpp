/***************************************************************
 * Name:      CiMScheduleApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2014-03-16
 * Copyright:  ()
 * License:
 **************************************************************/

#include "CiMScheduleApp.h"

//(*AppHeaders
#include "CiMScheduleMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CiMScheduleApp);

bool CiMScheduleApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CiMScheduleFrame* Frame = new CiMScheduleFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
