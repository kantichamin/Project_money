#pragma once
#include<wx/wx.h>
#include "TaxOther.h"

#include "main.h"
class TaxFund;
class TaxOther;
class TaxInsurance : public wxPanel {
public:
	void UpdateN();
	TaxInsurance(wxWindow* parent, main* main_panel, TaxFund* prevPanel);
	double n3 = 0.0;
private:
	TaxFund* prev;
	main* mainpanel;
	wxPanel* panelfund;
	wxPanel* panelinsurance;
	TaxOther* panelother;
	wxTextCtrl* livetext;
	wxTextCtrl* healthtext;
	wxTextCtrl* paranttext;


};

