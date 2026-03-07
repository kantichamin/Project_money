#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Finance");
	mainFrame->SetClientSize(800, 750);
	mainFrame->CenterOnScreen();
	mainFrame->Show();
	return true;
}