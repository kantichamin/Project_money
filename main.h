#pragma once
#include<wx/wx.h>

class TaxFam;
class main : public wxPanel
{
public: 
    main(wxWindow* parant, wxPanel* main_panel);

    // ตัวแปรที่ต้องใช้ส่งค่า
    double Tax = 0.0;
    double Salary = 0.0;
    double FamilyDeduction = 0.0;
    double FamilyDuck = 0.0;
    double FamilySwan = 0.0;
    double FamilyChicken = 0.0;

    wxPanel* mainpanel;
    wxPanel* panel;
    TaxFam* panel1;
    wxTextCtrl* salaryman;
};

