#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "InandEx.h"
#include "Invest.h"
#include "BarChartPanel.h"

class MainFrame : public wxFrame
{
public:
	void Refreshinfo();
    void OnClose(wxCloseEvent& event);
    MainFrame(const wxString& title);

private:
    wxStaticText* taxText;
    wxStaticText* incomeText;
    wxStaticText* expenseText;
    wxStaticText* netText;
    double net;
    double ttex;
    double ttin;
    wxPanel* mainPanel;
    wxListCtrl* m_listCtrl;
    InandEx* inandexPanel;
    Invest* investPanel;
    BarChartPanel* chart;
};
