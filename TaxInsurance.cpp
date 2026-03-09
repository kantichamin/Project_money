#include "TaxInsurance.h"
#include "TaxOther.h"
#include"main.h"
#include"TaxFund.h"

using namespace std;
void TaxInsurance::UpdateN() {
	n3 = 0;

	double numBefore = 0, numAfter = 0, num = 0;
	livetext->GetValue().ToDouble(&numBefore);
	healthtext->GetValue().ToDouble(&numAfter);
	paranttext->GetValue().ToDouble(&num);
	n3 += (numBefore * 30000) + (numAfter * 60000) + (num * 60000);

	
	if (mainpanel) mainpanel->FamilySwan = n3;

}
TaxInsurance::TaxInsurance(wxWindow* parent, main* main_panel, TaxFund* prevPanel) :wxPanel(parent, wxID_ANY) {
	prev = prevPanel;
	this->mainpanel = main_panel;
	panelinsurance = new wxPanel(this);
	panelinsurance->Show(true);
	panelinsurance->SetBackgroundColour(wxColour(80, 80, 80));
	wxPanel* bar = new wxPanel(panelinsurance, wxID_ANY);
	bar->SetBackgroundColour(wxColour(60, 60, 60));
	wxPanel* livetextanswer = new wxPanel(panelinsurance, wxID_ANY);
	wxPanel* healthtextanswer = new wxPanel(panelinsurance, wxID_ANY);
	wxPanel* paranttextanswer = new wxPanel(panelinsurance, wxID_ANY);
	wxPanel* pensiontextanswer = new wxPanel(panelinsurance, wxID_ANY);

	//--------------------------------------
	

	wxStaticText* text = new wxStaticText(bar, wxID_ANY, wxString::FromUTF8("รายการลดหย่อนภาษี : ประกัน"));
	text->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(bar, wxID_ANY, " << ");
	back->SetBackgroundColour(wxColour(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);
	wxButton* next = new wxButton(bar, wxID_ANY, " >> ");
	next->SetBackgroundColour(wxColour(60, 60, 60));
	next->SetForegroundColour(*wxWHITE);

	wxStaticText* live = new wxStaticText(panelinsurance, wxID_ANY, wxString::FromUTF8("เบี้ยประกันชีวิต : ไม่เกิน 100,000 บาท"));
	live->SetForegroundColour(*wxWHITE);
	livetext = new wxTextCtrl(livetextanswer, wxID_ANY, wxString::FromUTF8(""));
	livetext->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* health = new wxStaticText(panelinsurance, wxID_ANY, wxString::FromUTF8("เบี้ยประกันสุขภาพ : ไม่เกิน 25,000"));
	health->SetForegroundColour(*wxWHITE);
	healthtext = new wxTextCtrl(healthtextanswer, wxID_ANY, wxString::FromUTF8(""));

	wxStaticText* warning = new wxStaticText(panelinsurance, wxID_ANY, wxString::FromUTF8("***เบี้ยประกันชีวิต และประกันสุขภาพรวมกันต้องไม่เกิน 100,000 บาท***"));
	warning->SetForegroundColour(*wxWHITE);

	wxStaticText* parant = new wxStaticText(panelinsurance, wxID_ANY, wxString::FromUTF8("เบี้ยประกันสุขภาพบิดา,มารดา : ไม่เกิน 15,000"));
	parant->SetForegroundColour(*wxWHITE);
	paranttext = new wxTextCtrl(paranttextanswer, wxID_ANY, wxString::FromUTF8(""));
	paranttext->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* pension = new wxStaticText(panelinsurance, wxID_ANY, wxString::FromUTF8("เบี้ยประกันชีวิตบำนาญ"));
	pension->SetForegroundColour(*wxWHITE);
	wxTextCtrl* pensiontext = new wxTextCtrl(pensiontextanswer, wxID_ANY, wxString::FromUTF8(""));
	wxStaticText* warningpension = new wxStaticText(panelinsurance, wxID_ANY, wxString::FromUTF8("*ไม่เกิน 15% ของรายได้ทั้งปี ไม่เกิน 200,000 บาท หากไม่ได้ใช้สิทธิประกันชีวิตทั่วไป สามารถนำมารวมได้สูงสุด 300,000 บาทและรวมกับกองทุนอื่นไม่เกิน 500,000 บาท*"));
	warningpension->SetForegroundColour(*wxWHITE);

	//---------------------------------

	wxBoxSizer* FirstROW = new wxBoxSizer(wxHORIZONTAL);
	FirstROW->Add(text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->AddStretchSpacer();
	FirstROW->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->Add(next, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	bar->SetSizer(FirstROW);

	wxBoxSizer* secROW = new wxBoxSizer(wxHORIZONTAL);
	secROW->Add(livetext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	livetextanswer->SetSizer(secROW);

	wxBoxSizer* threeeROW = new wxBoxSizer(wxHORIZONTAL);
	threeeROW->Add(healthtext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	healthtextanswer->SetSizer(threeeROW);

	wxBoxSizer* fourROW = new wxBoxSizer(wxHORIZONTAL);
	fourROW->Add(paranttext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	paranttextanswer->SetSizer(fourROW);

	wxBoxSizer* fifROW = new wxBoxSizer(wxHORIZONTAL);
	fifROW->Add(pensiontext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	pensiontextanswer->SetSizer(fifROW);

	//-----------------------------------

	wxBoxSizer* mainSize = new wxBoxSizer(wxVERTICAL);
	mainSize->Add(bar, 0, wxEXPAND);
	mainSize->Add(live, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(livetextanswer, 0, wxEXPAND);
	mainSize->Add(health, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(healthtextanswer, 0, wxEXPAND);
	mainSize->Add(warning, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(parant, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(paranttextanswer, 0, wxEXPAND);
	mainSize->Add(pension, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(pensiontextanswer, 0, wxEXPAND);
	mainSize->Add(warningpension, 0, wxALL | wxALIGN_LEFT, 10);
	panelinsurance->SetSizer(mainSize);

	//------------------------------

	livetext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	healthtext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	paranttext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });

	//-----------------------------

	panelother = new TaxOther(this, mainpanel,this);
	panelother->Show(false);

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide();
		prev->Show();
		GetParent()->Layout();
		});

	next->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {

		this->UpdateN();

		panelinsurance->Hide();
		panelother->Show();

		this->Layout();
		this->GetParent()->Layout();

		});
	//------------------------------

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(panelinsurance, 1, wxEXPAND);
	frameSizer->Add(panelother, 1, wxEXPAND);
	this->SetSizer(frameSizer);
	this->Layout();
}