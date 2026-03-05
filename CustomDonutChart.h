#ifndef CUSTOMDONUTCHART_H
#define CUSTOMDONUTCHART_H

#include <wx/wx.h>

class DonutChart : public wxPanel
{
public:
    DonutChart(wxWindow* parent);
    void SetValues(double income, double expense, double invest);

private:
    // ** เช็คด่วน: ต้องมี 3 บรรทัดนี้ในส่วน private **
    double vIncome = 0;
    double vExpense = 0;
    double vInvest = 0;

    void OnPaint(wxPaintEvent& evt);
};

#endif