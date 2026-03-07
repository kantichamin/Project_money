#include "InandEx.h"
#include "MyKeepPanel.h"
#include "MyWishlistPanel.h"
#include "MySummaryPanel.h"
#include "Account.h"
#include "listBox.h"
#include "MainFrame.h"

using namespace std;
wxString InandEx::AskAccountName() {
    wxTextEntryDialog dlg(this, "Enter account name: ");
    if (dlg.ShowModal() == wxID_OK) 
        return dlg.GetValue();
    return "";
}

int InandEx::AskBalance() {
    wxTextEntryDialog dlg(this, "Enter Balance: ");
    if (dlg.ShowModal() == wxID_OK)
        return wxAtoi(dlg.GetValue());
    return 0;
}

void InandEx::LoadAccounts() {
    ifstream accountfile("accounts.txt");
    string name;
    double balance;
    while (accountfile >> name >> balance) {
        accounts.emplace_back(name, balance);
        AccountBox* box = new AccountBox(accScroll, accountSizer, &accounts,accounts.size()-1);
        boxes.push_back(box);
        box->refresh();
        
    }
    accountfile.close();
    accountSizer->Layout();
    panel->Layout();

    string infilename = "IncomeList.txt";
    string exfilename = "ExpenseList.txt";
    string date = dateStr.ToStdString();
    if (!IsTodayAlreayWritten(infilename, date)) {
        ofstream incomefile(infilename, ios::app);
        incomefile << date << "\n";
        incomefile.close();
    }

    if (!IsTodayAlreayWritten(exfilename, date)) {
        ofstream expensefile(exfilename, ios::app);
        expensefile << date << "\n";
        expensefile.close();
    }
    
}

void InandEx::SaveAccounts() {
    ofstream accountfile("accounts.txt");
    for (const Account& acc : accounts)
        accountfile << acc.name << " " << acc.balance << "\n";
    
    

    
}


bool InandEx::IsTodayAlreayWritten(const string& filename, const string& date) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line == date) return true;
    }
    return false;
}

void InandEx::SaveCate() {
    ofstream catfile("Categories.txt");
    for (const auto& c : cate) {
        catfile << c << "\n";
    }
    catfile.close();
}

void InandEx::LoadCate() {
    cate.clear();

    ifstream catfile("Categories.txt");
    string line;


    while (getline(catfile, line)) {
        if (!line.empty())
            cate.push_back(line);
    }

    
    if (cate.empty()) {
        cate.push_back("Food");
        SaveCate();
    }

    catfile.close();
}

InandEx::InandEx(wxWindow* parent, wxPanel* main_panel)
    : wxPanel(parent, wxID_ANY) {
    mainpanel = main_panel;
    panel = new wxPanel(this);
    

    Keep_panel = new MyKeepPanel(this,panel, &accounts, &boxes);
    Wish_panel = new MyWishlistPanel(this, panel, &accounts, &boxes);
    Summary_panel = new MySummaryPanel(this, panel);
    panel->Show(true);
    Keep_panel->Show(false);
    Wish_panel->Show(false);
    Summary_panel->Show(false);
    
    
    SetBackgroundColour(wxColour(80, 80, 80));
    

    // ===== top bar account =====
    wxPanel* topBar = new wxPanel(panel);
    topBar->SetBackgroundColour(wxColour(60, 60, 60));
    wxStaticText* titleText = new wxStaticText(topBar, wxID_ANY, "Account");
    titleText->SetForegroundColour(*wxWHITE);
    
    

    // ===== account =====
    wxButton* Addacc = new wxButton( panel,wxID_ANY, "+", wxDefaultPosition, wxSize(20, 20));
    Addacc->SetBackgroundColour(wxColour(60, 60, 60));
    Addacc->SetForegroundColour(*wxWHITE);
    
    accScroll = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(780, 150));
    accScroll->SetBackgroundColour(wxColour(80, 80, 80));
    accScroll->SetScrollRate(5, 5);
    accountSizer = new wxBoxSizer(wxHORIZONTAL);
    accScroll->SetSizer(accountSizer);
    
    accounts.clear();
    LoadAccounts();
    LoadCate();
    Wish_panel->LoadWish();
    
    
    Keep_panel->RefreshAccounts();

    Addacc->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        wxString name = AskAccountName();
        
        if (name.IsEmpty()) return; 
        int money = AskBalance();
        accounts.emplace_back(name, money);
        AccountBox* box = new AccountBox(accScroll, accountSizer,&accounts ,accounts.size()-1);
        boxes.push_back(box);
        box->refresh();
        accountSizer->Layout();
        panel->Layout();

        Keep_panel->RefreshAccounts();
        
        });
    
    
    // ===== topbar income =====
    wxPanel* topBarin = new wxPanel(panel);
    topBarin->SetBackgroundColour(wxColour(60, 60, 60));
    wxStaticText* titleTextin = new wxStaticText(topBarin, wxID_ANY, "Income");
    titleTextin->SetForegroundColour(*wxWHITE);

    // ===== income =====
    wxStaticText* date = new wxStaticText(panel, wxID_ANY, "Date: "+dateStr);
    date->SetForegroundColour(*wxWHITE);
    wxButton* Addincome = new wxButton(panel, wxID_ANY, "+",wxDefaultPosition,wxSize(20,20));
    Addincome->SetBackgroundColour(wxColor(60, 60, 60));
    Addincome->SetForegroundColour(*wxWHITE);

    inScroll = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(780, 120));
    inScroll->SetBackgroundColour(wxColour(80, 80, 80));
    inScroll->SetScrollRate(0, 5);
    incomelistbox = new wxBoxSizer(wxVERTICAL);
	inScroll->SetSizer(incomelistbox);

    Addincome->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        listBox* inlist = new listBox(inScroll, incomelistbox, &accounts, &boxes,true);
        //incomelistbox->Layout();
        inScroll->FitInside();
        inScroll->Layout();
        //panel->Layout();
        });

    // ===== topbar expense =====
    wxPanel* topBarex = new wxPanel(panel);
    topBarex->SetBackgroundColour(wxColour(60, 60, 60));
    wxStaticText* titleTextex = new wxStaticText(topBarex, wxID_ANY, "Expense");
    titleTextex->SetForegroundColour(*wxWHITE);
    wxButton* Addexpense = new wxButton(panel, wxID_ANY, "+", wxDefaultPosition, wxSize(20, 20));
    Addexpense->SetBackgroundColour(wxColor(60, 60, 60));
    Addexpense->SetForegroundColour(*wxWHITE);
    wxButton* Addcategory = new wxButton(panel, wxID_ANY, L"เพิ่มหมวดหมู่");
    Addcategory->SetBackgroundColour(wxColor(60, 60, 60));
    Addcategory->SetForegroundColour(*wxWHITE);

    Addcategory->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        wxTextEntryDialog dlg(this, L"ชื่อหมวดหมู่: ");
        if (dlg.ShowModal() == wxID_OK) {
            wxString newCate = dlg.GetValue().Trim().Trim(false);
            if (newCate.IsEmpty()) return;

            
            bool exists = false;
            for (const auto& c : cate) {
                if (c == newCate) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                cate.push_back(newCate);
                SaveCate();
            }
            else {
                wxMessageBox("หมวดหมู่นี้มีอยู่แล้ว");
            }
        }
        });

    exScroll = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxSize(780, 20));
    exScroll->SetBackgroundColour(wxColour(80, 80, 80));
    exScroll->SetScrollRate(0, 5);
    expenselistbox = new wxBoxSizer(wxVERTICAL);
	exScroll->SetSizer(expenselistbox);

    Addexpense->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        listBox* exlist = new listBox(exScroll, expenselistbox, &accounts, &boxes,false);
        expenselistbox->Layout();
        panel->Layout();
        });

    // Button to each page
	wxButton* back = new wxButton(topBar, wxID_ANY, "<<", wxDefaultPosition, wxSize(40,20));
    back->SetBackgroundColour(wxColour(60, 60, 60));
    back->SetForegroundColour(*wxWHITE);

    wxButton* button = new wxButton(topBar, wxID_ANY, "Keep");
    button->SetMinSize(wxSize(80, 30));
    button->SetBackgroundColour(wxColour(60, 60, 60));
    button->SetForegroundColour(*wxWHITE);

    wxButton* button1 = new wxButton(topBar, wxID_ANY, "Wish List");
    button1->SetMinSize(wxSize(80, 30));
    button1->SetBackgroundColour(wxColour(60, 60, 60));
    button1->SetForegroundColour(*wxWHITE);

    wxButton* button2 = new wxButton(topBar, wxID_ANY, "Summary");
    button2->SetMinSize(wxSize(80, 30));
    button2->SetBackgroundColour(wxColour(60, 60, 60));
    button2->SetForegroundColour(*wxWHITE);

    // ===== sizer topBar =====
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(titleText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topSizer->AddStretchSpacer();
    topSizer->Add(back, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topSizer->Add(button, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topSizer->Add(button1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topSizer->Add(button2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topBar->SetSizer(topSizer);

    wxBoxSizer* topSizerin = new wxBoxSizer(wxHORIZONTAL);
    topSizerin->Add(titleTextin, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topBarin->SetSizer(topSizerin);
    topBarin->SetMinSize(wxSize(-1, 40));

    wxBoxSizer* topSizerex = new wxBoxSizer(wxHORIZONTAL);
    topSizerex->Add(titleTextex, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    topBarex->SetSizer(topSizerex);
    topBarex->SetMinSize(wxSize(-1, 40));
    

    // ===== main sizer =====
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(topBar, 0, wxEXPAND);
    mainSizer->AddSpacer(10);
    mainSizer->Add(Addacc, 0, wxALL,10);
    mainSizer->Add(accScroll, 0, wxEXPAND);
    mainSizer->AddSpacer(10);
    mainSizer->Add(topBarin, 0, wxEXPAND);
    mainSizer->AddSpacer(10);
    mainSizer->Add(date, 0, wxALIGN_CENTER);
    mainSizer->Add(Addincome, 0, wxALL,10);
    mainSizer->Add(inScroll, 0, wxEXPAND);
    mainSizer->AddSpacer(10);
    mainSizer->Add(topBarex, 0, wxEXPAND);
    mainSizer->AddSpacer(10);
    wxBoxSizer* addcat = new wxBoxSizer(wxHORIZONTAL);
    addcat->Add(Addexpense, 0, wxLEFT, 10);
	addcat->Add(Addcategory, 0, wxLEFT, 5);
    mainSizer->Add(addcat, 0, wxALL,10);
    mainSizer->Add(exScroll, 1, wxEXPAND);
    


    panel->SetSizer(mainSizer);

    // ===== page =====
    button->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        panel->Show(false);
        Keep_panel->Show(true);
        this->Layout();
        });
    button1->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        panel->Show(false);
        Wish_panel->Show(true);
        this->Layout();
        });
    button2->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        panel->Show(false);
        Summary_panel->Show(true);
		Summary_panel->RefreshSummary();
        this->Layout();
        });

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(panel, 1, wxEXPAND);
    frameSizer->Add(Keep_panel, 1, wxEXPAND);
    frameSizer->Add(Wish_panel, 1, wxEXPAND);
    frameSizer->Add(Summary_panel, 1, wxEXPAND);
    this->SetSizer(frameSizer);

    back->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        this->Hide();
        mainpanel->Show();
        MainFrame* frame = (MainFrame*)mainpanel->GetParent();
		frame->Refreshinfo();
		frame->Layout();
        });

    
}