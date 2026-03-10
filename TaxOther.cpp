#include "TaxOther.h"
#include "main.h"
#include "MainFrame.h"
#include"TaxInsurance.h"

using namespace std;
void TaxOther::OnSummarize(wxCommandEvent& evt) {

	UpdateN();
	if (mainpanel) {
		// 1. รวมค่าลดหย่อนจากทุกหน้า
		double totalDeduction = mainpanel->FamilyDeduction  // จากหน้า TaxFam
			+ mainpanel->FamilyDuck      // จากหน้า TaxFund
			+ mainpanel->FamilySwan      // จากหน้า TaxInsurance
			+ mainpanel->FamilyChicken;  // จากหน้านี้


		double tax = mainpanel->Tax;
		tax -= totalDeduction;
		if (tax < 0) tax = 0;

		totle->SetLabel(wxString::Format(wxString::FromUTF8("%.2f"), tax));
		totle->Show();
		panelother->Layout();
	}

}
void TaxOther::UpdateN() {
	n4 = 0;

	double numBefore = 0, numAfter = 0, num = 0;
	governmenttext->GetValue().ToDouble(&numBefore);
	savetext->GetValue().ToDouble(&numAfter);
	teachertext->GetValue().ToDouble(&num);
	//n4 += (numBefore * 30000) + (numAfter * 60000) + (num * 60000);
	n4 = numBefore + numAfter + num;

	main* frame = dynamic_cast<main*>(wxGetTopLevelParent(this));
	if (frame) frame->FamilyChicken = n4;

	if (mainpanel) mainpanel->FamilyChicken = n4;

}

TaxOther::TaxOther(wxWindow* parent, main* main_panel, TaxInsurance* prevPanel) :wxPanel(parent, wxID_ANY) {
	prev = prevPanel;
	mainpanel = main_panel;
	panelother = new wxPanel(this);
	panelother->Show(true);
	panelother->SetBackgroundColour(wxColour(80, 80, 80));
	wxPanel* bar = new wxPanel(panelother, wxID_ANY);
	bar->SetBackgroundColour(wxColour(60, 60, 60));
	wxPanel* governmenttextanswer = new wxPanel(panelother, wxID_ANY);
	wxPanel* savetextanswer = new wxPanel(panelother, wxID_ANY);
	wxPanel* teachertextanswer = new wxPanel(panelother, wxID_ANY);
	wxPanel* success = new wxPanel(panelother, wxID_ANY);



	//---------------------------------------


	wxStaticText* text = new wxStaticText(bar, wxID_ANY, wxString::FromUTF8("รายการลดหย่อนภาษี : กองทุนอื่นๆ"));
	text->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(bar, wxID_ANY, " << ");
	back->SetBackgroundColour(wxColour(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);

	wxButton* backh = new wxButton(panelother, wxID_ANY, L"🏚️");
	backh->SetBackgroundColour(wxColour(60, 60, 60));
	backh->SetForegroundColour(*wxWHITE);


	wxStaticText* government = new wxStaticText(panelother, wxID_ANY, wxString::FromUTF8("กองทุนบำเหน็จบำนาญข้าราชการ (กบข.)"));
	government->SetForegroundColour(*wxWHITE);
	governmenttext = new wxTextCtrl(governmenttextanswer, wxID_ANY, wxString::FromUTF8(""));
	wxStaticText* warninggovernment = new wxStaticText(panelother, wxID_ANY, wxString::FromUTF8("*ไม่เกิน 15% ของรายได้ทั้งปี และรวมกับกองทุนอื่นไม่เกิน 500,000 บาท*"));
	warninggovernment->SetForegroundColour(*wxWHITE);

	wxStaticText* save = new wxStaticText(panelother, wxID_ANY, wxString::FromUTF8("กองทุนออมแห่งชาติ (กอช.)"));
	save->SetForegroundColour(*wxWHITE);
	savetext = new wxTextCtrl(savetextanswer, wxID_ANY, wxString::FromUTF8(""));
	wxStaticText* warningsave = new wxStaticText(panelother, wxID_ANY, wxString::FromUTF8("*ไม่เกิน 13,200 บาท และรวมกับกองทุนอื่นและเบี้ยประกันชีวิตแบบบำนาญแล้วไม่เกิน 500,000 บาท*"));
	warningsave->SetForegroundColour(*wxWHITE);

	wxStaticText* teacher = new wxStaticText(panelother, wxID_ANY, wxString::FromUTF8("กองทุนออมแห่งชาติ (กอช.)"));
	teacher->SetForegroundColour(*wxWHITE);
	teachertext = new wxTextCtrl(teachertextanswer, wxID_ANY, wxString::FromUTF8(""));
	wxStaticText* warningteacher = new wxStaticText(panelother, wxID_ANY, wxString::FromUTF8("*ไม่เกิน 13,200 บาท และรวมกับกองทุนอื่นและเบี้ยประกันชีวิตแบบบำนาญแล้วไม่เกิน 500,000 บาท*"));
	warningteacher->SetForegroundColour(*wxWHITE);

	summarize = new wxButton(panelother, wxID_ANY, wxString::FromUTF8(" คำนวนภาษี "));
	summarize->SetBackgroundColour(wxColour(60, 60, 60));
	summarize->SetForegroundColour(*wxWHITE);

	

	totle = new wxStaticText(panelother, wxID_ANY, "");
	totle->SetForegroundColour(*wxWHITE);
	totle->Hide();

	

	//---------------------------------------

	wxBoxSizer* FirstROW = new wxBoxSizer(wxHORIZONTAL);
	FirstROW->Add(text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->AddStretchSpacer();
	FirstROW->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	bar->SetSizer(FirstROW);

	wxBoxSizer* secROW = new wxBoxSizer(wxHORIZONTAL);
	secROW->Add(governmenttext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	governmenttextanswer->SetSizer(secROW);

	wxBoxSizer* threeeROW = new wxBoxSizer(wxHORIZONTAL);
	threeeROW->Add(savetext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	savetextanswer->SetSizer(threeeROW);

	wxBoxSizer* fourROW = new wxBoxSizer(wxHORIZONTAL);
	fourROW->Add(teachertext, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	teachertextanswer->SetSizer(fourROW);

	wxBoxSizer* successSizer = new wxBoxSizer(wxHORIZONTAL);
	successSizer->Add(summarize, 0, wxALL | wxALIGN_CENTER, 10);
	success->SetSizer(successSizer);

	//------------------------------

	wxBoxSizer* mainSize = new wxBoxSizer(wxVERTICAL);
	mainSize->Add(bar, 0, wxEXPAND);
	mainSize->Add(government, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(governmenttextanswer, 0, wxEXPAND);
	mainSize->Add(warninggovernment, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(save, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(savetextanswer, 0, wxEXPAND);
	mainSize->Add(warningsave, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(teacher, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(teachertextanswer, 0, wxEXPAND);
	mainSize->Add(warningteacher, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(summarize, 0, wxALL | wxALIGN_CENTER, 10);
	mainSize->Add(totle, 0, wxALL | wxALIGN_CENTER, 10);
	mainSize->Add(backh, 0, wxALL | wxALIGN_CENTER, 10);
	panelother->SetSizer(mainSize);

	//------------------------------

	governmenttext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	savetext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	teachertext->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });

	//-----------------------------

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide(); 
		prev->Show(); 
		GetParent()->Layout(); 
		
		});

	backh->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		MainFrame* frame = dynamic_cast<MainFrame*>(wxGetTopLevelParent(this));

		frame->taxpanel->Hide();
		frame->mainPanel->Show();

		frame->Refreshinfo();
		frame->Layout();
		});

	summarize->Bind(wxEVT_BUTTON, &TaxOther::OnSummarize, this);

			totle->SetLabel(wxString::Format(wxString::FromUTF8("%.2f"), tax));
			totle->Show();
			panelother->Layout();
		}
		});

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(panelother, 1, wxEXPAND);
	this->SetSizer(frameSizer);
	this->Layout();

}

