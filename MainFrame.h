#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <string>
#include <fstream>


struct MandCate {
    std::map<std::string, double> monthlycatett;
};

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

    std::map<std::string, double> monthlyintotal;
    std::map<std::string, MandCate> monthlyextotal;
    double totalExpenseAll;

    void Calintotal();
    void Calextotal();

    void RefreshDashboard();

};
