#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

void MainFrame::Refreshinfo() {

	inandexPanel->Summary_panel->Calintotal();
	inandexPanel->Summary_panel->Calextotal();

	ttin = inandexPanel->Summary_panel->totalinyear;
	ttex = inandexPanel->Summary_panel->totalexyear;
	balance = inandexPanel->Summary_panel->Calbalance();
	net = balance + ttin - ttex;

	incomeText->SetLabel(wxString::Format(L"+ ฿ %.2f", ttin));
	expenseText->SetLabel(wxString::Format(L"- ฿ %.2f", ttex));
	netText->SetLabel(wxString::Format(L"฿ %.2f", net));

	chart->income = ttin;
	chart->expense = ttex;
	chart->net = net;
	chart->deduction = 0;
	chart->tax = 8900;

	chart->Refresh();
}

void MainFrame::OnClose(wxCloseEvent& event) {

	int ans = wxMessageBox("GOOD ORGANIZE TODAY!!", "Exit", wxYES_NO | wxCANCEL);
	if (ans == wxYES) {
		inandexPanel->SaveAccounts();
		inandexPanel->Wish_panel->SaveWish();
		inandexPanel->SaveCate();
	}
	else return;

	event.Skip();
}

MainFrame::MainFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 750))
{
	//ตั้งค่าธีมมืดพื้นหลัง
	this->SetBackgroundColour(wxColour(30, 30, 30));
	mainPanel = new wxPanel(this);
	mainPanel->Show();
	mainPanel->SetBackgroundColour(wxColour(30, 30, 30));

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	//หน้าอื่นๆ
	inandexPanel = new InandEx(this, mainPanel);
	inandexPanel->Hide();

	investPanel = new Invest(this, mainPanel);
	investPanel->Hide();

	//หัวข้อแอป
	wxStaticText* header = new wxStaticText(mainPanel, wxID_ANY, "Rainy Day");
	header->SetForegroundColour(*wxWHITE);
	header->SetFont(wxFont(26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	mainSizer->Add(header, 0, wxALL, 20);

	// ปุ่มเมนูหลัก 3 ปุ่มสีดำ
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	auto setupBtn = [&](const wxString& label) {
		wxButton* b = new wxButton(mainPanel, wxID_ANY, label, wxDefaultPosition, wxSize(180, 40));
		b->SetBackgroundColour(wxColour(0, 0, 0));
		b->SetForegroundColour(*wxWHITE);
		return b;
		};

	wxButton* inandexBtn = setupBtn(L"รายรับ-รายจ่าย");
	wxButton* taxBtn = setupBtn(L"คำนวณภาษี");
	wxButton* InvestBtn = setupBtn(L"คำแนะนำลงทุน");

	btnSizer->Add(inandexBtn, 0, wxRIGHT, 10);
	btnSizer->Add(taxBtn, 0, wxRIGHT, 10);
	btnSizer->Add(InvestBtn, 0, wxRIGHT, 10);
	mainSizer->Add(btnSizer, 0, wxLEFT, 20);



	//ส่วนกลาง สรุปเงิน (ซ้าย) และ กราฟ (ขวา)
	wxBoxSizer* midSizer = new wxBoxSizer(wxHORIZONTAL);

	// ฝั่งซ้าย สรุปตัวเลข
	wxStaticBoxSizer* leftBox = new wxStaticBoxSizer(wxVERTICAL, mainPanel, L" สรุปการเงินและลดหย่อน (Financial & Deduction Summary) ");
	leftBox->GetStaticBox()->SetForegroundColour(*wxWHITE);
	leftBox->SetMinSize(wxSize(450, -1));


	wxBoxSizer* row1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lbl1 = new wxStaticText(mainPanel, wxID_ANY, L"รายรับรวม:");
	incomeText = new wxStaticText(mainPanel, wxID_ANY, L"+ ฿ 0");
	incomeText->SetForegroundColour(wxColour(100, 255, 100));
	incomeText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	lbl1->SetForegroundColour(wxColour(100, 255, 100));
	lbl1->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	row1->Add(lbl1, 0, wxALL, 5);
	row1->Add(incomeText, 0, wxALL, 5);
	leftBox->Add(row1, 0, wxEXPAND);

	wxBoxSizer* row2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lbl2 = new wxStaticText(mainPanel, wxID_ANY, L"รายจ่ายรวม:");
	expenseText = new wxStaticText(mainPanel, wxID_ANY, L"+ ฿ 0");
	expenseText->SetForegroundColour(wxColour(225, 100, 100));
	expenseText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	lbl2->SetForegroundColour(wxColour(255, 100, 100));
	lbl2->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	row2->Add(lbl2, 0, wxALL, 5);
	row2->Add(expenseText, 0, wxALL, 5);
	leftBox->Add(row2, 0, wxEXPAND);

	wxBoxSizer* row3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lbl3 = new wxStaticText(mainPanel, wxID_ANY, L"เงินคงเหลือ:");
	netText = new wxStaticText(mainPanel, wxID_ANY, L"+ ฿ 0");
	netText->SetForegroundColour(wxColour(*wxWHITE));
	netText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	lbl3->SetForegroundColour(wxColour(*wxWHITE));
	lbl3->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	row3->Add(lbl3, 0, wxALL, 5);
	row3->Add(netText, 0, wxALL, 5);
	leftBox->Add(row3, 0, wxEXPAND);

	wxBoxSizer* row4 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* lbl4 = new wxStaticText(mainPanel, wxID_ANY, L"รวมรายการลดหย่อนภาษี:");
	taxText = new wxStaticText(mainPanel, wxID_ANY, L"+ ฿ 0");
	taxText->SetForegroundColour(wxColour(100, 200, 255));
	taxText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	lbl4->SetForegroundColour(wxColour(100, 200, 255));
	lbl4->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	row4->Add(lbl4, 0, wxALL, 5);
	row4->Add(taxText, 0, wxALL, 5);
	leftBox->Add(row4, 0, wxEXPAND);

	midSizer->Add(leftBox, 1, wxEXPAND | wxALL, 10);

	// ฝั่งขวา กราฟวงกลมและช่องภาษี
	wxBoxSizer* rightBox = new wxBoxSizer(wxVERTICAL);

	// ช่องภาษีสีส้ม (ด้านล่างกราฟ)
	wxPanel* taxPanel = new wxPanel(mainPanel);
	taxPanel->SetBackgroundColour(wxColour(40, 40, 40));
	wxBoxSizer* tSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* tTitle = new wxStaticText(taxPanel, wxID_ANY, L"ยอดภาษีที่ต้องจ่ายรวมรายปี");
	tTitle->SetForegroundColour(wxColour(255, 165, 0));
	wxStaticText* tVal = new wxStaticText(taxPanel, wxID_ANY, L"- ฿ 8,900.00");
	tVal->SetForegroundColour(wxColour(255, 165, 0));
	tVal->SetFont(wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	tSizer->Add(tTitle, 0, wxALIGN_CENTER | wxTOP, 10);
	tSizer->Add(tVal, 0, wxALIGN_CENTER | wxBOTTOM, 10);
	taxPanel->SetSizer(tSizer);

	rightBox->AddStretchSpacer();
	rightBox->Add(taxPanel, 0, wxEXPAND | wxTOP, 20); // ขยับลงมาให้พอดี
	midSizer->Add(rightBox, 1, wxEXPAND | wxALL, 30);

	mainSizer->Add(midSizer, 0, wxEXPAND);

	//แผนภูมิ
	chart = new BarChartPanel(mainPanel);
	chart->SetMinSize(wxSize(700, 350));

	mainSizer->Add(chart, 1, wxEXPAND | wxALL, 10);;
	mainPanel->SetSizer(mainSizer);

	// เชื่อมหน้าอื่นเมื่อกดปุ่ม

	inandexBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		mainPanel->Hide();
		investPanel->Hide();
		inandexPanel->Show();
		Layout();
		});
	
	InvestBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		mainPanel->Hide();
		inandexPanel->Hide();
		investPanel->Show();
		Layout();
		});

	// จัดหน้า
	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(mainPanel, 1, wxEXPAND);
	frameSizer->Add(inandexPanel, 1, wxEXPAND);
	frameSizer->Add(investPanel, 1, wxEXPAND);
	this->SetSizer(frameSizer);

	Refreshinfo();

	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}