#include "stdafx.h"
#include "ReportsForm.h"

namespace DeviceManagementApp {

    void ReportsForm::InitializeComponent()
    {
        this->Text = L"Отчеты";
        this->Size = System::Drawing::Size(800, 600);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::WhiteSmoke;

        Label^ lblTitle = gcnew Label();
        lblTitle->Text = L"Отчеты (функция в разработке)";
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
        lblTitle->Location = Point(20, 20);
        lblTitle->Size = Drawing::Size(400, 30);
        lblTitle->ForeColor = Color::DarkBlue;
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);
    }
}