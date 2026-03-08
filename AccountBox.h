#pragma once
#include <wx/wx.h>
#include "Account.h"

class AccountBox : public wxPanel
{
public:
	std::vector<Account>* accounts;
	int index;
	wxStaticText* label;

	AccountBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, int i);
	void refresh();
};

