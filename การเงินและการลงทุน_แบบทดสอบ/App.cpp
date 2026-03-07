#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainframe = new MainFrame(wxT("แบบทดสอบการลงทุน"));
	mainframe->SetClientSize(800, 750);
	mainframe->Center();
	mainframe->Show();
	return true;
}
