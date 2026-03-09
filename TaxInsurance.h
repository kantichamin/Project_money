#pragma once
#include<wx/wx.h>
#include "TaxOther.h"
#include"TaxFund.h"
class TaxOther;
class TaxInsurance : public wxPanel {
public:
	void UpdateN();
	TaxInsurance(wxWindow* parent, wxPanel* main_panel);
	double n3 = 0.0;
private:
	wxPanel* mainpanel;
	wxPanel* panelfund;
	wxPanel* panelinsurance;
	TaxOther* panelother;
	wxTextCtrl* livetext;
	wxTextCtrl* healthtext;
	wxTextCtrl* paranttext;


};

