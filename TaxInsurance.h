#pragma once
#include<wx/wx.h>
#include "TaxOther.h"
class TaxInsurance : public wxPanel {
public:
	TaxInsurance(wxWindow* parent, wxPanel* main_panel);
private:
	wxPanel* mainpanel;
	wxPanel* panelfund;
	wxPanel* panelinsurance;
	TaxOther* panelother;


};

