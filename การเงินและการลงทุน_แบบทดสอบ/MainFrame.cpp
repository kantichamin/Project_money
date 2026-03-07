#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/scrolwin.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	//------- Panel ใหญ่ หน้าแบบทดสอบ --------//
	main = new wxPanel(this);
	main->SetBackgroundColour(wxColor(60, 60, 60));
	main->Show();

	//------- tap ด้านบน -------//
	wxPanel* menutap = new wxPanel(main);
	menutap->SetBackgroundColour(wxColor(60, 60, 60));
	menutap->SetMinSize(wxSize(-1, 40));

	wxStaticText* menutext = new wxStaticText(menutap, wxID_ANY, wxT("การเงินและการลงทุน"));
	menutext->SetForegroundColour(wxColor(255, 255, 255));

	wxButton* buttontap1 = new wxButton(menutap, wxID_ANY, "<<");
	buttontap1->SetBackgroundColour(wxColor(60, 60, 60));
	buttontap1->SetForegroundColour(wxColor(255, 255, 255));

	wxButton* buttontap2 = new wxButton(menutap, wxID_ANY, ">>");
	buttontap2->SetBackgroundColour(wxColor(60, 60, 60));
	buttontap2->SetForegroundColour(wxColor(255, 255, 255));

	//------- กดปุ่ม << ของหน้าแสดงผล เพื่อแสดงแบบทดสอบ -------//
	buttontap1->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		choices1_->SetSelection(0);
		choices2_->SetSelection(0);
		choices3_->SetSelection(0);
		choices4_->SetSelection(0);
		choices5_->SetSelection(0);
		choices6_->SetSelection(0);
		choices7_->SetSelection(0);
		choices8_->SetSelection(0);
		choices9_->SetSelection(0);
		choices10_->SetSelection(0);

		// กลับหน้าแบบทดสอบ
		sent->Hide();
		mainScroll->Show();

		mainScroll->Scroll(0, 0); // เลื่อนกลับบนสุด

		main->Layout();
	});

	wxBoxSizer* menusize = new wxBoxSizer(wxHORIZONTAL);
		menusize->Add(menutext, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 20);
		menusize->AddStretchSpacer();
		menusize->Add(buttontap1, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
		menusize->Add(buttontap2, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

	menutap->SetSizer(menusize);


	//------- พท.ด้านล่าง -------//
	mainScroll = new wxScrolledWindow(main, wxID_ANY);
	mainScroll->SetScrollRate(0, 20);

		//------- หน้าใหม่ แสดงผล -------//
		sent = new Quiz(main,mainScroll);
		sent->Hide();

		//------- ส่วนของ หัว -------//
		wxPanel* smallpanel = new wxPanel(mainScroll);
		smallpanel->SetBackgroundColour(wxColor(80, 80, 80));
		smallpanel->SetMinSize(wxSize(-1, 300));

		wxStaticText* smalltext1 = new wxStaticText(smallpanel, wxID_ANY, L"แบบทดสอบความเสี่ยงการลงทุน");
		smalltext1->SetForegroundColour(wxColor(255, 255, 255));
		wxFont smallfont1(45,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);
		smalltext1->SetFont(smallfont1);

		wxStaticText* smalltext2 = new wxStaticText(smallpanel, wxID_ANY, L"--------------------------------------");
		smalltext2->SetForegroundColour(wxColor(255, 255, 255));
		wxFont smallpanelfont2(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
		smalltext2->SetFont(smallpanelfont2);

		wxStaticText* smalltext3 = new wxStaticText(smallpanel, wxID_ANY,
			L"ทุกคนอยากได้ผลตอบแทนสูง ความเสี่ยงต่ำ\n"
			L"แต่ความจริงคือผลตอบแทนกับความเสี่ยงมาคู่กัน ยิ่งหวังผลสูง ก็ต้องยอมรับความเสี่ยงมากขึ้น\n"
			L"แล้วคุณรับความเสี่ยงได้แค่ไหน? ลองทำแบบทดสอบเพื่อค้นหาระดับ\n"
			L"และแนวทางการลงทุนที่เหมาะกับคุณ",
			wxDefaultPosition,
			wxDefaultSize,
			wxALIGN_CENTER);
		smalltext3->SetForegroundColour(wxColor(255, 255, 255));
		wxFont smallfont3(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT);
		smalltext3->SetFont(smallfont3);

		wxBoxSizer* smallsize = new wxBoxSizer(wxVERTICAL);
			smallsize->Add(smalltext1, 0, wxALIGN_CENTER | wxTOP, 20);
			smallsize->Add(smalltext2, 0, wxALIGN_CENTER | wxTOP, 1);
			smallsize->Add(smalltext3, 0, wxALIGN_CENTER | wxTOP, 1);

		smallpanel->SetSizer(smallsize);


		//------- ส่วนของคำภาม -------//
		wxPanel* panel = new wxPanel(mainScroll);
		panel->SetBackgroundColour(wxColor(60, 60, 60));


		//------- หมวด 1 -------//
		//ข้อ 1
		wxStaticText* question1 = new wxStaticText(panel, wxID_ANY, L"1.ถ้าคิดถึงเงินลงทุนก้อนนี้ คุณรู้สึกว่า...");
		question1->SetForegroundColour(wxColor(255, 255, 255));
		wxFont questionfont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Segoe UI"); // ขนาด และรูปแบบตัวอักษร ของคำถาม
		question1->SetFont(questionfont);
		wxArrayString choices1;
		choices1.Add(L" A)  เก็บเงินในระยะยาว มากกว่า 5 ปี");
		choices1.Add(L" B)  เก็บไว้ซื้อของที่ต้องการ ไม่รีบ แต่ไม่อยากรอนาน 1 - 5 ปี");
		choices1.Add(L" C)  ต้องการใช้ใน 1 ปี");

		choices1_ = new wxRadioBox(panel, wxID_ANY,"", wxDefaultPosition, wxDefaultSize, choices1, 1);
		choices1_->SetForegroundColour(wxColor(255, 255, 255));
		wxFont choicesfont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Segoe UI"); // ขนาด และรูปแบบตัวอักษร ของตัวเลือก
		choices1_->SetFont(choicesfont);

		//ข้อ 2
		wxStaticText* question2 = new wxStaticText(panel, wxID_ANY, L"2.เป้าหมายหลักของการลงทุนคือ");
		question2->SetForegroundColour(wxColor(255, 255, 255));
		question2->SetFont(questionfont);

		wxArrayString choices2;
		choices2.Add(L" A)  เก็บรักษาเงิน");
		choices2.Add(L" B)  เพิ่มมูลค่าอย่างค่อยเป็นค่อยไป");
		choices2.Add(L" C)  สร้างโอกาสให้เงินเติบโตอย่างรวดเร็ว");

		choices2_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices2, 1);
		choices2_->SetForegroundColour(wxColor(255, 255, 255));
		choices2_->SetFont(choicesfont);

		//ข้อ 3
		wxStaticText* question3 = new wxStaticText(panel, wxID_ANY, L"3.คุณคิดว่าจะใช้เงินก้อนนี้เมื่อไร");
		question3->SetForegroundColour(wxColor(255, 255, 255));
		question3->SetFont(questionfont);

		wxArrayString choices3;
		choices3.Add(L" A)  มากกว่า 7 ปี");
		choices3.Add(L" B)  ประมาณ 3-7 ปี");
		choices3.Add(L" C)  ภายใน 1-3 ปี");

		choices3_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices3, 1);
		choices3_->SetForegroundColour(wxColor(255, 255, 255));
		choices3_->SetFont(choicesfont);

		//ข้อ 4
		wxStaticText* question4 = new wxStaticText(panel, wxID_ANY, L"4.ประสบการณ์การลงทุนของคุณ");
		question4->SetForegroundColour(wxColor(255, 255, 255));
		question4->SetFont(questionfont);

		wxArrayString choices4;
		choices4.Add(L" A)  ไม่เคยลงทุนมาก่อน");
		choices4.Add(L" B)  เคยลงทุนบ้าง");
		choices4.Add(L" C)  ลงทุนสม่ำเสมอ / เข้าใจสินทรัพย์");
	
		choices4_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices4, 1);
		choices4_->SetForegroundColour(wxColor(255, 255, 255));
		choices4_->SetFont(choicesfont);

		//ข้อ 5
		wxStaticText* question5 = new wxStaticText(panel, wxID_ANY, L"5.เมื่อเห็นข่าวตลาดผันผวนรุนแรง คุณมักจะ");
		question5->SetForegroundColour(wxColor(255, 255, 255));
		question5->SetFont(questionfont);
	
		wxArrayString choices5;
		choices5.Add(L" A)  เครียดและอยากหยุดลงทุน");
		choices5.Add(L" B)  กังวลแต่ยังควบคุมได้");
		choices5.Add(L" C)  มองเป็นเรื่องปกติ");
	
		choices5_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices5, 1);
		choices5_->SetForegroundColour(wxColor(255, 255, 255));
		choices5_->SetFont(choicesfont);

		//ข้อ 6
		wxStaticText* question6 = new wxStaticText(panel, wxID_ANY, L"6.คุณเคยขายสินทรัพย์เพราะความกลัวหรือไม่");
		question6->SetForegroundColour(wxColor(255, 255, 255));
		question6->SetFont(questionfont);
	
		wxArrayString choices6;
		choices6.Add(L" A)  เคย และรู้สึกเสียดายทีหลัง");
		choices6.Add(L" B)  เคยบ้าง แต่ไม่บ่อย");
		choices6.Add(L" C)  ไม่เคย");
	
		choices6_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices6, 1);
		choices6_->SetForegroundColour(wxColor(255, 255, 255));
		choices6_->SetFont(choicesfont);

		//ข้อ 7
		wxStaticText* question7 = new wxStaticText(panel, wxID_ANY, L"7.ถ้าการลงทุนยังไม่เห็นผลใน 1–2 ปี คุณจะ...");
		question7->SetForegroundColour(wxColor(255, 255, 255));
		question7->SetFont(questionfont);
	
		wxArrayString choices7;
		choices7.Add(L" A)  เลิกและถอนเงิน");
		choices7.Add(L" B)  ลังเล แต่ยังถือไว้");
		choices7.Add(L" C)  ถือยาวตามแผน");
	
		choices7_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices7, 1);
		choices7_->SetForegroundColour(wxColor(255, 255, 255));
		choices7_->SetFont(choicesfont);

		//ข้อ 8
		wxStaticText* question8 = new wxStaticText(panel, wxID_ANY, L"8.คุณมีเงินสำรองฉุกเฉินเพียงพอหรือไม่");
		question8->SetForegroundColour(wxColor(255, 255, 255));
		question8->SetFont(questionfont);
	
		wxArrayString choices8;
		choices8.Add(L" A)  น้อยกว่า 3 เดือน");
		choices8.Add(L" B)  3–6 เดือน");
		choices8.Add(L" C)  มากกว่า 6 เดือน");
	
		choices8_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices8, 1);
		choices8_->SetForegroundColour(wxColor(255, 255, 255));
		choices8_->SetFont(choicesfont);

		//ข้อ 9
		wxStaticText* question9 = new wxStaticText(panel, wxID_ANY, L"9.รายได้ของคุณมีความมั่นคงแค่ไหน");
		question9->SetForegroundColour(wxColor(255, 255, 255));
		question9->SetFont(questionfont);
	
		wxArrayString choices9;
		choices9.Add(L" A)  ไม่แน่นอน / เปลี่ยนบ่อย");
		choices9.Add(L" B)  ค่อนข้างมั่นคง");
		choices9.Add(L" C)  มั่นคงมาก");
	
		choices9_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices9, 1);
		choices9_->SetForegroundColour(wxColor(255, 255, 255));
		choices9_->SetFont(choicesfont);

		//ข้อ 10
		wxStaticText* question10 = new wxStaticText(panel, wxID_ANY, L"10.คุณสามารถลงทุนอย่างสม่ำเสมอได้หรือไม่");
		question10->SetForegroundColour(wxColor(255, 255, 255));
		question10->SetFont(questionfont);
	
		wxArrayString choices10;
		choices10.Add(L" A)  ไม่แน่ใจ / ขึ้นกับสถานการณ์");
		choices10.Add(L" B)  พอทำได้บางช่วง");
		choices10.Add(L" C)  ทำได้สม่ำเสมอ");
	
		choices10_ = new wxRadioBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, choices10, 1);
		choices10_->SetForegroundColour(wxColor(255, 255, 255));
		choices10_->SetFont(choicesfont);

		//------- ปุ่มส่ง -------//
		wxButton* send = new wxButton(panel, wxID_ANY, L"ส่งแบบทดสอบ", wxDefaultPosition, wxSize(200,50));
		send->SetBackgroundColour(wxColor(80, 80, 80));
		send->SetForegroundColour(wxColor(255, 255, 255));
		wxFont sendfont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Segoe UI");
		send->SetFont(sendfont);

		//------- กดปุ่มส่ง -------//
		send->Bind(wxEVT_BUTTON, [this](wxCommandEvent&){

			//------- คำนวนคะแนน -------//
			int q1 = choices1_->GetSelection() + 1;
			int q2 = choices2_->GetSelection() + 1;
			int q3 = choices3_->GetSelection() + 1;
			int q4 = choices4_->GetSelection() + 1;
			int q5 = choices5_->GetSelection() + 1;
			int q6 = choices6_->GetSelection() + 1;
			int q7 = choices7_->GetSelection() + 1;
			int q8 = choices8_->GetSelection() + 1;
			int q9 = choices9_->GetSelection() + 1;
			int q10 = choices10_->GetSelection() + 1;

			int r = q1 + q2 + q3 + q4;
			int m = q5 + q6 + q7;
			int re = q8 + q9 + q10;

			int risk = Risk(r);
			int mental = Mental(m);
			int ready = Readiness(re);

			sent->SetScore(risk, mental, ready);
			sent->SetScore2(risk, mental, ready);// ส่งคะแนนไปยังหน้าแสดงผล

			mainScroll->Hide(); // ซ่อนหน้านี้
			sent->Show(); // แสดงหน้าแสดงผล
			main->Layout();
			sent->Refresh();
			});



		wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
			panelSizer->Add(question1, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices1_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question2, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices2_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question3, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices3_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question4, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices4_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question5, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices5_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question6, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices6_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question7, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices7_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question8, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices8_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question9, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices9_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(question10, 0, wxLEFT | wxTOP, 30);
			panelSizer->Add(choices10_, 0, wxLEFT | wxRIGHT | wxEXPAND, 35);

			panelSizer->Add(send, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 50);
	
		panel->SetSizer(panelSizer);



		//------- จัดวาง layout -------//
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
			sizer->Add(smallpanel, 0, wxEXPAND);
			sizer->Add(panel, 1, wxEXPAND);

		mainScroll->SetSizer(sizer);  
		mainScroll->FitInside();


	//------- จัดวาง layout หลัก -------//
	wxBoxSizer* allsizer = new wxBoxSizer(wxVERTICAL);
		allsizer->Add(menutap, 0, wxEXPAND);
		allsizer->Add(mainScroll, 1, wxEXPAND);
		allsizer->Add(sent, 1, wxEXPAND);

	main->SetSizer(allsizer);
	sent->Hide();
	Layout();
}

//------- ฟังก์ชันคำนวน ระดับคะแนน -------//
int MainFrame::Risk(int r) {
	if (r >= 4 && r <= 6) return 1;
	else if (r >= 7 && r <= 9) return 2;
	else if (r >= 10 && r <= 12) return 3;
	return 0;
}

int MainFrame::Mental(int m) {
	if (m >= 3 && m <= 4) return 1;
	else if (m >= 5 && m <= 7) return 2;
	else if (m >= 8 && m <= 9) return 3;
	return 0;
}

int MainFrame::Readiness(int re) {
	if (re >= 3 && re <= 4) return 1;
	else if (re >= 5 && re <= 7) return 2;
	else if (re >= 8 && re <= 9) return 3;
	return 0;
}
