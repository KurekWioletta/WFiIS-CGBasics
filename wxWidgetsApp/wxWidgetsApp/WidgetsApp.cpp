#include "WidgetsApp.h"

wxIMPLEMENT_APP(WidgetsApp);

bool WidgetsApp::OnInit()
{
	Frame *frame = new Frame();
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}
