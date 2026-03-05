#pragma once
#include <wx/wx.h>
#include "Account.h"
#include <vector>
#include "AccountBox.h"
#include <fstream>
#include <string>


class listBox : public wxPanel
{
    std::vector<Account>* accounts;
    std::vector<AccountBox*>* boxes;
    wxTextCtrl* ans;
    wxChoice* choice;
    wxButton* ok;
    wxStaticText* result;
    bool isIncome;
    wxChoice* cate;
    
public:
    
    void OnConfirm(wxCommandEvent& event);
    void changein();
    void changeex();
    void saveincome(wxString r);
    void saveexpense(wxString r);
    listBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, std::vector<AccountBox*>* bxs, bool incomemode);
    
};

