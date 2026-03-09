#pragma once
#include<wx/wx.h>
#include "TaxFund.h"
class TaxFam : public wxPanel{
	public:
		TaxFam(wxWindow* parent, wxPanel* main_panel);
	private:
		wxPanel* mainpanel;
		wxPanel* panelfam;
		TaxFund* panelfund;
	};

