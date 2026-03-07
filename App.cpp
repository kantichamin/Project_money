#include "App.h"
#include "mainframe.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	mainframe* mainFrame = new mainframe("Finance");
	mainFrame->SetClientSize(800, 750);
	mainFrame->CenterOnScreen();
	mainFrame->Show();
	return true;
}