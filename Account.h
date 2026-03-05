#pragma once
#include <wx/wx.h>
class Account
{
public:
	wxString name;
	double balance;

	Account(const wxString& n, double b);



	void add(double money);
	void sub(double money);
};

