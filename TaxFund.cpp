#include "TaxFund.h"
#include <wx/wx.h>

using namespace std;
TaxFund::TaxFund(wxWindow* parent, wxPanel* main_panel) :wxPanel(parent, wxID_ANY) {
	mainpanel = main_panel;
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
	wxTextCtrl* pvdtext = new wxTextCtrl(pvdtextanswer, wxID_ANY, wxString::FromUTF8(""));
	pvdtext->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* fund = new wxStaticText(panelfund, wxID_ANY, wxString::FromUTF8("เงินประกันสังคม : ไม่เกิน 9,000 บาท"));
	fund->SetForegroundColour(*wxWHITE);
	wxTextCtrl* fundtext = new wxTextCtrl(fundtextanswer, wxID_ANY, wxString::FromUTF8(""));
	fundtext->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* live = new wxStaticText(panelfund, wxID_ANY, wxString::FromUTF8("ดอกเบี้ยซื้อที่อยู่อาศัย : ไม่เกิน 100,000 บาท"));
	live->SetForegroundColour(*wxWHITE);
	wxTextCtrl* livetext = new wxTextCtrl(livetextanswer, wxID_ANY, wxString::FromUTF8(""));
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

	panelinsurance = new TaxInsurance(this, panelfund);
	panelinsurance->Show(false);

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Show(false);
		mainpanel->Show(true);
		mainpanel->GetParent()->Layout();
		this->Layout();
		});

	next->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		panelfund->Show(false);
		panelinsurance->Show(true);
		this->Layout();

		});

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(panelfund, 1, wxEXPAND);
	frameSizer->Add(panelinsurance, 1, wxEXPAND);
	this->SetSizer(frameSizer);
	this->Layout();
}