#include "MyKeepPanel.h"
#include <fstream>

using namespace std;
void MyKeepPanel::RefreshAccounts() {
	acc->Clear();
	for (const auto& a : *accounts)
		acc->Append(wxString::FromUTF8(a.name));
}

void MyKeepPanel::OnPaint(wxPaintEvent& event) {
	wxPaintDC dc(bottlepanel);

	int bottleWidth = 100;
	int bottleHeight = 200;

	int x = 40;   
	int y = 20;                          

	int waterHeight = bottleHeight * percent / 100.0;

	dc.DrawRectangle(x, y, bottleWidth, bottleHeight);

	dc.SetBrush(*wxGREY_BRUSH);
	dc.DrawRectangle(x,
		y + bottleHeight - waterHeight,
		bottleWidth,
		waterHeight);
	dc.SetTextForeground(*wxWHITE);
	dc.DrawText(wxString::Format("%.0f%%", percent),
		x + 40,
		y + bottleHeight + 10);
}

void MyKeepPanel::OnConfirm(wxCommandEvent& event) {
	goalAmount = wxAtof(goal->GetValue());

	if (goalAmount <= 0) return;
	goalText->SetLabel(wxString::Format("%.0f", goalAmount));
	goal->Hide();
	goalText->Show();

	wxString selectedAcc = acc->GetStringSelection();
	accText->SetLabel(selectedAcc);
	acc->Hide();
	accText->Show();

	
	SaveKeep();

	ok->Disable();

	Layout();
}

void MyKeepPanel::SaveKeep() {
	ofstream goalfile("keep.txt");
	if (!goalfile.is_open()) return;
	goalfile << goalAmount << endl;
	goalfile << currentSaved << endl;
	goalfile << percent << endl;
	goalfile << acc->GetSelection() << endl;
	goalfile.close();
}

void MyKeepPanel::LoadKeep()
{
	ifstream goalfile("keep.txt");

	if (!goalfile.is_open()) return;

	int accIndex;

	goalfile >> goalAmount;
	goalfile >> currentSaved;
	goalfile >> percent;
	goalfile >> accIndex;

	goalfile.close();

	// restore UI
	if (goalAmount > 0)
	{
		goalText->SetLabel(wxString::Format("%.0f", goalAmount));
		goal->Hide();
		goalText->Show();

		acc->SetSelection(accIndex);
		accText->SetLabel(acc->GetStringSelection());
		acc->Hide();
		accText->Show();

		ok->Disable();
	}

	bottlepanel->Refresh();
}

MyKeepPanel::MyKeepPanel(wxWindow* parent,wxPanel* main_panel, std::vector<Account>* accs, std::vector<AccountBox*>* bxs)
	: wxPanel(parent, wxID_ANY), accounts(accs), boxes(bxs)
{
	srand(time(0));
	const char* bank[5] = { "5","10","20","50","100" };
	mainpanel = main_panel;
	// ===== topbar =====
	wxPanel* topbarkeep = new wxPanel(this);
	topbarkeep->SetBackgroundColour(wxColor(60, 60, 60));
	wxStaticText* titletext = new wxStaticText(topbarkeep, wxID_ANY, "Keep Challance");
	titletext->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(topbarkeep, wxID_ANY, "<<", wxDefaultPosition, wxSize(30, 20));
	back->SetBackgroundColour(wxColor(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);

	// ===== goal =====
	ask = new wxStaticText(this, wxID_ANY, "I want to keep ");
	ask->SetForegroundColour(*wxWHITE);
	goal = new wxTextCtrl(this, wxID_ANY, "");
	ask2 = new wxStaticText(this, wxID_ANY, "Today you have ");
	ask2->SetForegroundColour(*wxWHITE);
	save = new wxButton(this, wxID_ANY, "Save", wxDefaultPosition, wxSize(40, 20));
	save->SetForegroundColour(*wxWHITE);
	save->SetBackgroundColour(wxColor(80,80,80));
	money = new wxStaticText(this, wxID_ANY, "      ");
	money->SetForegroundColour(*wxWHITE);
	from = new wxStaticText(this, wxID_ANY, "from");
	from->SetForegroundColour(*wxWHITE);
	wxArrayString names;
	for (const auto& a : *accounts) names.Add(wxString::FromUTF8(a.name));
	acc = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, names);
	ok = new wxButton(this, wxID_ANY, "ok", wxDefaultPosition, wxSize(20, 20));
	ok->SetForegroundColour(*wxWHITE);
	ok->SetBackgroundColour(wxColor(80, 80, 80));
	reset = new wxButton(this, wxID_ANY, "reset", wxDefaultPosition, wxSize(40, 20));
	reset->SetForegroundColour(*wxWHITE);
	reset->SetBackgroundColour(wxColor(80, 80, 80));

	goalText = new wxStaticText(this, wxID_ANY, "");
	goalText->SetForegroundColour(*wxWHITE);
	goalText->Hide();

	accText = new wxStaticText(this, wxID_ANY, "");
	accText->SetForegroundColour(*wxWHITE);
	accText->Hide();

	
	save->Bind(wxEVT_BUTTON, [this,bank](wxCommandEvent&) {
		
		if (goalAmount <= 0) return;
		

		int index = rand() % 5;
		double moneyAdd = wxAtof(bank[index]);

		currentSaved += moneyAdd;

		percent = (currentSaved / goalAmount) * 100.00;

		if (percent > 100) percent = 100;
		money->SetLabel( wxString::Format("%.0f", moneyAdd));
		bottlepanel->Refresh();
		SaveKeep();
		});

	ok->Bind(wxEVT_BUTTON, &MyKeepPanel::OnConfirm, this);

	reset->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		goalAmount = 0;
		currentSaved = 0;
		percent = 0;
		bottlepanel->Refresh();

		goal->SetValue("");
		goal->Show();
		goalText->Hide();

		acc->SetSelection(wxNOT_FOUND);
		acc->Show();
		accText->Hide();

		money->SetLabel("      ");

		SaveKeep();
		ok->Enable();
		Layout();
		});
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(titletext,0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	topSizer->AddStretchSpacer();
	topSizer->Add(back,0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	topbarkeep->SetSizer(topSizer);

	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	box->Add(ask, 0, wxALL, 10);
	box->Add(goal, 0, wxALL, 10);
	box->Add(goalText, 0, wxALL, 10);

	wxBoxSizer* box2 = new wxBoxSizer(wxHORIZONTAL);
	box2->Add(ask2, 0, wxALL, 5);
	box2->Add(save, 0, wxALL, 5);
	box2->Add(money, 0, wxALL, 5);
	box2->Add(from, 0, wxALL, 5);
	box2->Add(acc, 0, wxALL, 5);
	box2->Add(accText, 0, wxALL, 5);
	box2->Add(ok, 0, wxALL, 5);
	box2->Add(reset, 0, wxALL, 5);

	bottlepanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 300));
	bottlepanel->SetBackgroundColour(wxColor(80,80,80));
	bottlepanel->Bind(wxEVT_PAINT, &MyKeepPanel::OnPaint, this);

	LoadKeep();

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(topbarkeep,0,wxEXPAND);
	mainSizer->Add(box, 0, wxALL);
	mainSizer->Add(box2, 0, wxALL);
	mainSizer->Add(bottlepanel, 0, wxALL, 20);
	

	this->SetSizer(mainSizer);
	this->Layout();

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide();
		mainpanel->Show();
		mainpanel->GetParent()->Layout();
		});
}