#include "TaxFam.h"
#include "TaxFund.h"
#include "main.h"

using namespace std;

void TaxFam::UpdateN() {
	n = 60000; // เริ่มต้นที่ลดหย่อนส่วนบุคคลเสมอ

	// ตรวจสอบ Checkbox พ่อแม่
	if (cbpa1->IsChecked()) n += 30000;
	if (cbpa2->IsChecked()) n += 30000;

	// ตรวจสอบสถานะสมรสจาก ListBox
	if (myChoice->GetStringSelection() == wxString::FromUTF8("คู่สมรสไม่มีเงินได้")) {
		n += 60000;
	}

	// ดึงค่าจากช่องกรอกตัวเลข (ต้องดึงตอนที่ฟังก์ชันนี้ถูกเรียก)
	double numBefore = 0, numAfter = 0, num = 0;
	ch2561bf->GetValue().ToDouble(&numBefore);
	ch2561af->GetValue().ToDouble(&numAfter);
	childhowinfrim->GetValue().ToDouble(&num);
	n += (numBefore * 30000) + (numAfter * 60000) + (num * 60000);

	// ตรวจสอบผู้พิการ
	if (cbchri1->IsChecked()) n += 60000;
	if (cbchri2->IsChecked()) n += 60000;
	if (cbchri4->IsChecked()) n += 60000;

	if (cbpama1->IsChecked()) n += 30000;
	if (cbpama2->IsChecked()) n += 30000;

	if (cbchildT->IsChecked()) n += 30000;

	if (cbchrima1->IsChecked()) n += 60000;
	if (cbchrima2->IsChecked()) n += 60000;
	if (cbchrima3->IsChecked()) n += 60000;
	
	// อัปเดตยอดไปเก็บไว้ที่ Frame หลักเพื่อให้หน้าอื่นดึงไปใช้ได้
	main* frame = dynamic_cast<main*>(wxGetTopLevelParent(this));
	if (frame) frame->FamilyDeduction = n;
}

TaxFam::TaxFam(wxWindow* parent, wxPanel* main_panel):wxPanel(parent, wxID_ANY) {
	mainpanel = main_panel;
	panelfam = new wxPanel(this);
	panelfam->Show(true);
	panelfam->SetBackgroundColour(wxColour(80, 80, 80));
	n = 0.0;
	wxPanel* bar = new wxPanel(panelfam, wxID_ANY);
	bar->SetBackgroundColour(wxColour(60, 60, 60));
	wxPanel* owna = new wxPanel(panelfam, wxID_ANY);
	wxPanel* rule = new wxPanel(panelfam, wxID_ANY);
	wxPanel* rulema = new wxPanel(panelfam, wxID_ANY);
	wxPanel* parant = new wxPanel(panelfam, wxID_ANY);
	wxPanel* parantma = new wxPanel(panelfam, wxID_ANY);
	wxPanel* chrip = new wxPanel(panelfam, wxID_ANY);
	wxPanel* chripma = new wxPanel(panelfam, wxID_ANY);
	wxPanel* child1 = new wxPanel(panelfam, wxID_ANY);
	wxPanel* childbefore = new wxPanel(panelfam, wxID_ANY);
	wxPanel* childafter = new wxPanel(panelfam, wxID_ANY);
	wxPanel* childinfrim = new wxPanel(panelfam, wxID_ANY);



	//---------------------------------

	wxStaticText* text = new wxStaticText(bar, wxID_ANY, wxString::FromUTF8("รายการลดหย่อนภาษี : ครอบครัว"));
	text->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(bar, wxID_ANY, " << ");
	back->SetBackgroundColour(wxColour(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);
	wxButton* next = new wxButton(bar, wxID_ANY, " >> ");
	next->SetBackgroundColour(wxColour(60, 60, 60));
	next->SetForegroundColour(*wxWHITE);

	wxStaticText* own = new wxStaticText(owna, wxID_ANY, wxString::FromUTF8("ลดหย่อนส่วนบุคคน  : "));
	own->SetForegroundColour(*wxWHITE);
	ownan = new wxTextCtrl(owna, wxID_ANY, wxString::FromUTF8("60000"));
	ownan->SetEditable(false);
	ownan->SetBackgroundColour(wxColour(200, 200, 200));

	wxStaticText* status = new wxStaticText(panelfam, wxID_ANY, wxString::FromUTF8("สถานะสมรส"));
	status->SetForegroundColour(*wxWHITE);

	wxCheckBox* chparule1 = new wxCheckBox(rule, wxID_ANY, wxString::FromUTF8("บุพการีมีอายุ 60 ปีบริบูรณ์ขึ้นไป ในปีภาษีนี้"));
	chparule1->SetForegroundColour(*wxWHITE);
	wxCheckBox* chparule2 = new wxCheckBox(rule, wxID_ANY, wxString::FromUTF8("บุพการีมีเงินได้พึงประเมินไม่เกิน 30,000 บาท ต่อปี"));
	chparule2->SetForegroundColour(*wxWHITE);

	wxCheckBox* chpamarule1 = new wxCheckBox(rulema, wxID_ANY, wxString::FromUTF8("บุพการีคู่สมรสมีอายุ 60 ปีบริบูรณ์ขึ้นไป ในปีภาษีนี้"));
	chpamarule1->SetForegroundColour(*wxWHITE);
	wxCheckBox* chpamarule2 = new wxCheckBox(rulema, wxID_ANY, wxString::FromUTF8("บุพการีคู่สมรสมีเงินได้พึงประเมินไม่เกิน 30,000 บาท ต่อปี"));
	chpamarule2->SetForegroundColour(*wxWHITE);

	wxStaticText* pa = new wxStaticText(parant, wxID_ANY, wxString::FromUTF8("ลดหย่อนบิดา-มารดา(ตนเอง)  : "));
	pa->SetForegroundColour(*wxWHITE);
	cbpa1 = new wxCheckBox(parant, wxID_ANY, wxString::FromUTF8("บิดา"));
	cbpa1->SetForegroundColour(*wxWHITE);
	cbpa2 = new wxCheckBox(parant, wxID_ANY, wxString::FromUTF8("มารดา"));
	cbpa2->SetForegroundColour(*wxWHITE);

	wxStaticText* pama = new wxStaticText(parantma, wxID_ANY, wxString::FromUTF8("ลดหย่อนบิดา-มารดา(คู่สมรส)  : "));
	pama->SetForegroundColour(*wxWHITE);
	cbpama1 = new wxCheckBox(parantma, wxID_ANY, wxString::FromUTF8("บิดา"));
	cbpama1->SetForegroundColour(*wxWHITE);
	cbpama2 = new wxCheckBox(parantma, wxID_ANY, wxString::FromUTF8("มารดา"));
	cbpama2->SetForegroundColour(*wxWHITE);

	wxStaticText* chri = new wxStaticText(chrip, wxID_ANY, wxString::FromUTF8("ลดหย่อนผู้พิการหรือทุพพลภาพ(ไม่มีเงินได้)  : "));
	chri->SetForegroundColour(*wxWHITE);
	cbchri1 = new wxCheckBox(chrip, wxID_ANY, wxString::FromUTF8("บิดา"));
	cbchri1->SetForegroundColour(*wxWHITE);
	cbchri2 = new wxCheckBox(chrip, wxID_ANY, wxString::FromUTF8("มารดา"));
	cbchri2->SetForegroundColour(*wxWHITE);
	wxCheckBox* cbchri3 = new wxCheckBox(chrip, wxID_ANY, wxString::FromUTF8("บุตร"));
	cbchri3->SetForegroundColour(*wxWHITE);
	cbchri4 = new wxCheckBox(chrip, wxID_ANY, wxString::FromUTF8("ญาติ (เช่น พี่,น้อง ฯลฯ)"));
	cbchri4->SetForegroundColour(*wxWHITE);
	cbchri3->Hide();

	wxStaticText* chrima = new wxStaticText(chripma, wxID_ANY, wxString::FromUTF8("ลดหย่อนผู้พิการหรือทุพพลภาพ (คู่สมรสไม่มีเงินได้)  : "));
	chrima->SetForegroundColour(*wxWHITE);
	cbchrima1 = new wxCheckBox(chripma, wxID_ANY, wxString::FromUTF8("คู่สมรส"));
	cbchrima1->SetForegroundColour(*wxWHITE);
	cbchrima2 = new wxCheckBox(chripma, wxID_ANY, wxString::FromUTF8("บิดา"));
	cbchrima2->SetForegroundColour(*wxWHITE);
	cbchrima3 = new wxCheckBox(chripma, wxID_ANY, wxString::FromUTF8("มารดา"));
	cbchrima3->SetForegroundColour(*wxWHITE);
	

	wxArrayString choices;
	choices.Add(wxString::FromUTF8("โสด"));
	choices.Add(wxString::FromUTF8("หย่า"));
	choices.Add(wxString::FromUTF8("คู่สมรสมีเงินได้(แยกยื่น)"));
	choices.Add(wxString::FromUTF8("คู่สมรสไม่มีเงินได้"));
	myChoice = new wxListBox(panelfam, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	myChoice->SetBackgroundColour(wxColour(200, 200, 200));

	wxStaticText* child = new wxStaticText(child1, wxID_ANY, wxString::FromUTF8("บุตรคนที่ 1 (เกิดปีใดก็ตาม)   :"));
	child->SetForegroundColour(*wxWHITE);
	child->Hide();
	cbchildT = new wxCheckBox(child1, wxID_ANY, wxString::FromUTF8("มี"));
	cbchildT->SetForegroundColour(*wxWHITE);
	cbchildT->Hide();
	wxCheckBox* cbchildF = new wxCheckBox(child1, wxID_ANY, wxString::FromUTF8("ไม่มี"));
	cbchildF->SetForegroundColour(*wxWHITE);
	cbchildF->Hide();

	wxStaticText* child2 = new wxStaticText(panelfam, wxID_ANY, wxString::FromUTF8("บุตรคนที่ 2 เป็นต้นไป"));
	child2->SetForegroundColour(*wxWHITE);
	wxStaticText* chbf2561 = new wxStaticText(childbefore, wxID_ANY, wxString::FromUTF8("จำนวนบุตรที่เกิดก่อนปี 2561  : "));
	chbf2561->SetForegroundColour(*wxWHITE);
	ch2561bf = new wxTextCtrl(childbefore, wxID_ANY, wxString::FromUTF8(""));
	ch2561bf->SetBackgroundColour(wxColour(200, 200, 200));
	wxStaticText* chaf2561 = new wxStaticText(childafter, wxID_ANY, wxString::FromUTF8("จำนวนบุตรที่เกิดตั้งแต่ปี 2561 เป็นต้นไป  : "));
	chaf2561->SetForegroundColour(*wxWHITE);
	ch2561af = new wxTextCtrl(childafter, wxID_ANY, wxString::FromUTF8(""));
	ch2561af->SetBackgroundColour(wxColour(200, 200, 200));

	wxStaticText* chinfrim = new wxStaticText(childinfrim, wxID_ANY, wxString::FromUTF8("จำนวนบุตรที่ต้องการใช้สิทธิ์ลดหย่อนผู้พิการ  : "));
	chinfrim->SetForegroundColour(*wxWHITE);
	childhowinfrim = new wxTextCtrl(childinfrim, wxID_ANY, wxString::FromUTF8(""));
	childhowinfrim->SetBackgroundColour(wxColour(200, 200, 200));




	//------------------------------

	wxBoxSizer* FirstROW = new wxBoxSizer(wxHORIZONTAL);
	FirstROW->Add(text, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->AddStretchSpacer();
	FirstROW->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	FirstROW->Add(next, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	bar->SetSizer(FirstROW);

	wxBoxSizer* secROW = new wxBoxSizer(wxHORIZONTAL);
	secROW->Add(own, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	secROW->Add(ownan, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	owna->SetSizer(secROW);

	wxBoxSizer* threeROW = new wxBoxSizer(wxHORIZONTAL);
	threeROW->Add(chparule1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	threeROW->Add(chparule2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	rule->SetSizer(threeROW);

	wxBoxSizer* threedotoneROW = new wxBoxSizer(wxHORIZONTAL);
	threedotoneROW->Add(chpamarule1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	threedotoneROW->Add(chpamarule2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	rulema->SetSizer(threedotoneROW);

	wxBoxSizer* fourROW = new wxBoxSizer(wxHORIZONTAL);
	fourROW->Add(pa, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fourROW->Add(cbpa1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fourROW->Add(cbpa2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	parant->SetSizer(fourROW);
	parant->Show(false);

	wxBoxSizer* fourdotoneROW = new wxBoxSizer(wxHORIZONTAL);
	fourdotoneROW->Add(pama, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fourdotoneROW->Add(cbpama1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fourdotoneROW->Add(cbpama2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	parantma->SetSizer(fourdotoneROW);
	parantma->Show(false);

	wxBoxSizer* fiveROW = new wxBoxSizer(wxHORIZONTAL);
	fiveROW->Add(chri, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fiveROW->Add(cbchri1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fiveROW->Add(cbchri2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fiveROW->Add(cbchri3, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	fiveROW->Add(cbchri4, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	chrip->SetSizer(fiveROW);

	wxBoxSizer* sixROW = new wxBoxSizer(wxHORIZONTAL);
	sixROW->Add(child, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	sixROW->Add(cbchildT, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	sixROW->Add(cbchildF, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	child1->SetSizer(sixROW);

	wxBoxSizer* sevenROW = new wxBoxSizer(wxHORIZONTAL);
	sevenROW->Add(chbf2561, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	sevenROW->Add(ch2561bf, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	childbefore->SetSizer(sevenROW);

	wxBoxSizer* eightROW = new wxBoxSizer(wxHORIZONTAL);
	eightROW->Add(chaf2561, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	eightROW->Add(ch2561af, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	childafter->SetSizer(eightROW);

	wxBoxSizer* nineROW = new wxBoxSizer(wxHORIZONTAL);
	nineROW->Add(chinfrim, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	nineROW->Add(childhowinfrim, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	childinfrim->SetSizer(nineROW);

	wxBoxSizer* tenROW = new wxBoxSizer(wxHORIZONTAL);
	tenROW->Add(chrima, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	tenROW->Add(cbchrima1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	tenROW->Add(cbchrima2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	tenROW->Add(cbchrima3, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	chripma->SetSizer(tenROW);

	//---------------------------------

	wxBoxSizer* mainSize = new wxBoxSizer(wxVERTICAL);
	mainSize->Add(bar, 0, wxEXPAND);
	mainSize->Add(owna, 0, wxEXPAND);
	mainSize->Add(rule, 0, wxEXPAND);
	mainSize->Add(parant, 0, wxEXPAND);
	mainSize->Add(status, 0, wxALL | wxALIGN_LEFT, 10);
	mainSize->Add(myChoice, 0, wxALL | wxEXPAND, 10);
	mainSize->Add(rulema, 0, wxEXPAND);
	rulema->Show(false);
	mainSize->Add(parantma, 0, wxEXPAND);
	parantma->Show(false);
	mainSize->Add(child1, 0, wxEXPAND);
	child1->Show(false);

	mainSize->Add(child2, 0, wxALL | wxALIGN_LEFT, 10);
	child2->Hide();
	mainSize->Add(childbefore, 0, wxEXPAND);
	childbefore->Hide();
	mainSize->Add(childafter, 0, wxEXPAND);
	childafter->Hide();
	mainSize->Add(chrip, 0, wxEXPAND);
	mainSize->Add(childinfrim, 0, wxEXPAND);
	childinfrim->Hide();
	mainSize->Add(chripma, 0, wxEXPAND);
	chripma->Hide();
	panelfam->SetSizer(mainSize);

	//-------------------------------------------------

	auto updateVisibility = [=](wxCommandEvent& event) {
		bool isConditionMet = chparule1->GetValue() && chparule2->GetValue();
		parant->Show(isConditionMet);
		this->Layout(); 
	};
	chparule1->Bind(wxEVT_CHECKBOX, updateVisibility);
	chparule2->Bind(wxEVT_CHECKBOX, updateVisibility);

	auto updateParantVisibility = [=](wxCommandEvent& event) {
		bool isConditionMet = chpamarule1->GetValue() && chpamarule2->GetValue();
		parantma->Show(isConditionMet);
		this->Layout();
	};
	chpamarule1->Bind(wxEVT_CHECKBOX, updateParantVisibility);
	chpamarule2->Bind(wxEVT_CHECKBOX, updateParantVisibility);

	//-------------------------------------------------------
	auto toggleChildDetails = [=](bool show) {
		child2->Show(show);
		childbefore->Show(show);
		childafter->Show(show);
		cbchri3->Show(show);
		panelfam->Layout();
		};


	cbchildT->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event){
		if (event.IsChecked()) {
			cbchildF->SetValue(false);
			toggleChildDetails(true);
		}
		else {
			toggleChildDetails(false);
		}
		});

	cbchildF->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
		if (event.IsChecked()) {
			cbchildT->SetValue(false);
			toggleChildDetails(false);
		}
		});

	myChoice->Bind(wxEVT_LISTBOX, [=](wxCommandEvent& event) {
		wxString selected = event.GetString();
		child1->Show(false);        // ส่วนบุตรคนที่ 1
		child->Show(false);
		cbchildT->Show(false);
		cbchildF->Show(false);

		child2->Hide();             // หัวข้อบุตรคนที่ 2 เป็นต้นไป
		childbefore->Hide();        // จำนวนบุตรก่อน 2561
		childafter->Hide();         // จำนวนบุตรหลัง 2561

		rulema->Show(false);        // กฎเกณฑ์พ่อแม่คู่สมรส
		parantma->Show(false);      // ตัวเลือกพ่อแม่คู่สมรส
		chripma->Hide();

		childinfrim->Show(false);   // ช่องกรอกจำนวนบุตรพิการ
		cbchri3->Show(false);       // Checkbox "บุตร" ในหมวดผู้พิการ

		if (selected == wxString::FromUTF8("หย่า")) {
			child1->Show(true);
			child->Show(true);
			cbchildT->Show(true);
			cbchildF->Show(true);
		}
		else if (selected == wxString::FromUTF8("คู่สมรสมีเงินได้(แยกยื่น)") ||
			selected == wxString::FromUTF8("คู่สมรสไม่มีเงินได้")) {
			child1->Show(true);
			child->Show(true);
			cbchildT->Show(true);
			cbchildF->Show(true);
			rulema->Show(true);
			chripma->Show(true);
		}
		else if (selected == wxString::FromUTF8("โสด")) {
			cbchildT->SetValue(false);
			cbchildF->SetValue(false);
			cbchri3->SetValue(false);
		}
		panelfam->Layout(); 
		});
	cbchri3->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {/*เมื่อกดบุตรแล้วจำนวนบุตรที่ต้องการลดหย่อนพิการจะโผล่มา*/
		if (event.IsChecked()) {
			childinfrim->Show(true);
		}
		else {
			childinfrim->Show(false);
			childhowinfrim->Clear();
		}
		panelfam->Layout();
		});

	cbpa1->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbpa2->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbpama1->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbpama2->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchri1->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchri2->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchri4->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchildT->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchrima1->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchrima2->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });
	cbchrima3->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent&) { UpdateN(); });

	myChoice->Bind(wxEVT_LISTBOX, [=](wxCommandEvent&) { UpdateN(); });


	ch2561bf->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	ch2561af->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });
	childhowinfrim->Bind(wxEVT_TEXT, [=](wxCommandEvent&) { UpdateN(); });

	//----------------------------------------------

	panelfund = new TaxFund(this, panelfam);
	panelfund->Show(false);

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Show(false);
		mainpanel->Show(true);
		mainpanel->GetParent()->Layout();
		this->Layout();
		});

	next->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->UpdateN();
		panelfam->Show(false);
		panelfund->Show(true);
		this->Layout();

		});
	//-----------------------------------------

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(panelfam, 1, wxEXPAND);
	frameSizer->Add(panelfund, 1, wxEXPAND);

	this->SetSizer(frameSizer);
	this->Layout();	

	//----------------------------------------------


}