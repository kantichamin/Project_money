#pragma once
#include <wx/wx.h>

class WishList 
{
public:
	const wxString wish;
	double amount;
	int accountindex;
	double currentAmount = 0;


	WishList(const wxString &w, double a, int acindex, double currentam);
	void Addw(double money);
};

