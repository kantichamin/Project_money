#include "WishListBox.h"


WishListBox::WishListBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, std::vector<AccountBox*>* bxs,WishList* g) 
	: wxPanel(parent), accounts(accs), boxes(bxs), goals(g) {

	Goal = new wxStaticText(this, wxID_ANY, goals->wish);
	Goal->SetForegroundColour(*wxWHITE);
	wxString m = wxString::Format("%.2f", goals->amount);
	Amount = new wxStaticText(this, wxID_ANY, "Goal " + m + " from " + (*accounts)[goals->accountindex].name);
	Amount->SetForegroundColour(*wxWHITE);
	Saved = new wxStaticText(this, wxID_ANY, "Saved ");
	Saved->SetForegroundColour(*wxWHITE);
	process = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(250, 25), wxGA_HORIZONTAL | wxGA_SMOOTH);
	double percent = goals->currentAmount * 100.00 / goals->amount;
	process->SetValue(percent);
	process->SetBackgroundColour(wxColour(80, 80, 80));
	process->SetForegroundColour(wxColour(60, 60, 60));
	today = new wxStaticText(this, wxID_ANY, "Today I have saved ");
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

	wxBoxSizer* main = new wxBoxSizer(wxVERTICAL);
	main->Add(Goal, 0, wxALL);
	main->Add(Amount, 0, wxALL);
	main->Add(rowsave, 0, wxALL);
	main->Add(rowtoday, 0, wxALL);
	this->SetSizer(main);
	mainSizer->Add(this, 0, wxALL, 10);

}

//void WishList::refresh() {
//
//}