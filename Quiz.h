#pragma once
#include <wx/wx.h>
#include <string>
class Quiz : public wxPanel
{
	int RealRisk_1;
	int RealRisk_2;
	bool risk_2;
	wxPanel* mainpanel;
	wxPanel* panelall;
	wxPanel* risk2Panel;
	wxStaticText* smallpaneltext2;
	wxScrolledWindow* mainScroll;
	wxStaticText* risk_1text;
	wxStaticText* item1;
	wxStaticText* item2;
	wxStaticText* item3;
	wxStaticText* risk_1text2;
	wxStaticText* item1_;
	wxStaticText* item2_;
	wxStaticText* item3_;
	wxStaticText* Text1_;
public:
	Quiz(wxWindow* parent, wxPanel* main);
	int SetScore(int r, int m, int re);
	int SetScore2(int r, int m, int re);
	wxString conjunction();
	wxString Typepanel(int r);
	wxString investment(int r);
	wxString proportion(int r);
	wxString explanation(int r);
};

