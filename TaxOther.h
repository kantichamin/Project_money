#pragma once
#include<wx/wx.h>
#include"main.h"

class TaxInsurance;
class TaxOther : public wxPanel {
public:
	void OnSummarize(wxCommandEvent& evt);
	void UpdateN();
	TaxOther(wxWindow* parent, main* main_panel, TaxInsurance* prevPanel);

	double n4 = 0.0;
private:
	double tax;
	TaxInsurance* prev;
	wxButton* summarize;
	main* mainpanel;
	wxPanel* panelother;
	wxStaticText* totle;
	double currentTax;
	wxTextCtrl* governmenttext;
	wxTextCtrl* savetext;
	wxTextCtrl* teachertext;
	

};

