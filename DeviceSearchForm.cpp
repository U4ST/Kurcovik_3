#include "stdafx.h"
#include "DeviceSearchForm.h"

namespace DeviceManagementApp {

    DeviceSearchForm::DeviceSearchForm(List<DeviceData^>^ devices)
    {
        availableDevices = devices;
        selectedIndex = -1;
        InitializeComponent();
        LoadDevices();
    }

    void DeviceSearchForm::InitializeComponent()
    {
        this->Text = L"Поиск устройства";
        this->Size = System::Drawing::Size(500, 400);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;

        // Поле поиска
        Label^ lblSearch = gcnew Label();
        lblSearch->Text = L"Поиск по IMEI/модели:";
        lblSearch->Location = System::Drawing::Point(20, 20);
        lblSearch->Size = System::Drawing::Size(150, 25);
        this->Controls->Add(lblSearch);

        txtSearch = gcnew TextBox();
        txtSearch->Location = System::Drawing::Point(180, 20);
        txtSearch->Size = System::Drawing::Size(250, 25);
        txtSearch->TextChanged += gcnew System::EventHandler(this, &DeviceSearchForm::txtSearch_TextChanged);
        this->Controls->Add(txtSearch);

        // Список устройств
        dgvDevices = gcnew DataGridView();
        dgvDevices->Location = System::Drawing::Point(20, 60);
        dgvDevices->Size = System::Drawing::Size(440, 250);
        dgvDevices->ReadOnly = true;
        dgvDevices->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        dgvDevices->AllowUserToAddRows = false;
        this->Controls->Add(dgvDevices);

        // Настраиваем колонки
        dgvDevices->Columns->Add("Model", L"Модель");
        dgvDevices->Columns->Add("IMEI", L"IMEI");
        dgvDevices->Columns->Add("SerialNumber", L"Серийный номер");

        // Кнопки
        Button^ btnSelect = gcnew Button();
        btnSelect->Text = L"Выбрать";
        btnSelect->Location = System::Drawing::Point(180, 320);
        btnSelect->Size = System::Drawing::Size(100, 30);
        btnSelect->Click += gcnew System::EventHandler(this, &DeviceSearchForm::btnSelect_Click);
        this->Controls->Add(btnSelect);

        Button^ btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = System::Drawing::Point(290, 320);
        btnCancel->Size = System::Drawing::Size(100, 30);
        btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Controls->Add(btnCancel);

        this->AcceptButton = btnSelect;
        this->CancelButton = btnCancel;
    }

    void DeviceSearchForm::LoadDevices()
    {
        dgvDevices->Rows->Clear();
        for each (DeviceData ^ device in availableDevices)
        {
            dgvDevices->Rows->Add(device->Model, device->IMEI, device->SerialNumber);
        }
    }

    void DeviceSearchForm::txtSearch_TextChanged(Object^ sender, EventArgs^ e)
    {
        String^ searchText = txtSearch->Text->ToLower();
        dgvDevices->Rows->Clear();

        for each (DeviceData ^ device in availableDevices)
        {
            if (device->Model->ToLower()->Contains(searchText) ||
                device->IMEI->ToLower()->Contains(searchText) ||
                device->SerialNumber->ToLower()->Contains(searchText))
            {
                dgvDevices->Rows->Add(device->Model, device->IMEI, device->SerialNumber);
            }
        }
    }

    void DeviceSearchForm::btnSelect_Click(Object^ sender, EventArgs^ e)
    {
        if (dgvDevices->SelectedRows->Count > 0)
        {
            selectedIndex = dgvDevices->SelectedRows[0]->Index;
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
        else
        {
            MessageBox::Show(L"Выберите устройство!",
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
}