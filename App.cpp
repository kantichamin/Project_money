#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MainFrame* frame = new MainFrame("Finance");
    frame->SetClienSize(800, 750);
    frame->CenterOnScreen();
    frame->Show();
    return true;

}
