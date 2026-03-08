#pragma once
#include <wx/wx.h>

class BarChartPanel : public wxPanel
{
public:
    BarChartPanel(wxWindow* parent);

    double income = 0;
    double expense = 0;
    double net = 0;
    double tax = 0;
    double deduction = 0;

private:
    void OnPaint(wxPaintEvent& evt);

    wxDECLARE_EVENT_TABLE();
};