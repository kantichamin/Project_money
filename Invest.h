#pragma once
#include <wx/wx.h>
#include <wx/scrolwin.h>
#include "Quiz.h"

class Invest : public wxPanel
{
	wxPanel* mainpanel;
	wxScrolledWindow* mainScroll;
	Quiz* sent;
	wxPanel* main;
	wxRadioBox* choices1_;
	wxRadioBox* choices2_;
	wxRadioBox* choices3_;
	wxRadioBox* choices4_;
	wxRadioBox* choices5_;
	wxRadioBox* choices6_;
	wxRadioBox* choices7_;
	wxRadioBox* choices8_;
	wxRadioBox* choices9_;
	wxRadioBox* choices10_;
public:
	Invest(wxWindow* parent, wxPanel* main_panel);
	int Risk(int);
	int Mental(int);
	int Readiness(int);
};