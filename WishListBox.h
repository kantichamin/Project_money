#pragma once
#include <wx/wx.h>
#include "Account.h"
#include "AccountBox.h"
#include "WishList.h"

class WishListBox : public wxPanel
{
	wxStaticText* Goal;
	wxStaticText* Amount;
	wxStaticText* Saved;
	wxGauge* process;
	wxStaticText* today;
	wxTextCtrl* tdamount;
	wxButton* ok;


	WishList* goals;
	std::vector<Account>* accounts;
	std::vector<AccountBox*>* boxes;
	
public:
	
	WishListBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, std::vector<AccountBox*>* bxs,WishList* g);
	//void refresh();
};

