#include "MyWishlistPanel.h"
#include "WishListBox.h"
#include <fstream>

using namespace std;
wxString MyWishlistPanel::AskGoal() {
	wxTextEntryDialog dlg(this, "Enter you goal: ");
	if (dlg.ShowModal() == wxID_OK)   return dlg.GetValue();
	else return "";
}

int MyWishlistPanel::AskAmount() {
	wxTextEntryDialog dlg(this, "Enter the amount: ");
	if (dlg.ShowModal() == wxID_OK)   return wxAtoi(dlg.GetValue());
	else return 0;
}

int MyWishlistPanel::AskAccount() {
	wxArrayString ac;
	for (const auto& a : *accounts) ac.Add(wxString::FromUTF8(a.name));
	wxSingleChoiceDialog dlg(this, "Account you take from: ", "Accounts", ac);
	if (dlg.ShowModal() == wxID_OK) return dlg.GetSelection();
	else return 0;
}

void MyWishlistPanel::SaveWish() {
	ofstream Wishfile("wishlist.txt");
	if (!Wishfile.is_open()) return;
	for (const auto& g : goals)
		Wishfile << g.wish << "|" << g.amount << "|" << g.accountindex << "|" << g.currentAmount << endl;
	Wishfile.close();
}

void MyWishlistPanel::LoadWish() {
	goals.clear();
	for (auto* box : boxgoals)
		box->Destroy();
	boxgoals.clear();
	ifstream Wishfile("wishlist.txt");
	string text;
	if (!Wishfile.is_open()) return;
	while (getline(Wishfile, text)) {
		size_t pos = text.find('|');
		size_t pos1 = text.find('|', pos + 1);
		size_t pos2 = text.find('|', pos1 + 1);
		if (pos == -1 || pos1 == -1 || pos2 == -1) continue;
			wxString w = text.substr(0, pos);
			double a = stof(text.substr(pos+1,pos1-pos-1));
			int i = stod(text.substr(pos1 + 1, pos2-pos1-1));
			double c = stof(text.substr(pos2 + 1));
			if (i >= accounts->size())
				continue;
			goals.emplace_back(w, a, i, c);
			WishListBox* boxw = new WishListBox(scroll, wishlist, accounts, boxes, &goals.back());
			boxgoals.push_back(boxw);
			wishlist->Layout();
			this->Layout();
		
	}

}

MyWishlistPanel::MyWishlistPanel(wxWindow* parent, wxPanel* main_panel, std::vector<Account>* accs, std::vector<AccountBox*>* bxs)
	:wxPanel(parent,wxID_ANY), accounts(accs), boxes(bxs)
{
	mainpanel=main_panel;
	wxPanel* topbarwish = new wxPanel(this);
	topbarwish->SetBackgroundColour(wxColor(60, 60, 60));
	wxStaticText* titletext = new wxStaticText(topbarwish, wxID_ANY, "Wish List");
	titletext->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	titletext->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(topbarwish, wxID_ANY, "<<", wxDefaultPosition, wxSize(30, 20));
	back->SetBackgroundColour(wxColor(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);

	wxButton* Addwish = new wxButton(this, wxID_ANY, "+", wxDefaultPosition, wxSize(20, 20));
	Addwish->SetBackgroundColour(wxColor(60, 60, 60));
	Addwish->SetForegroundColour(*wxWHITE);

	scroll = new wxScrolledWindow(this);
	scroll->SetBackgroundColour(wxColor(80, 80, 80));
	scroll->SetScrollRate(0, 5);
	wishlist = new wxBoxSizer(wxVERTICAL);
	scroll->SetSizer(wishlist);

	Addwish->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		wxString goal = AskGoal();
		if (goal.IsEmpty()) return;
		int amount = AskAmount();
		int accin = AskAccount();
		goals.emplace_back(goal, amount, accin,0);
		WishListBox* box = new WishListBox(scroll, wishlist, accounts, boxes, &goals.back());
		boxgoals.push_back(box);
		wishlist->Layout();
		scroll->FitInside();
		scroll->Layout();
		});

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(titletext, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	topSizer->AddStretchSpacer();
	topSizer->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	topbarwish->SetSizer(topSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(topbarwish, 0, wxEXPAND);
	mainSizer->AddSpacer(10);
	mainSizer->Add(Addwish, 0, wxALL,10);
	mainSizer->Add(scroll, 1, wxEXPAND | wxALL, 10);
	this->SetSizer(mainSizer);
	this->Layout();

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide();
		mainpanel->Show();
		mainpanel->GetParent()->Layout();
		});
	
	
}