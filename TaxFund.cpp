#include "TaxFund.h"
#include "TaxInsurance.h"
#include "main.h"
#include "TaxFam.h"
using namespace std;
void TaxFund::UpdateN() {
	n2 = 0;

	double numBefore = 0, numAfter = 0, num = 0;
	pvdtext->GetValue().ToDouble(&numBefore);
	fundtext->GetValue().ToDouble(&numAfter);
	livetext->GetValue().ToDouble(&num);
	n2 += (numBefore * 30000) + (numAfter * 60000) + (num * 60000);

	main* frame = dynamic_cast<main*>(wxGetTopLevelParent(this));
	if (frame) frame->FamilyDuck = n2;

	if (mainpanel) mainpanel->FamilyDuck = n2;

}
TaxFund::TaxFund(wxWindow* parent, main* main_panel, TaxFam* prevPanel) :wxPanel(parent, wxID_ANY) {
	prev = prevPanel;
	this->mainpanel = main_panel;
	panelfund = new wxPanel(this);
	panelfund->Show(true);
	panelfund->SetBackgroundColour(wxColour(80, 80, 80));
	wxPanel* bar = new wxPanel(panelfund, wxID_ANY);
	bar->SetBackgroundColour(wxColour(60, 60, 60));
	wxPanel* pvdtextanswer = new wxPanel(panelfund, wxID_ANY);
	wxPanel* fundtextanswer = new wxPanel(panelfund, wxID_ANY);
	wxPanel* livetextanswer = new wxPanel(panelfund, wxID_ANY);

	//----------------------------------
	
	wxStaticText* text = new wxStaticText(bar, wxID_ANY, wxString::FromUTF8("รายการลดหย่อนภาษี : กองทุน เงินประกันสังคม และที่อยู่อาศัย"));
	text->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(bar, wxID_ANY, " << ");
	back->SetBackgroundColour(wxColour(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);
	wxButton* next = new wxButton(bar, wxID_ANY, " >> ");
	next->SetBackgroundColour(wxColour(60, 60, 60));
	next->SetForegroundColour(*wxWHITE);

	wxStaticText* pvd = new wxStaticText(panelfund, wxID_ANY, wxString::FromUTF8("ค่าลดหย่อนกองทุนสำรองเลี้ยงชีพ (PVD) : ไม่เกิน 15% ของเงินเดือน (ไม่รวมเงินสมทบจากนายจ้าง) และไม่เกิน 500,000 บาท"));
	pvd->SetForegroundColour(*wxWHITE);
	pvdtext = new wxTextCtrl(pvdtextanswer, wxID_ANY, wxString::FromUTF8(""));
	pvdtext->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* fund = new wxStaticText(panelfund, wxID_ANY, wxString::FromUTF8("เงินประกันสังคม : ไม่เกิน 9,000 บาท"));
	fund->SetForegroundColour(*wxWHITE);
	fundtext = new wxTextCtrl(fundtextanswer, wxID_ANY, wxString::FromUTF8(""));
	fundtext->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* live = new wxStaticText(panelfund, wxID_ANY, wxString::FromUTF8("ดอกเบี้ยซื้อที่อยู่อาศัย : ไม่เกิน 100,000 บาท"));
	live->SetForegroundColour(*wxWHITE);
	livetext = new wxTextCtrl(livetextanswer, wxID_ANY, wxString::FromUTF8(""));
	livetext->SetBackgroundColour(wxColour(200, 200, 200));

	//--------------------------------

	wxBoxSizer* FirstROW = new wxBoxSizer(wxHORIZONTAL);
	FirstROW->Add(text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->AddStretchSpacer();
	FirstROW->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->Add(next, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	bar->SetSizer(FirstROW);

	wxBoxSizer* secROW = new wxBoxSizer(wxHORIZONTAL);
	secROW->Add(pvdtext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	pvdtextanswer->SetSizer(secROW);

	wxBoxSizer* threeROW = new wxBoxSizer(wxHORIZONTAL);
	threeROW->Add(fundtext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fundtextanswer->SetSizer(threeROW);

	wxBoxSizer* fourROW = new wxBoxSizer(wxHORIZONTAL);
	fourROW->Add(livetext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	livetextanswer->SetSizer(fourROW);

	//-----------------------------------------

	wxBoxSizer* mainSize = new wxBoxSizer(wxVERTICAL);
	mainSize->Add(bar, 0, wxEXPAND);
	mainSize->Add(pvd, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(pvdtextanswer, 0, wxEXPAND);
	mainSize->Add(fund, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(fundtextanswer, 0, wxEXPAND);
	mainSize->Add(live, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(livetextanswer, 0, wxEXPAND);
	panelfund->SetSizer(mainSize);

	//----------------------------------------

	pvdtext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	fundtext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	livetext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	//------------------------------------

	panelinsurance = new TaxInsurance(this, mainpanel,this);
	panelinsurance->Show(false);

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide();
		prev->Show();
		GetParent()->Layout();
		});

	next->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		UpdateN();

		panelfund->Hide();
		panelinsurance->Show();

		Layout();
		GetParent()->Layout();

		});

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(panelfund, 1, wxEXPAND);
	frameSizer->Add(panelinsurance, 1, wxEXPAND);
	this->SetSizer(frameSizer);
	this->Layout();
}