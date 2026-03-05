#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

MainFrame::MainFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800))
{
	//ตั้งค่าธีมมืดพื้นหลัง
	this->SetBackgroundColour(wxColour(30, 30, 30));
	wxPanel* mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(30, 30, 30));

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

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
	btnSizer->Add(setupBtn(L"รายรับ-รายจ่าย"), 0, wxRIGHT, 10);
	btnSizer->Add(setupBtn(L"คำนวณภาษี"), 0, wxRIGHT, 10);
	btnSizer->Add(setupBtn(L"คำแนะนำลงทุน"), 0, wxRIGHT, 10);
	mainSizer->Add(btnSizer, 0, wxLEFT, 20);

	//ส่วนกลาง สรุปเงิน (ซ้าย) และ กราฟ (ขวา)
	wxBoxSizer* midSizer = new wxBoxSizer(wxHORIZONTAL);

	// ฝั่งซ้าย สรุปตัวเลข
	wxStaticBoxSizer* leftBox = new wxStaticBoxSizer(wxVERTICAL, mainPanel, L" สรุปการเงินและลดหย่อน (Financial & Deduction Summary) ");
	leftBox->GetStaticBox()->SetForegroundColour(*wxWHITE);
	leftBox->SetMinSize(wxSize(650, -1));

	auto createInfoRow = [&](const wxString& label, const wxString& value, const wxColour& color) {
		wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText* lbl = new wxStaticText(mainPanel, wxID_ANY, label);
		lbl->SetForegroundColour(*wxWHITE);
		lbl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		wxStaticText* val = new wxStaticText(mainPanel, wxID_ANY, value);
		val->SetForegroundColour(color);
		val->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		row->Add(lbl, 0, wxALL, 5);
		row->Add(val, 0, wxALL, 5);
		return row;
		};

	leftBox->Add(createInfoRow(L"รายรับรวม:", L"+ ฿ 25,000.00", wxColour(100, 255, 100)), 0, wxEXPAND);
	leftBox->Add(createInfoRow(L"รายจ่ายรวม:", L"- ฿ 10,250.00", wxColour(255, 100, 100)), 0, wxEXPAND);
	leftBox->Add(createInfoRow(L"ยอดเงินคงเหลือ:", L"฿ 14,750.00", *wxWHITE), 0, wxEXPAND);
	leftBox->Add(createInfoRow(L"รวมรายการลดหย่อนภาษี:", L"+ ฿ 7,300.00", wxColour(100, 200, 255)), 0, wxEXPAND);

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

	// ตารางด้านล่าง
	wxStaticBoxSizer* tableBox = new wxStaticBoxSizer(wxVERTICAL, mainPanel, L" ตารางรายการล่าสุด (Recent Transactions) ");
	tableBox->GetStaticBox()->SetForegroundColour(*wxWHITE);

	m_listCtrl = new wxListCtrl(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(620, 350), wxLC_REPORT);
	m_listCtrl->SetBackgroundColour(wxColour(45, 45, 45));
	m_listCtrl->SetForegroundColour(*wxWHITE);

	m_listCtrl->InsertColumn(0, L"วันที่", wxLIST_FORMAT_LEFT, 100);
	m_listCtrl->InsertColumn(1, L"รายละเอียด", wxLIST_FORMAT_LEFT, 250);
	m_listCtrl->InsertColumn(2, L"ประเภท", wxLIST_FORMAT_LEFT, 130);
	m_listCtrl->InsertColumn(3, L"จำนวนเงิน", wxLIST_FORMAT_RIGHT, 140);

	// เติมข้อมูลตัวอย่าง
	long i = m_listCtrl->InsertItem(0, L"02/03/2026");
	m_listCtrl->SetItem(i, 1, L"เงินเดือน");
	m_listCtrl->SetItem(i, 2, L"รายรับ");
	m_listCtrl->SetItem(i, 3, L"+ 25,000.00");

	tableBox->Add(m_listCtrl, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(tableBox, 0, wxALIGN_LEFT | wxLEFT | wxALL, 20);

	mainPanel->SetSizer(mainSizer);
}