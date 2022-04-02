#include "YetiApp.h"
#include "YetiFrame.h"

// this will implement the main loop
wxIMPLEMENT_APP(YetiApp);

bool YetiApp::OnInit()
{
	YetiFrame* frame = new YetiFrame();
	frame->Show();
	return true;
}