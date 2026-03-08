#include "WishListBox.h"


WishListBox::WishListBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, std::vector<AccountBox*>* bxs,WishList* g) 
	: wxPanel(parent), accounts(accs), boxes(bxs), goals(g) {

	wxStaticBoxSizer* WishBox = new wxStaticBoxSizer(wxVERTICAL, this);
	WishBox->GetStaticBox()->SetForegroundColour(*wxWHITE);
	WishBox->SetMinSize(wxSize(600, -1));
	Goal = new wxStaticText(this, wxID_ANY, goals->wish);
	Goal->SetFont(wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	Goal->SetForegroundColour(*wxWHITE);
	wxString m = wxString::Format("%.2f", goals->amount);
	Amount = new wxStaticText(this, wxID_ANY, "Goal  " + m + "  from  " + wxString::FromUTF8((*accounts)[goals->accountindex].name));
	Amount->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	Amount->SetForegroundColour(*wxWHITE);
	Saved = new wxStaticText(this, wxID_ANY, "Saved ");
	Saved->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	Saved->SetForegroundColour(*wxWHITE);
	process = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(250, 25), wxGA_HORIZONTAL | wxGA_SMOOTH);
	double percent = goals->currentAmount * 100.00 / goals->amount;
	process->SetValue(percent);
	process->SetBackgroundColour(wxColour(80, 80, 80));
	process->SetForegroundColour(wxColour(60, 60, 60));
	today = new wxStaticText(this, wxID_ANY, "Today I have saved ");
	today->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	today->SetForegroundColour(*wxWHITE);
	tdamount = new wxTextCtrl(this, wxID_ANY, "");
	tdamount->SetForegroundColour(*wxWHITE);
	tdamount->SetBackgroundColour(wxColor(80,80,80));
	ok = new wxButton(this, wxID_ANY, "ok", wxDefaultPosition, wxSize(20,20));
	ok->SetBackgroundColour(wxColor(80, 80, 80));
	ok->SetForegroundColour(*wxWHITE);



	ok->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		double money = wxAtoi(tdamount->GetValue());
		goals->currentAmount += money;
		double percent = goals->currentAmount * 100.00 / goals->amount;
		process->SetValue(percent);
		(*accounts)[goals->accountindex].sub(money);
		(*boxes)[goals->accountindex]->refresh();
		tdamount->SetValue("");
		
		});

	wxBoxSizer* rowsave = new wxBoxSizer(wxHORIZONTAL);
	rowsave->Add(Saved, 0, wxALL, 10);
	rowsave->Add(process, 0, wxALL, 10);

	wxBoxSizer* rowtoday = new wxBoxSizer(wxHORIZONTAL);
	rowtoday->Add(today, 0, wxALL, 10);
	rowtoday->Add(tdamount, 0, wxALL, 10);
	rowtoday->Add(ok, 0, wxALL, 10);

	
	WishBox->Add(Goal, 0, wxALL | wxALIGN_CENTER,10);
	WishBox->Add(Amount, 0, wxLEFT,10);
	WishBox->Add(rowtoday, 0, wxALL);
	WishBox->Add(rowsave, 0, wxALL);
	this->SetSizer(WishBox);
	mainSizer->Add(this, 0, wxALL | wxALIGN_CENTER, 10);

}

//void WishList::refresh() {
//
//}