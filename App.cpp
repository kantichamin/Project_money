#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MainFrame* frame = new MainFrame("Rainy Day Dashboard");
    frame->Show(true);
    return true;
}