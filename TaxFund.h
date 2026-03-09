#pragma once
#include<wx/wx.h>
#include"TaxInsurance.h"
class TaxFund : public wxPanel {
public:
	TaxFund(wxWindow* parent, wxPanel* main_panel);
private:
	wxPanel* mainpanel;
	wxPanel* panelfund;
	TaxInsurance* panelinsurance;

};

