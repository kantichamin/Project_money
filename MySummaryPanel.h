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
	void RefreshSummary();
	void Calextotal();
	void Calintotal();
	void OnPaintper(wxPaintEvent& event);
	void OnPaintcir(wxPaintEvent& event);
	MySummaryPanel(wxWindow* parent, wxPanel* main_panel);

private:
	wxPanel* chart;
	map<string, double> monthlyintotal;
	map<string, MandCate> monthlyextotal;
	wxLocale locale;
	wxDateTime now = wxDateTime::Now();
	wxString month;
	wxStaticText* ttexpense;
	wxStaticText* ttincome;
	wxStaticText* tt;
	wxPanel* mainpanel;
	wxPanel* percent;
	wxString monthnum = now.Format("%m");
	double ttex = 0;
};

