#pragma once
#include<wx/wx.h>
#include"main.h"
#include"TaxInsurance.h"
class TaxOther : public wxPanel {
public:
	void UpdateN();
	TaxOther(wxWindow* parent, wxPanel* main_panel);
	double n4 = 0.0;
private:
	wxPanel* mainpanel;
	wxPanel* panelother;
	wxStaticText* totle;
	double currentTax;
	wxTextCtrl* governmenttext;
	wxTextCtrl* savetext;
	wxTextCtrl* teachertext;
	

};

