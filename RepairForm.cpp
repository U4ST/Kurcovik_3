#include "stdafx.h"
#include "RepairForm.h"
#include "DeviceSearchForm.h"

namespace DeviceManagementApp {

    void RepairForm::InitializeComponent()
    {
        this->Text = L"Создание заявки на ремонт";
        this->Size = System::Drawing::Size(500, 450);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = Color::WhiteSmoke;

        lblTitle = gcnew Label();
        lblTitle->Text = L"Новая заявка на ремонт";
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
        lblTitle->Location = Point(20, 20);
        lblTitle->Size = Drawing::Size(450, 30);
        lblTitle->ForeColor = Color::DarkBlue;
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        int yPos = 60;
        int labelWidth = 150;
        int fieldWidth = 300;

        // Выбор устройства
        Label^ lblDevice = gcnew Label();
        lblDevice->Text = L"Выбор устройства:";
        lblDevice->Location = Point(20, yPos);
        lblDevice->Size = Drawing::Size(labelWidth, 25);
        lblDevice->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblDevice);

        cmbDevices = gcnew ComboBox();
        cmbDevices->Location = Point(180, yPos);
        cmbDevices->Size = Drawing::Size(200, 25);
        cmbDevices->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbDevices->DropDownStyle = ComboBoxStyle::DropDownList;
        this->Controls->Add(cmbDevices);

        btnSearchDevice = gcnew Button();
        btnSearchDevice->Text = L"Поиск";
        btnSearchDevice->Location = Point(390, yPos);
        btnSearchDevice->Size = Drawing::Size(80, 25);
        btnSearchDevice->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnSearchDevice->BackColor = Color::LightGray;
        btnSearchDevice->Click += gcnew EventHandler(this, &RepairForm::btnSearchDevice_Click);
        this->Controls->Add(btnSearchDevice);

        yPos += 40;

        // Описание проблемы
        Label^ lblProblem = gcnew Label();
        lblProblem->Text = L"Описание проблемы:";
        lblProblem->Location = Point(20, yPos);
        lblProblem->Size = Drawing::Size(labelWidth, 25);
        lblProblem->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblProblem);

        txtProblemDescription = gcnew TextBox();
        txtProblemDescription->Location = Point(180, yPos);
        txtProblemDescription->Multiline = true;
        txtProblemDescription->Size = Drawing::Size(290, 80);
        txtProblemDescription->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtProblemDescription->ScrollBars = ScrollBars::Vertical;
        this->Controls->Add(txtProblemDescription);

        yPos += 100;

        // Срочность
        Label^ lblUrgency = gcnew Label();
        lblUrgency->Text = L"Срочность:";
        lblUrgency->Location = Point(20, yPos);
        lblUrgency->Size = Drawing::Size(labelWidth, 25);
        lblUrgency->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblUrgency);

        cmbUrgency = gcnew ComboBox();
        cmbUrgency->Location = Point(180, yPos);
        cmbUrgency->Size = Drawing::Size(200, 25);
        cmbUrgency->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbUrgency->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbUrgency->Items->AddRange(gcnew cli::array<String^>(3) {
            L"Низкая", L"Средняя", L"Высокая"
        });
        cmbUrgency->SelectedIndex = 1;
        this->Controls->Add(cmbUrgency);

        yPos += 40;

        // Контактные данные
        Label^ lblContact = gcnew Label();
        lblContact->Text = L"Контактные данные:";
        lblContact->Location = Point(20, yPos);
        lblContact->Size = Drawing::Size(labelWidth, 25);
        lblContact->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblContact);

        txtContactInfo = gcnew TextBox();
        txtContactInfo->Location = Point(180, yPos);
        txtContactInfo->Size = Drawing::Size(290, 25);
        txtContactInfo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(txtContactInfo);

        yPos += 50;

        // Кнопки
        btnSave = gcnew Button();
        btnSave->Text = L"Создать заявку";
        btnSave->Location = Point(150, yPos);
        btnSave->Size = Drawing::Size(120, 35);
        btnSave->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
        btnSave->BackColor = Color::LightGreen;
        btnSave->Click += gcnew EventHandler(this, &RepairForm::btnSave_Click);
        this->Controls->Add(btnSave);

        btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(280, yPos);
        btnCancel->Size = Drawing::Size(120, 35);
        btnCancel->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
        btnCancel->BackColor = Color::LightGray;
        btnCancel->Click += gcnew EventHandler(this, &RepairForm::btnCancel_Click);
        this->Controls->Add(btnCancel);

        this->AcceptButton = btnSave;
        this->CancelButton = btnCancel;
    }

    void RepairForm::LoadDevices()
    {
        cmbDevices->Items->Clear();

        if (availableDevices != nullptr)
        {
            for each (DeviceData ^ device in availableDevices)
            {
                String^ displayText = String::Format(L"{0} ({1})",
                    device->Model, device->IMEI);
                cmbDevices->Items->Add(displayText);
            }

            if (cmbDevices->Items->Count > 0)
                cmbDevices->SelectedIndex = 0;
        }
    }

    void RepairForm::btnSave_Click(Object^ sender, EventArgs^ e)
    {
        if (cmbDevices->SelectedIndex == -1)
        {
            MessageBox::Show(L"Выберите устройство!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        if (String::IsNullOrWhiteSpace(txtProblemDescription->Text))
        {
            MessageBox::Show(L"Введите описание проблемы!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtProblemDescription->Focus();
            return;
        }

        // Сохраняем данные
        if (cmbDevices->SelectedIndex >= 0 && cmbDevices->SelectedIndex < availableDevices->Count)
        {
            DeviceData^ selectedDevice = availableDevices[cmbDevices->SelectedIndex];
            repairData->DeviceId = selectedDevice->Id;
            repairData->DeviceIMEI = selectedDevice->IMEI;
            repairData->DeviceModel = selectedDevice->Model;
        }

        repairData->ProblemDescription = txtProblemDescription->Text;
        repairData->Urgency = cmbUrgency->SelectedItem->ToString();
        repairData->ContactInfo = txtContactInfo->Text;
        repairData->CreatedDate = DateTime::Now;
        repairData->Status = L"Создана";

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }

    void RepairForm::btnCancel_Click(Object^ sender, EventArgs^ e)
    {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    void RepairForm::btnSearchDevice_Click(Object^ sender, EventArgs^ e)
    {
        try
        {
            DeviceSearchForm^ searchForm = gcnew DeviceSearchForm(availableDevices);

            if (searchForm->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
            {
                int selectedIndex = searchForm->SelectedIndex;
                if (selectedIndex >= 0 && selectedIndex < availableDevices->Count)
                {
                    cmbDevices->SelectedIndex = selectedIndex;
                }
            }
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(String::Format(L"Ошибка поиска: {0}", ex->Message),
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}