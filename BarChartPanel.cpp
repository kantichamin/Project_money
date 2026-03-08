#include "BarChartPanel.h"

wxBEGIN_EVENT_TABLE(BarChartPanel, wxPanel)
EVT_PAINT(BarChartPanel::OnPaint)
wxEND_EVENT_TABLE()

BarChartPanel::BarChartPanel(wxWindow* parent)
    : wxPanel(parent)
{
    SetBackgroundColour(wxColour(30, 30, 30));

    Bind(wxEVT_SIZE, [this](wxSizeEvent& e) {
        Refresh();
        e.Skip();
        });
}

void BarChartPanel::OnPaint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);

    int w, h;
    GetClientSize(&w, &h);

    dc.SetBackground(wxBrush(wxColour(30, 30, 30)));
    dc.Clear();

    // ข้อมูลกราฟ
    double values[5] = { income, expense, net, deduction, tax };

    wxColour colors[5] = {
        wxColour(100,255,100), 
        wxColour(255,100,100),
        wxColour(255,255,255),
        wxColour(100,200,255),
        wxColour(255,165,0) 
    };

    wxString labels[5] = {
        L"รายรับ",
        L"รายจ่าย",
        L"รายได้รวม",
        L"ค่าลดหย่อน",
        L"ภาษี"
    };

    int marginLeft = 60;
    int marginBottom = 60;

    int chartHeight = h - marginBottom - 20;

    // หาค่าสูงสุด
    double maxVal = 1;
    for (int i = 0; i < 5; i++)
    {
        if (values[i] > maxVal)
            maxVal = values[i];
    }

    int chartWidth = w - marginLeft - 40;

    int barSpace = chartWidth / 5;
    int barWidth = barSpace * 0.6;

    // วาดแกน
    dc.SetPen(wxPen(wxColour(120, 120, 120)));

    dc.DrawLine(marginLeft, 10, marginLeft, chartHeight);
    dc.DrawLine(marginLeft, chartHeight, w - 20, chartHeight);

    // grid line
    dc.SetPen(wxPen(wxColour(70, 70, 70), 1, wxPENSTYLE_DOT));

    for (int i = 1; i <= 4; i++)
    {
        int y = chartHeight - (chartHeight * i / 4);
        dc.DrawLine(marginLeft, y, w - 20, y);
    }

    // วาดแท่งกราฟ
    for (int i = 0; i < 5; i++)
    {
        int x = marginLeft + i * barSpace + (barSpace - barWidth) / 2;

        int barHeight = (int)((values[i] / maxVal) * (chartHeight - 20));

        int y = chartHeight - barHeight;

        dc.SetBrush(wxBrush(colors[i]));
        dc.SetPen(*wxTRANSPARENT_PEN);

        dc.DrawRoundedRectangle(x, y, barWidth, barHeight, 5);

        // ตัวเลขด้านบน
        wxString val = wxString::Format("%.0f", values[i]);

        dc.SetTextForeground(*wxWHITE);

        int tw, th;
        dc.GetTextExtent(val, &tw, &th);

        dc.DrawText(val, x + (barWidth - tw) / 2, y - th - 2);

        // label ด้านล่าง
        wxString label = labels[i];

        dc.GetTextExtent(label, &tw, &th);

        dc.DrawText(label,
            x + (barWidth - tw) / 2,
            chartHeight + 5);
    }
}