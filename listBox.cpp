#include "listBox.h"


using namespace std;
void listBox::OnConfirm(wxCommandEvent& event){
	if (isIncome) changein();
	else changeex();
	wxString text = ans->GetValue();
	wxString choicev = choice->GetStringSelection();
	wxString catv = cate->GetStringSelection();
	wxString finaltext;
	if (isIncome) finaltext = text + " - " + choicev;
	else finaltext = text + " - " + choicev + " - " + catv;
	result->SetLabel(finaltext);
	result->SetForegroundColour(*wxWHITE);

	if (isIncome) saveincome(result->GetLabel());
	else saveexpense(result->GetLabel());

	wxBoxSizer* box = new wxBoxSizer(wxVERTICAL);
	box->Add(result, 0, wxEXPAND, 5);

	
	ans->Destroy();
	cate->Destroy();
	choice->Destroy();
	ok->Destroy();

	result->Show();
	this->SetSizer(box);
	this->Layout();
}

void listBox::changein() {
	int index = choice->GetSelection();
	if (index == wxNOT_FOUND) return;
	double m = wxAtof(ans->GetValue());
	(*accounts)[index].add(m);
	(*boxes)[index]->refresh();

}

void listBox::changeex() {
	int index = choice->GetSelection();
	if (index == wxNOT_FOUND) return;
	double m = wxAtof(ans->GetValue());
	(*accounts)[index].sub(m);
	(*boxes)[index]->refresh();

}

void listBox::saveincome(wxString r) {
	ofstream incomefile("IncomeList.txt",ios::app);
	string re_r = r.ToStdString();
	incomefile << re_r << "\n";
}

void listBox::saveexpense(wxString r) {
	ofstream expensefile("ExpenseList.txt", ios::app);
	string re_r = r.ToStdString();
	expensefile << re_r << "\n";
}

listBox::listBox(wxScrolledWindow* parent, wxBoxSizer* mainSizer, std::vector<Account>* accs, std::vector<AccountBox*>* bxs, bool incomemode)
	: wxPanel(parent), accounts(accs), boxes(bxs), isIncome(incomemode){

	ans = new wxTextCtrl(this, wxID_ANY,"How much?");
	ans->SetForegroundColour(wxColor(128, 128, 128));
	

	wxArrayString categories;
	if (incomemode == 0) {
		string line;
		ifstream catfile("Categories.txt");
		while (getline(catfile, line)) {
			categories.Add(line);
		}
	}
	cate = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, categories);
	if (incomemode == 1) cate->Hide();
	if (cate->IsEmpty()) cate->Hide();

	wxArrayString names;
	for (const auto& a : *accounts) names.Add(wxString::FromUTF8(a.name));

	choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, names);

	ok = new wxButton(this, wxID_ANY, "OK", wxDefaultPosition, wxSize(20, 20));

	result = new wxStaticText(this, wxID_ANY, "");
	result->Hide();

	ok->Bind(wxEVT_BUTTON, &listBox::OnConfirm, this);
	
	wxBoxSizer* box = new wxBoxSizer(wxHORIZONTAL);
	box->Add(ans, 1, wxALL | wxEXPAND, 5);
	box->Add(cate, 0, wxALL, 5);
	box->Add(choice, 0, wxALL, 5);
	box->Add(ok, 0, wxALL, 5);
	this->SetSizer(box);
	mainSizer->Add(this, 0, wxALL, 5);
}

