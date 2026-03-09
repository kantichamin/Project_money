#pragma once
#include<wx/wx.h>
class TaxOther : public wxPanel {
public:
	TaxOther(wxWindow* parent, wxPanel* main_panel);
private:
	wxPanel* mainpanel;
	wxPanel* panelother;
	wxPanel* panelinsurance;


};

