#include "Quiz.h"

Quiz::Quiz(wxWindow* parent, wxPanel* main) : wxPanel(parent, wxID_ANY)
{
    mainpanel = main;
    RealRisk_1 = 1;
    RealRisk_2 = 1;

    risk_2 = true;

    panelall = new wxPanel(this);
    panelall->SetBackgroundColour(wxColor(50, 50, 50));


    //------- ส่วนของ ด้านล่างอันแรก -------//

    wxPanel* smallpanel = new wxPanel(panelall);
    smallpanel->SetBackgroundColour(wxColor(80, 80, 80));
    smallpanel->SetMinSize(wxSize(-1, 300));

    wxStaticText* smallpaneltext1 = new wxStaticText(smallpanel, wxID_ANY, L"สายการลงทุนของคุณ");
    smallpaneltext1->SetForegroundColour(wxColour(255, 255, 255));
    wxFont smallpanelfont1(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Segoe UI");
    smallpaneltext1->SetFont(smallpanelfont1);

    wxStaticText* smallpaneltext = new wxStaticText(smallpanel, wxID_ANY, L"-------------------------------------------");
    smallpaneltext->SetForegroundColour(wxColor(255, 255, 255));
    wxFont smallpanelfont(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Segoe UI");
    smallpaneltext->SetFont(smallpanelfont);

    wxStaticText* Ptext1 = new wxStaticText(smallpanel, wxID_ANY,
        L"โปรแกรมนี้มีวัตถุประสงค์เพื่อให้เกิดความเข้าใจ\n"
        L"เรื่องการจัดสรรเงินลงทุนซึ่งเป็นลักษณะเฉพาะของแต่ละบุคคล\n"
        L"มิได้จัดทำขึ้นเพื่อประเมินความเสี่ยงสำหรับการทำธุรกรรมใดๆ\n"
        L"* และเหมาะสำหรับคนที่ไม่มีภาระหนี้สิน *\n"
        L"* มีเงินฉุกเฉินเกิน 3 เดือน *\n"
        L"* และมีค่าใช้จ่ายจำเป็นไม่เกิน 60 % / เดือน *\n",
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTER);
    Ptext1->SetForegroundColour(wxColor(255, 255, 255));
    wxFont pltextfont(13, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Segoe UI");
    Ptext1->SetFont(pltextfont);

    wxBoxSizer* smallSizer = new wxBoxSizer(wxVERTICAL);
    smallSizer->Add(smallpaneltext1, 0, wxALIGN_CENTER | wxTOP, 20);
    smallSizer->Add(smallpaneltext, 0, wxALIGN_CENTER | wxTOP, 5);
	smallSizer->Add(Ptext1, 0, wxALIGN_CENTER | wxTOP, 5);

    smallpanel->SetSizer(smallSizer);


    //------- Scroll -------//

    mainScroll = new wxScrolledWindow(panelall, wxID_ANY);
    mainScroll->SetScrollRate(0, 20);


    // ------- เนื้อหา ------- //

    wxStaticText* paneltext1 = new wxStaticText(mainScroll, wxID_ANY, L"แนะนำ “ประเภทการลงทุน” สำหรับคุณ");
    paneltext1->SetForegroundColour(wxColor(255, 255, 255));
    wxFont paneltextfont(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Segoe UI");
    paneltext1->SetFont(paneltextfont);


    risk_1text = new wxStaticText(mainScroll, wxID_ANY, Typepanel(RealRisk_1));
    risk_1text->SetForegroundColour(wxColor(255, 255, 255));
    wxFont titleFont(28, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Segoe UI");
    risk_1text->SetFont(titleFont);


    wxStaticText* investTitle1 = new wxStaticText(mainScroll, wxID_ANY, L"การลงทุนที่เหมาะ\n");
    investTitle1->SetForegroundColour(wxColor(255, 255, 255));
    wxFont investTitleFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Segoe UI");
    investTitle1->SetFont(investTitleFont);


    item1 = new wxStaticText(mainScroll, wxID_ANY, investment(RealRisk_1));
    item1->SetForegroundColour(wxColor(255, 255, 255));
    wxFont itemFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Segoe UI");
    item1->SetFont(itemFont);


    wxStaticText* investTitle2 = new wxStaticText(mainScroll, wxID_ANY, L"สัดส่วนตัวอย่าง\n");
    investTitle2->SetForegroundColour(wxColor(255, 255, 255));
    investTitle2->SetFont(investTitleFont);


    item2 = new wxStaticText(mainScroll, wxID_ANY, proportion(RealRisk_1));
    item2->SetForegroundColour(wxColor(255, 255, 255));
    item2->SetFont(itemFont);


    wxStaticText* investTitle3 = new wxStaticText(mainScroll, wxID_ANY, L"คำอธิบาย\n");
    investTitle3->SetForegroundColour(wxColor(255, 255, 255));
    investTitle3->SetFont(investTitleFont);


    item3 = new wxStaticText(mainScroll, wxID_ANY, explanation(RealRisk_1));
    item3->SetForegroundColour(wxColor(255, 255, 255));
    item3->SetFont(itemFont);


    wxBoxSizer* mainScrollSizer = new wxBoxSizer(wxVERTICAL);

    mainScrollSizer->Add(paneltext1, 0, wxLEFT | wxTOP, 40);
    mainScrollSizer->Add(risk_1text, 0, wxLEFT, 60);

    mainScrollSizer->Add(investTitle1, 0, wxLEFT, 120);
    mainScrollSizer->Add(item1, 0, wxLEFT, 150);

    mainScrollSizer->Add(investTitle2, 0, wxLEFT, 120);
    mainScrollSizer->Add(item2, 0, wxLEFT, 150);

    mainScrollSizer->Add(investTitle3, 0, wxLEFT, 120);
    mainScrollSizer->Add(item3, 0, wxLEFT, 150);



    // -------- risk2 panel -------- //

    risk2Panel = new wxPanel(mainScroll);
    wxBoxSizer* risk2Sizer = new wxBoxSizer(wxVERTICAL);


    wxStaticText* Text1 = new wxStaticText(risk2Panel, wxID_ANY, L"\n-------------------------------------------\n");
    Text1->SetForegroundColour(wxColor(255, 255, 255));

    wxFont Text1Font(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Segoe UI");
    Text1->SetFont(Text1Font);


    Text1_ = new wxStaticText(risk2Panel, wxID_ANY, conjunction());
    Text1_->SetForegroundColour(wxColor(255, 255, 255));

    wxFont Text1_Font(28, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Segoe UI");
    Text1_->SetFont(Text1_Font);


    risk_1text2 = new wxStaticText(risk2Panel, wxID_ANY, Typepanel(RealRisk_2));
    risk_1text2->SetForegroundColour(wxColor(255, 255, 255));
    risk_1text2->SetFont(titleFont);


    wxStaticText* investTitle1_ = new wxStaticText(risk2Panel, wxID_ANY, L"การลงทุนที่เหมาะ\n");
    investTitle1_->SetForegroundColour(wxColor(255, 255, 255));
    investTitle1_->SetFont(investTitleFont);


    item1_ = new wxStaticText(risk2Panel, wxID_ANY, investment(RealRisk_2));
    item1_->SetForegroundColour(wxColor(255, 255, 255));
    item1_->SetFont(itemFont);


    wxStaticText* investTitle2_ = new wxStaticText(risk2Panel, wxID_ANY, L"สัดส่วนตัวอย่าง\n");
    investTitle2_->SetForegroundColour(wxColor(255, 255, 255));
    investTitle2_->SetFont(investTitleFont);


    item2_ = new wxStaticText(risk2Panel, wxID_ANY, proportion(RealRisk_2));
    item2_->SetForegroundColour(wxColor(255, 255, 255));
    item2_->SetFont(itemFont);


    wxStaticText* investTitle3_ = new wxStaticText(risk2Panel, wxID_ANY, L"คำอธิบาย\n");
    investTitle3_->SetForegroundColour(wxColor(255, 255, 255));
    investTitle3_->SetFont(investTitleFont);


    item3_ = new wxStaticText(risk2Panel, wxID_ANY, explanation(RealRisk_2));
    item3_->SetForegroundColour(wxColor(255, 255, 255));
    item3_->SetFont(itemFont);



    risk2Sizer->Add(Text1, 0, wxALIGN_CENTER);
    risk2Sizer->Add(Text1_, 0, wxLEFT | wxTOP, 40);
    risk2Sizer->Add(risk_1text2, 0, wxLEFT, 60);

    risk2Sizer->Add(investTitle1_, 0, wxLEFT, 120);
    risk2Sizer->Add(item1_, 0, wxLEFT, 150);

    risk2Sizer->Add(investTitle2_, 0, wxLEFT, 120);
    risk2Sizer->Add(item2_, 0, wxLEFT, 150);

    risk2Sizer->Add(investTitle3_, 0, wxLEFT, 120);
    risk2Sizer->Add(item3_, 0, wxLEFT, 150);


    risk2Panel->SetSizer(risk2Sizer);

    mainScrollSizer->Add(risk2Panel, 0, wxEXPAND);


    mainScroll->SetSizer(mainScrollSizer);
    mainScroll->FitInside();


    // ------- Layout ------- //

    wxBoxSizer* panelallSizer = new wxBoxSizer(wxVERTICAL);
    panelallSizer->Add(smallpanel, 0, wxEXPAND);
    panelallSizer->Add(mainScroll, 1, wxEXPAND);

    panelall->SetSizer(panelallSizer);


    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(panelall, 1, wxEXPAND);

    SetSizer(mainSizer);


    risk2Panel->Show(risk_2 && RealRisk_1 != RealRisk_2);
}



// -------- Score -------- //

int Quiz::SetScore(int r, int m, int re)
{
    RealRisk_1 = r;

    bool allowIncrease = false;

    if (m == 1 && RealRisk_1 > 1) RealRisk_1 -= 1;
    if (m == 3) allowIncrease = true;
    if (allowIncrease && re == 3 && RealRisk_1 < 3) RealRisk_1 += 1;

    if (RealRisk_1 < 1) RealRisk_1 = 1;
    if (RealRisk_1 > 3) RealRisk_1 = 3;

    risk_1text2->SetLabel(Typepanel(RealRisk_1));
    item1_->SetLabel(investment(RealRisk_1));
    item2_->SetLabel(proportion(RealRisk_1));
    item3_->SetLabel(explanation(RealRisk_1));
    Text1_->SetLabel(conjunction());

    return RealRisk_1;
}



int Quiz::SetScore2(int r, int m, int re)
{
    

    RealRisk_2 = RealRisk_1;
    risk_2 = true;

    if (r == 1)
        risk_2 = false;

    else if (r == 2)
    {
        if (m == 1) RealRisk_2 -= 1;
        else if (m == 2) RealRisk_2 -= 1;
        else if (m == 3 && re == 3) RealRisk_2 += 1;
    }

    else if (r == 3)
    {
        if (m == 1) RealRisk_2 -= 1;
        else if (m == 2) RealRisk_2 -= 1;
        else if (m == 3 && re == 3) risk_2 = false;
    }

    if (RealRisk_2 < 1) RealRisk_2 = 1;
    if (RealRisk_2 > 3) RealRisk_2 = 3;

    if (RealRisk_2 == RealRisk_1)
        risk_2 = false;

    risk_1text->SetLabel(Typepanel(RealRisk_2));
    item1_->SetLabel(investment(RealRisk_2));
    item2_->SetLabel(proportion(RealRisk_2));
    item3_->SetLabel(explanation(RealRisk_2));
    Text1_->SetLabel(conjunction());

    if (risk_2 && RealRisk_1 != RealRisk_2)
        risk2Panel->Show(true);
    else
        risk2Panel->Show(false);

    mainScroll->FitInside();
    Layout();
    Refresh();

    return RealRisk_2;
}

wxString Quiz::Typepanel(int r) {
    wxString t;

    if (r == 1) t = L"\n🟡 สายอนุรักษ์ (ความเสี่ยงต่ำ)\n";
    else if (r == 2) t = L"\n🟡 สายสมดุล (ความเสี่ยงกลาง)\n";
    else if (r == 3) t = L"\n🟡 สายเติบโต (ความเสี่ยงสูง)\n";

    return t;
}

wxString Quiz::investment(int r) {
    wxString t;

    if (r == 1) t = L"•  เงินฝาก / ออมทรัพย์ดอกเบี้ยสูง\n\n•  กองทุนตลาดเงิน\n\n•  กองทุนตราสารหนี้\n\n•  ประกันออมทรัพย์ / ประกันสะสมทรัพย์\n\n";
    else if (r == 2) t = L"•  กองทุนหุ้นไทย / หุ้นต่างประเทศ\n\n•  ETF ตลาดหลัก\n\n•  กองทุนดัชนี(Index Fund)\n\n•  กองทุนผสม\n\n";
    else if (r == 3) t = L"•  หุ้นรายตัว\n\n•  กองทุนหุ้นเฉพาะกลุ่ม / เทคโนโลยี\n\n•  ETF เชิงธีม\n\n•  สินทรัพย์ทางเลือก (บางส่วน)\n\n";

    return t;
}

wxString Quiz::proportion(int r) {
	wxString t;

    if (r == 1) t = L"•  ความเสี่ยงต่ำ 80–100%\n\n•  สินทรัพย์เสี่ยง 0–20%\n\n";
    else if (r == 2) t = L"•  ความเสี่ยงต่ำ 40–60%\n\n•  สินทรัพย์เสี่ยง 40–60%\n\n";
    else if (r == 3) t = L"•  ความเสี่ยงต่ำ 0–20%\n\n•  สินทรัพย์เสี่ยง 80–100%\n\n";

	return t;
}

wxString Quiz::explanation(int r) {
    wxString t;

    if (r == 1) t = L" | เหมาะกับการเริ่มต้นลงทุน\n | เน้นรักษาเงินต้นและสร้างวินัยทางการเงิน\n |  ผลตอบแทนอาจไม่สูง แต่ความผันผวนต่ำมาก\n";
    else if (r == 2) t = L" | เหมาะกับผู้ที่ต้องการให้เงินเติบโตอย่างสม่ำเสมอ\n | รับความผันผวนได้ในระดับหนึ่ง\n |  ควรลงทุนแบบทยอย (DCA) และถือระยะกลาง–ยาว\n";
    else if (r == 3) t = L" | เหมาะกับการลงทุนเพื่อเพิ่มมูลค่าในระยะยาว\n | ต้องรับความผันผวนและขาดทุนระยะสั้นได้\n |  วินัยและการกระจายความเสี่ยงสำคัญมาก\n";

    return t;
}

wxString Quiz::conjunction() {
    wxString t;

    if (RealRisk_1 > RealRisk_2) {
        return L"ถ้าคุณอยาก \"ลดความเสี่ยง\" นี่คืออีกแนวทาง\n";
    }
    else {
        return L"ถ้าคุณอยาก \"พัฒนา\" นี่คืออีกแนวทาง\n";
    }
}
