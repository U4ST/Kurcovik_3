#include "stdafx.h"
#include "RepairCompleteForm.h"

namespace DeviceManagementApp {

    void RepairCompleteForm::InitializeComponent()
    {
        this->Text = L"Завершение ремонта";
        this->Size = System::Drawing::Size(500, 400);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = Color::WhiteSmoke;

        Label^ lblTitle = gcnew Label();
        lblTitle->Text = L"Завершение ремонта";
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
        lblTitle->Location = Point(20, 20);
        lblTitle->Size = Drawing::Size(450, 30);
        lblTitle->ForeColor = Color::DarkBlue;
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        int yPos = 60;
        int labelWidth = 180;
        int fieldWidth = 250;

        // Дата ремонта
        Label^ lblDate = gcnew Label();
        lblDate->Text = L"Дата ремонта:";
        lblDate->Location = Point(20, yPos);
        lblDate->Size = Drawing::Size(labelWidth, 25);
        lblDate->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblDate);

        dtpRepairDate = gcnew DateTimePicker();
        dtpRepairDate->Location = Point(210, yPos);
        dtpRepairDate->Size = Drawing::Size(fieldWidth, 25);
        dtpRepairDate->Format = DateTimePickerFormat::Short;
        this->Controls->Add(dtpRepairDate);

        yPos += 40;

        // Стоимость
        Label^ lblCost = gcnew Label();
        lblCost->Text = L"Стоимость ремонта ($):";
        lblCost->Location = Point(20, yPos);
        lblCost->Size = Drawing::Size(labelWidth, 25);
        lblCost->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblCost);

        txtRepairCost = gcnew TextBox();
        txtRepairCost->Location = Point(210, yPos);
        txtRepairCost->Size = Drawing::Size(fieldWidth, 25);
        txtRepairCost->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtRepairCost->KeyPress += gcnew KeyPressEventHandler(this, &RepairCompleteForm::txtRepairCost_KeyPress);
        this->Controls->Add(txtRepairCost);

        yPos += 40;

        // Описание работ
        Label^ lblWork = gcnew Label();
        lblWork->Text = L"Описание выполненных работ:";
        lblWork->Location = Point(20, yPos);
        lblWork->Size = Drawing::Size(labelWidth, 25);
        lblWork->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblWork);

        txtWorkDescription = gcnew TextBox();
        txtWorkDescription->Location = Point(210, yPos);
        txtWorkDescription->Multiline = true;
        txtWorkDescription->Size = Drawing::Size(fieldWidth, 80);
        txtWorkDescription->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtWorkDescription->ScrollBars = ScrollBars::Vertical;
        this->Controls->Add(txtWorkDescription);

        yPos += 100;

        // Гарантия
        Label^ lblWarranty = gcnew Label();
        lblWarranty->Text = L"Гарантия на ремонт (дней):";
        lblWarranty->Location = Point(20, yPos);
        lblWarranty->Size = Drawing::Size(labelWidth, 25);
        lblWarranty->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblWarranty);

        txtWarrantyDays = gcnew TextBox();
        txtWarrantyDays->Location = Point(210, yPos);
        txtWarrantyDays->Size = Drawing::Size(fieldWidth, 25);
        txtWarrantyDays->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtWarrantyDays->KeyPress += gcnew KeyPressEventHandler(this, &RepairCompleteForm::txtWarrantyDays_KeyPress);
        this->Controls->Add(txtWarrantyDays);

        yPos += 40;

        // Техник
        Label^ lblTech = gcnew Label();
        lblTech->Text = L"ФИО техника:";
        lblTech->Location = Point(20, yPos);
        lblTech->Size = Drawing::Size(labelWidth, 25);
        lblTech->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblTech);

        txtTechnicianName = gcnew TextBox();
        txtTechnicianName->Location = Point(210, yPos);
        txtTechnicianName->Size = Drawing::Size(fieldWidth, 25);
        txtTechnicianName->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(txtTechnicianName);

        yPos += 50;

        // Кнопки
        btnSave = gcnew Button();
        btnSave->Text = L"Сохранить";
        btnSave->Location = Point(150, yPos);
        btnSave->Size = Drawing::Size(120, 35);
        btnSave->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
        btnSave->BackColor = Color::LightGreen;
        btnSave->Click += gcnew EventHandler(this, &RepairCompleteForm::btnSave_Click);
        this->Controls->Add(btnSave);

        btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(280, yPos);
        btnCancel->Size = Drawing::Size(120, 35);
        btnCancel->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
        btnCancel->BackColor = Color::LightGray;
        btnCancel->Click += gcnew EventHandler(this, &RepairCompleteForm::btnCancel_Click);
        this->Controls->Add(btnCancel);

        this->AcceptButton = btnSave;
        this->CancelButton = btnCancel;
    }

    void RepairCompleteForm::LoadRepairData()
    {
        dtpRepairDate->Value = DateTime::Now;
        txtWarrantyDays->Text = "90"; // Значение по умолчанию
    }

    void RepairCompleteForm::btnSave_Click(Object^ sender, EventArgs^ e)
    {
        // Проверка ввода
        double cost;
        if (!Double::TryParse(txtRepairCost->Text, cost) || cost < 0)
        {
            MessageBox::Show(L"Введите корректную стоимость ремонта!",
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtRepairCost->Focus();
            return;
        }

        int warrantyDays;
        if (!Int32::TryParse(txtWarrantyDays->Text, warrantyDays) || warrantyDays < 0)
        {
            MessageBox::Show(L"Введите корректное количество дней гарантии!",
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtWarrantyDays->Focus();
            return;
        }

        // Сохранение данных
        repairData->RepairDate = dtpRepairDate->Value;
        repairData->RepairCost = cost;
        repairData->WorkDescription = txtWorkDescription->Text;
        repairData->WarrantyDays = warrantyDays;
        repairData->TechnicianName = txtTechnicianName->Text;
        repairData->CompletedDate = DateTime::Now;

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }

    void RepairCompleteForm::btnCancel_Click(Object^ sender, EventArgs^ e)
    {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    void RepairCompleteForm::txtRepairCost_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        // Разрешаем только цифры, точку и backspace
        if (!Char::IsDigit(e->KeyChar) && e->KeyChar != '.' && e->KeyChar != 0x08)
        {
            e->Handled = true;
        }
    }

    void RepairCompleteForm::txtWarrantyDays_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        // Разрешаем только цифры и backspace
        if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
        {
            e->Handled = true;
        }
    }
}