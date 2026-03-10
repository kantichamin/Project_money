#include "main.h"
#include "TaxFam.h"

using namespace std;
main::main(wxWindow* parent,wxPanel* main_panel) 
	: wxPanel(parent, wxID_ANY) {
	mainpanel = main_panel;
	panel = new wxPanel(this);
	panel->Show(true);
	panel->SetBackgroundColour(wxColour(80, 80, 80));
	wxPanel* bar = new wxPanel(panel, wxID_ANY);
	bar->SetBackgroundColour(wxColour(60, 60, 60));
	wxPanel* salaryan = new wxPanel(panel, wxID_ANY);
	wxPanel* bonusan = new wxPanel(panel, wxID_ANY);
	wxPanel* anotheran = new wxPanel(panel, wxID_ANY);

	wxStaticText* text = new wxStaticText(bar, wxID_ANY, wxString::FromUTF8("รายรับ"));
	text->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(bar,wxID_ANY," << ");
	back->SetBackgroundColour(wxColour(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);
	wxButton* next = new wxButton(bar, wxID_ANY, " >> ");
	next->SetBackgroundColour(wxColour(60, 60, 60));
	next->SetForegroundColour(*wxWHITE);

	
	wxStaticText* salary = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("เงินเดือน(บาท)"));
	salary->SetForegroundColour(*wxWHITE);
	salaryman = new wxTextCtrl(salaryan, wxID_ANY, wxString::FromUTF8(""));
	salaryman->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* bonus = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("โบนัสรายปี(บาท)"));
	bonus->SetForegroundColour(*wxWHITE);
	wxTextCtrl* bonusman = new wxTextCtrl(bonusan, wxID_ANY, wxString::FromUTF8(""));
	bonusman->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* another = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("รายได้อื่นๆ ทั้งปี เช่น การขายของไลน์ รับจ้างฟรีแลนซ์ (บาท)"));
	another->SetForegroundColour(*wxWHITE);
	wxTextCtrl* anotherman = new wxTextCtrl(anotheran, wxID_ANY, wxString::FromUTF8(""));
	anotherman->SetBackgroundColour(wxColour(200, 200, 200));

	wxBoxSizer* FirstROW = new wxBoxSizer(wxHORIZONTAL);
	FirstROW->Add(text, 0, wxALL |wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->AddStretchSpacer();
	FirstROW->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->Add(next, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	bar->SetSizer(FirstROW);

	//----------------------------------------------
	// --- เพิ่มส่วนนี้เข้าไป (การ Bind Event) ---
	auto calculateTotal = [=]() {
		double s = 0, b = 0, a = 0;

		// ดึงค่าจากทั้ง 3 ช่องมาแปลงเป็นตัวเลข
		salaryman->GetValue().ToDouble(&s);
		bonusman->GetValue().ToDouble(&b);
		anotherman->GetValue().ToDouble(&a);

		double sum = (s * 12) + b + a;
		Tax = 0;

		if (sum <= 150000)
		{
			Tax = 0;
		}
		else if (sum <= 300000)
		{
			Tax = (sum - 150000) * 0.05;
		}
		else if (sum <= 500000)
		{
			Tax = 7500 + (sum - 300000) * 0.10;
		}
		else if (sum <= 750000)
		{
			Tax = 27500 + (sum - 500000) * 0.15;
		}
		else if (sum <= 1000000)
		{
			Tax = 65000 + (sum - 750000) * 0.20;
		}
		else if (sum <= 2000000)
		{
			Tax = 115000 + (sum - 1000000) * 0.25;
		}
		else if (sum <= 5000000)
		{
			Tax = 365000 + (sum - 2000000) * 0.30;
		}
		else
		{
			Tax = 1265000 + (sum - 5000000) * 0.35;
		}

		//Tax -= (FamilyDeduction + FamilyDuck + FamilySwan + FamilyChicken);

		// อัปเดต UI
		this->Layout();
		};

	
	salaryman->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { calculateTotal(); });
	bonusman->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { calculateTotal(); });
	anotherman->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { calculateTotal(); });

	//----------------------------------------------

	wxBoxSizer* mainSize = new wxBoxSizer(wxVERTICAL);
	mainSize->Add(bar, 0, wxEXPAND);
	mainSize->Add(salary, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(salaryan, 0, wxEXPAND);
	mainSize->Add(bonus, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(bonusan, 0, wxEXPAND);
	mainSize->Add(another, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(anotheran, 0, wxEXPAND);
	panel->SetSizer(mainSize);

	wxBoxSizer* Sara = new wxBoxSizer(wxHORIZONTAL);
	Sara->Add(salaryman, 1, wxALL | wxALIGN_CENTER, 10);
	salaryan->SetSizer(Sara);

	wxBoxSizer* bow = new wxBoxSizer(wxHORIZONTAL);
	bow->Add(bonusman, 1, wxALL | wxALIGN_CENTER, 10);
	bonusan->SetSizer(bow);

	wxBoxSizer* ana = new wxBoxSizer(wxHORIZONTAL);
	ana->Add(anotherman, 1, wxALL | wxALIGN_CENTER, 10);
	anotheran->SetSizer(ana);
	//--------------------------------------------------

	panel1 = new TaxFam(this,this);
	panel1->Show(false);

	next->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		panel->Hide();
		panel1->Show();

		Layout();
		GetParent()->Layout();
		});

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide();
		mainpanel->Show();
		mainpanel->GetParent()->Layout();
		});

	//---------------------------------------------------
	

	//tt += FamilyDeduction + FamilyDuck +FamilySwan +FamilyChicken;

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(panel, 1, wxEXPAND);
	frameSizer->Add(panel1, 1, wxEXPAND);

	this->SetSizer(frameSizer);

	//---------------------------------------------------



	
}