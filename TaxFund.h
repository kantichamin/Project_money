#pragma once
#include<wx/wx.h>
#include "main.h"
class TaxFam;
class TaxInsurance;
class TaxFund : public wxPanel {
public:
	void UpdateN();
	TaxFund(wxWindow* parent, main* main_panel, TaxFam* prevPanel);
	double n2 = 0.0 ;
private:
	TaxFam* prev;
	main* mainpanel;
	wxPanel* panelfund;
	TaxInsurance* panelinsurance;
	wxTextCtrl* pvdtext;
	wxTextCtrl* fundtext;
	wxTextCtrl* livetext;


};

