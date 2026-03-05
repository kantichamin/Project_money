#pragma once
#include <vector>
#include <wx/wx.h>
#include <memory>
#include "AccountBox.h"
#include "Account.h"
#include "MyKeepPanel.h"
#include "MyWishlistPanel.h"
#include "MySummaryPanel.h"
#include <fstream>
#include <string>

using namespace std;

class InandEx : public wxPanel
{
public:
	
	wxDateTime now = wxDateTime::Now();
	wxString dateStr = now.Format("%d/%m/%y");
	wxString AskAccountName();
	int AskBalance();
	void LoadAccounts();
	void SaveAccounts();
	void OnClose(wxCloseEvent& event);
	bool IsTodayAlreayWritten(const string& filename, const string& date);
	void SaveCate();
	void LoadCate();
	InandEx(wxWindow* parent, wxPanel* main_panel);
	
	
	
private:
	wxPanel* mainpanel;
	wxPanel* panel;
	wxScrolledWindow* accScroll;
	wxScrolledWindow* inScroll;
	wxScrolledWindow* exScroll;
	MyKeepPanel* Keep_panel;
	MyWishlistPanel* Wish_panel;
	MySummaryPanel* Summary_panel;
	std::vector<Account> accounts;
	std::vector<AccountBox*> boxes;
	std::vector<WishList>* goals;
	std::vector<wxString> cate;
	wxBoxSizer* accountSizer;
	wxBoxSizer* incomelistbox;
	wxBoxSizer* expenselistbox;
};

