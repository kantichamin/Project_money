#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    wxStaticText* m_incomeTotal;
    wxStaticText* m_expenseTotal;
    wxStaticText* m_balanceTotal;
    wxStaticText* m_deductionTotal;
    wxStaticText* m_taxResult;
    wxListCtrl* m_listCtrl;

    void RefreshDashboard();
};