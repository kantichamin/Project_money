#pragma once
#include<wx/wx.h>
class TaxFund;
class TaxFam : public wxPanel{
	public:
		double n = 0.0;
		void UpdateN();
		TaxFam(wxWindow* parent, wxPanel* main_panel);
		wxTextCtrl* ownan;
		
	private:
		wxPanel* mainpanel;
		wxPanel* panelfam;
		TaxFund* panelfund;
		wxCheckBox* cbpa1;
		wxCheckBox* cbpa2;
		wxListBox* myChoice;
		wxTextCtrl* ch2561bf;
		wxTextCtrl* ch2561af;
		wxCheckBox* cbchri1;
		wxCheckBox* cbchri2;
		wxCheckBox* cbchri4;
		wxTextCtrl* childhowinfrim;
		wxCheckBox* cbpama1;
		wxCheckBox* cbpama2;
		wxCheckBox* cbchrima1;
		wxCheckBox* cbchrima2;
		wxCheckBox* cbchrima3;
		wxCheckBox* cbchildT;
		
	};

