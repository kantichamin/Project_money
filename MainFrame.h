#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    wxListCtrl* m_listCtrl;
};
