#include "CustomDonutChart.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <math.h> // สำหรับ M_PI

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

DonutChart::DonutChart(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(260, 260))
{
    // ใช้ Double Buffer เพื่อลดการกระพริบ
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &DonutChart::OnPaint, this);
    SetBackgroundColour(wxColour(30, 30, 30)); // สีพื้นหลังให้เนียนไปกับ Panel หลัก
}

void DonutChart::SetValues(double income, double expense, double invest)
{
    vIncome = income;
    vExpense = expense;
    vInvest = invest;
    Refresh(); // สั่งให้วาดใหม่เมื่อค่าเปลี่ยน
}

void DonutChart::OnPaint(wxPaintEvent& evt)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    double total = vIncome + vExpense + vInvest;

    // ถ้าไม่มีข้อมูลเลย ให้วาดวงกลมสีเทาว่างๆ ไว้ก่อน
    if (total <= 0) {
        gc->SetBrush(wxBrush(wxColour(60, 60, 60)));
        gc->DrawEllipse(30, 30, 200, 200);
        delete gc;
        return;
    }

    int w, h;
    GetSize(&w, &h);
    double cx = w / 2.0;
    double cy = h / 2.0;
    double radius = 100.0;

    // จุดเริ่มต้นคือด้านบน (เที่ยงตรง)
    double startAngle = -M_PI / 2.0;
    // 1. วาดส่วนรายรับ (สีเขียว)
    wxGraphicsPath path1 = gc->CreatePath();
    double angle1 = (vIncome / total) * 2.0 * M_PI;
    path1.MoveToPoint(cx, cy); // จุดเริ่มที่ศูนย์กลาง
    path1.AddArc(cx, cy, radius, startAngle, startAngle + angle1, true); // วาดเส้นโค้ง
    path1.CloseSubpath();
    gc->SetBrush(wxBrush(wxColour(50, 200, 50)));
    gc->FillPath(path1);
    startAngle += angle1;

    // 2. วาดส่วนรายจ่าย (สีแดง)
    wxGraphicsPath path2 = gc->CreatePath();
    double angle2 = (vExpense / total) * 2.0 * M_PI;
    path2.MoveToPoint(cx, cy);
    path2.AddArc(cx, cy, radius, startAngle, startAngle + angle2, true);
    path2.CloseSubpath();
    gc->SetBrush(wxBrush(wxColour(220, 60, 60)));
    gc->FillPath(path2);

    // 3. เจาะรูตรงกลาง (ทำให้เป็นโดนัทตามแบบ)
    gc->SetBrush(wxBrush(wxColour(30, 30, 30)));
    gc->DrawEllipse(cx - 65, cy - 65, 130, 130);
    delete gc;
}