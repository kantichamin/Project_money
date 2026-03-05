#pragma once
#include <wx/wx.h>
#include "WishList.h"
#include "WishListBox.h"
class MyWishlistPanel : public wxPanel
{
public:
	wxString AskGoal();
	int AskAmount();
	int AskAccount();
	void SaveWish();
	void LoadWish();
	MyWishlistPanel(wxWindow* parent, wxPanel* main_panel, std::vector<Account>* accs, std::vector<AccountBox*>* bxs);
private:
	wxPanel* mainpanel;
	wxBoxSizer* wishlist;
	wxScrolledWindow* scroll;
	std::vector<AccountBox*>* boxes;
	std::vector<Account>* accounts;
	std::vector<WishList> goals;
	std::vector<WishListBox*> boxgoals;

};

