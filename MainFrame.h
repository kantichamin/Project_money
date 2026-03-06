#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "InandEx.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    wxListCtrl* m_listCtrl;
    InandEx* inandexPanel;
};

