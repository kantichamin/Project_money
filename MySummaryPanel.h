#pragma once
#include <wx/wx.h>
#include <string>
#include <fstream>
#include <map>
#include <cmath>

using namespace std;

struct MandCate {
	map<string, double> monthlycatett;
};

class MySummaryPanel : public wxPanel
{
public:
	map<string, double> monthlyintotal;
	map<string, MandCate> monthlyextotal;
	double totalexyear;
	double totalinyear;

	void RefreshSummary();
	void Calextotal();
	void Calintotal();
	void OnPaintper(wxPaintEvent& event);
	void OnPaintcir(wxPaintEvent& event);
	MySummaryPanel(wxWindow* parent, wxPanel* main_panel);

private:
	
	wxPanel* chart;
	wxLocale locale;
	wxDateTime now = wxDateTime::Now();
	wxString month;
	wxStaticText* ttexpense;
	wxStaticText* ttincome;
	wxStaticText* tt;
	wxPanel* mainpanel;
	wxPanel* percent;
	wxString monthnum = now.Format("%m/%y");
	wxString year = now.Format("%y");
	double ttex = 0;
};

