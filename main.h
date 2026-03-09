#pragma once
#include<wx/wx.h>
#include "TaxFam.h"
class main : public wxPanel
{
private:
	wxPanel* panel;
	TaxFam* panel1;
public:
	main(const wxString& title);
};

