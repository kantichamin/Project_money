#pragma once
#include<wx/wx.h>
#include"TaxFam.h"
class TaxInsurance;
class TaxFund : public wxPanel {
public:
	void UpdateN();
	TaxFund(wxWindow* parent, wxPanel* main_panel);
	double n2 = 0.0 ;
private:
	wxPanel* mainpanel;
	wxPanel* panelfund;
	TaxInsurance* panelinsurance;
	wxTextCtrl* pvdtext;
	wxTextCtrl* fundtext;
	wxTextCtrl* livetext;


};

