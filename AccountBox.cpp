#include "AccountBox.h"
#include <wx/wx.h>
#include <string>

AccountBox::AccountBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, int i)
	: wxPanel(parent), accounts(accs), index(i) {
	wxStaticBoxSizer* box = new wxStaticBoxSizer(wxHORIZONTAL, this, (*accounts)[index].name);
	box->GetStaticBox()->SetForegroundColour(*wxWHITE);
	label = new wxStaticText(this, wxID_ANY, "Balance: 0");
	box->Add(label, 0, wxALL, 10);
	this->SetSizer(box);
	mainSizer->Add(this, 0, wxALL, 10);

}

void AccountBox::refresh() {
	double b = (*accounts)[index].balance;
	label->SetLabel(wxString::Format("Balance: %.2f",b ));
	label->SetForegroundColour(*wxWHITE);
}