#pragma once
#include <wx/wx.h>
#include "Account.h"
#include "AccountBox.h"
class MyKeepPanel: public wxPanel
{
public:
	std::vector<Account>* accounts;
	std::vector<AccountBox*>* boxes;
	void RefreshAccounts();
	void OnPaint(wxPaintEvent& event);
	void OnConfirm(wxCommandEvent& event);
	void SaveKeep();
	void LoadKeep();
	MyKeepPanel(wxWindow* parent, wxPanel* main_panel, std::vector<Account>* accs, std::vector<AccountBox*>* bxs);

private:
	wxButton* reset;
	wxStaticText* goalText;
	wxStaticText* accText;
	wxStaticText* result;
	double goalAmount = 0;
	double currentSaved = 0;
	wxPanel* bottlepanel;
	wxStaticText* money;
	double percent = 0;
	wxPanel * mainpanel;
	wxStaticText* ask;
	wxTextCtrl* goal;
	wxStaticText* ask2;
	wxButton* save;
	wxStaticText* from;
	wxChoice* acc;
	wxButton* ok;
};

