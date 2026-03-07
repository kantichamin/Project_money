#include "MySummaryPanel.h"

using namespace std;



void MySummaryPanel::Calextotal() {
	monthlyextotal.clear();
	ttex = 0;
	ifstream file("ExpenseList.txt");
	string line,currentmonth,cate;
	MandCate excate;
	while (getline(file, line)) {
		if (line.find("/") != string::npos) currentmonth = line.substr(3, 5);
		else {
			int pos = line.find("-");
			int pos1 = line.find("-", pos + 1);
			
			if (pos != string::npos && pos1 != string::npos) {
				cate = line.substr(pos1 + 1);
				cate.erase(0, cate.find_first_not_of(" "));
				double value = wxAtof(line.substr(0, pos));
				excate.monthlycatett[cate] += value;
				monthlyextotal[currentmonth] = excate;
				ttex += wxAtof(line.substr(0, pos));
			}
			
		}
	}
	file.close();

	totalexyear = 0;

	for (auto& month : monthlyextotal) {

		if (month.first.find(year.ToStdString()) != string::npos) {

			for (auto& cate : month.second.monthlycatett) totalexyear += cate.second;

		}
	}
}

void MySummaryPanel::Calintotal() {
	monthlyintotal.clear();
	ifstream file("IncomeList.txt");
	string line, currentmonth;
	double in;
	while (getline(file, line)) {
		if (line.find("/") != string::npos) currentmonth = line.substr(3, 5);
		else {
			int pos = line.find("-");
			if (pos != string::npos) {
				in = wxAtof(line.substr(0, pos));
				monthlyintotal[currentmonth] += in;
			}
		}
	}
	file.close();

	totalinyear = 0;

	for (auto& month : monthlyintotal) {

		if (month.first.find(year.ToStdString()) != string::npos) {

			totalinyear += month.second;
			
		}
	}
}

void MySummaryPanel::OnPaintper(wxPaintEvent& event) {
	Calintotal();
	Calextotal();
	wxPaintDC dc(percent);
	double income = monthlyintotal[monthnum.ToStdString()];
	auto it = monthlyextotal.find(monthnum.ToStdString());
	if (it == monthlyextotal.end()) return;

	double expense = 0;
	for (auto& pair : it->second.monthlycatett)
		expense += pair.second;

	if (income <= 0) return;
	double per = (expense / income) * 100.00;
	int width = 200;
	int height = 20;
	int x = 40;
	int y = 20;
	int fill = width * per / 100;
	dc.DrawRectangle(x, y, width, height);
	dc.SetBrush(*wxGREY_BRUSH);
	dc.DrawRectangle(x, y, fill, height);
	dc.SetTextForeground(*wxWHITE);
	dc.DrawText(wxString::Format(L"รายจ่ายคิดเป็น %.0f%% ของรายได้", per), x + width + 20, 20);


}

void MySummaryPanel::OnPaintcir(wxPaintEvent& event) {
	Calextotal();
	wxPaintDC dc(chart);
	int centerX = 200;
	int centerY = 150;
	int radius = 100;
	double startAngle = 0;
	int x = 50;
	string m = monthnum.ToStdString();

	auto it = monthlyextotal.find(m);
	if (it == monthlyextotal.end())
		return;

	if (ttex <= 0)
		return;

	int i = 100, j = 100, k = 100;

	int legendX = 20;
	int legendY = 20;
	int boxSize = 15;

	for (auto& pair : it->second.monthlycatett)
	{
		double value = pair.second;
		double angle = (value / ttex) * 360.0;

		wxColour sliceColor(i, j, k);

		
		dc.SetBrush(wxBrush(sliceColor));
		dc.SetPen(*wxTRANSPARENT_PEN);

		dc.DrawEllipticArc(centerX - radius,
			centerY - radius,
			radius * 2,
			radius * 2,
			startAngle,
			startAngle + angle);

		startAngle += angle;

		
		dc.SetBrush(wxBrush(sliceColor));
		dc.DrawRectangle(legendX, legendY, boxSize, boxSize);

		dc.SetTextForeground(*wxWHITE);
		dc.DrawText(pair.first, legendX + boxSize + 10, legendY - 2);

		legendY += 25;   

		i += 20;
		j += 20;
		k += 20;
	}
	
}

MySummaryPanel::MySummaryPanel(wxWindow* parent, wxPanel* main_panel)
	:wxPanel(parent, wxID_ANY)
{
	locale.Init(wxLANGUAGE_THAI);
	Calintotal();
	Calextotal();
	mainpanel = main_panel;
	wxPanel* topbarsummary = new wxPanel(this);
	topbarsummary->SetBackgroundColour(wxColor(60, 60, 60));
	wxStaticText* titletext = new wxStaticText(topbarsummary, wxID_ANY, "Summary");
	titletext->SetForegroundColour(*wxWHITE);
	wxButton* back = new wxButton(topbarsummary, wxID_ANY, "<<", wxDefaultPosition, wxSize(30, 20));
	back->SetBackgroundColour(wxColor(60, 60, 60));
	back->SetForegroundColour(*wxWHITE);

	month = now.Format("%B");
	wxStaticText* mon = new wxStaticText(this, wxID_ANY, month);
	wxFont font(20,                 
		wxFONTFAMILY_DEFAULT,
		wxFONTSTYLE_NORMAL,
		wxFONTWEIGHT_BOLD);
	mon->SetFont(font);
	mon->SetForegroundColour(*wxWHITE);
	double intt= monthlyintotal[monthnum.ToStdString()];
	wxString intexttt = wxString::Format("%.2f", intt);
	ttincome = new wxStaticText(this, wxID_ANY, L"รายได้ทั้งหมด : "+intexttt+L" บาท");
	ttincome->SetForegroundColour(*wxWHITE);
	double extt = ttex;
	wxString extexttt = wxString::Format("%.2f", extt);
	ttexpense = new wxStaticText(this, wxID_ANY, L"รายจ่ายทั้งหมด: "+extexttt+L" บาท");
	ttexpense->SetForegroundColour(*wxWHITE);
	double ttm = intt - extt;
	wxString ttmtext = wxString::Format("%.2f", ttm);
	tt = new wxStaticText(this, wxID_ANY, L"เงินคงเหลือสุทธิ: " + ttmtext);
	tt->SetForegroundColour(*wxWHITE);
	percent = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 50));
	percent->SetBackgroundColour(wxColor(80, 80, 80));
	percent->Bind(wxEVT_PAINT, &MySummaryPanel::OnPaintper, this);
	chart = new wxPanel(this, wxID_ANY);
	chart->SetBackgroundColour(wxColor(80, 80, 80));
	chart->Bind(wxEVT_PAINT, &MySummaryPanel::OnPaintcir, this);
	

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(titletext, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	topSizer->AddStretchSpacer();
	topSizer->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
	topbarsummary->SetSizer(topSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(topbarsummary, 0, wxEXPAND);
	mainSizer->Add(mon, 0, wxALL, 20);
	mainSizer->Add(ttincome, 0, wxLEFT , 30);
	mainSizer->AddSpacer(5);
	mainSizer->Add(ttexpense, 0, wxLEFT, 30);
	mainSizer->AddSpacer(5);
	mainSizer->Add(tt, 0, wxLEFT, 30);
	mainSizer->AddSpacer(5);
	mainSizer->Add(percent, 0, wxLEFT, 30);
	wxBoxSizer* graph = new wxBoxSizer(wxHORIZONTAL);
	graph->Add(chart, 1, wxEXPAND);

	mainSizer->Add(graph, 1, wxEXPAND | wxLEFT, 30);
	this->SetSizer(mainSizer);
	this->Layout();

	

	back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		this->Hide();
		mainpanel->Show();
		mainpanel->GetParent()->Layout();
		});
}
void MySummaryPanel::RefreshSummary() {
	Calintotal();
	Calextotal();
	double intt = monthlyintotal[monthnum.ToStdString()];
	double extt = 0;

	auto it = monthlyextotal.find(monthnum.ToStdString());
	if (it != monthlyextotal.end()) {
		for (auto& pair : it->second.monthlycatett)
			extt += pair.second;
	}

	double net = intt - extt;

	ttincome->SetLabel(
		L"รายได้ทั้งหมด : " + wxString::Format("%.2f", intt) + L" บาท");

	ttexpense->SetLabel(
		L"รายจ่ายทั้งหมด: " + wxString::Format("%.2f", extt) + L" บาท");

	tt->SetLabel(
		L"เงินคงเหลือสุทธิ: " + wxString::Format("%.2f", net));
	percent->Refresh();
	chart->Refresh();
}