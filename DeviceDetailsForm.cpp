#include "DeviceDetailsForm.h"
#include "AddEditForm.h"
#include "MainForm.h"  

namespace DeviceManagementApp {

    void DeviceDetailsForm::InitializeComponent()
    {
        this->SuspendLayout();

        this->Text = L"Детальная информация об устройстве";
        this->Size = System::Drawing::Size(500, 500);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = System::Drawing::Color::WhiteSmoke;

        // Заголовок
        lblTitle = gcnew Label();
        lblTitle->Text = L"Информация об устройстве";
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
        lblTitle->ForeColor = Color::DarkBlue;
        lblTitle->Location = Drawing::Point(10, 10);
        lblTitle->Size = Drawing::Size(460, 30);
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        int yPos = 50;
        int labelWidth = 150;
        int valueWidth = 300;

        // Производитель
        Label^ lblManufTitle = gcnew Label();
        lblManufTitle->Text = L"Производитель:";
        lblManufTitle->Location = Drawing::Point(10, yPos);
        lblManufTitle->Size = Drawing::Size(labelWidth, 25);
        lblManufTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblManufTitle);

        lblManufacturer = gcnew Label();
        lblManufacturer->Location = Drawing::Point(labelWidth + 20, yPos);
        lblManufacturer->Size = Drawing::Size(valueWidth, 25);
        lblManufacturer->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblManufacturer);
        yPos += 30;

        // Модель
        Label^ lblModelTitle = gcnew Label();
        lblModelTitle->Text = L"Модель:";
        lblModelTitle->Location = Drawing::Point(10, yPos);
        lblModelTitle->Size = Drawing::Size(labelWidth, 25);
        lblModelTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblModelTitle);

        lblModel = gcnew Label();
        lblModel->Location = Drawing::Point(labelWidth + 20, yPos);
        lblModel->Size = Drawing::Size(valueWidth, 25);
        lblModel->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblModel);
        yPos += 30;

        // Тип
        Label^ lblTypeTitle = gcnew Label();
        lblTypeTitle->Text = L"Тип устройства:";
        lblTypeTitle->Location = Drawing::Point(10, yPos);
        lblTypeTitle->Size = Drawing::Size(labelWidth, 25);
        lblTypeTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblTypeTitle);

        lblType = gcnew Label();
        lblType->Location = Drawing::Point(labelWidth + 20, yPos);
        lblType->Size = Drawing::Size(valueWidth, 25);
        lblType->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblType);
        yPos += 30;

        // Цена
        Label^ lblPriceTitle = gcnew Label();
        lblPriceTitle->Text = L"Цена ($):";
        lblPriceTitle->Location = Drawing::Point(10, yPos);
        lblPriceTitle->Size = Drawing::Size(labelWidth, 25);
        lblPriceTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblPriceTitle);

        lblPrice = gcnew Label();
        lblPrice->Location = Drawing::Point(labelWidth + 20, yPos);
        lblPrice->Size = Drawing::Size(valueWidth, 25);
        lblPrice->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblPrice);
        yPos += 30;

        // IMEI
        Label^ lblIMEITitle = gcnew Label();
        lblIMEITitle->Text = L"IMEI номер:";
        lblIMEITitle->Location = Drawing::Point(10, yPos);
        lblIMEITitle->Size = Drawing::Size(labelWidth, 25);
        lblIMEITitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblIMEITitle);

        lblIMEI = gcnew Label();
        lblIMEI->Location = Drawing::Point(labelWidth + 20, yPos);
        lblIMEI->Size = Drawing::Size(valueWidth, 25);
        lblIMEI->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblIMEI);
        yPos += 30;

        // Серийный номер
        Label^ lblSerialTitle = gcnew Label();
        lblSerialTitle->Text = L"Серийный номер:";
        lblSerialTitle->Location = Drawing::Point(10, yPos);
        lblSerialTitle->Size = Drawing::Size(labelWidth, 25);
        lblSerialTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblSerialTitle);

        lblSerialNumber = gcnew Label();
        lblSerialNumber->Location = Drawing::Point(labelWidth + 20, yPos);
        lblSerialNumber->Size = Drawing::Size(valueWidth, 25);
        lblSerialNumber->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblSerialNumber);
        yPos += 30;

        // Состояние
        Label^ lblStatusTitle = gcnew Label();
        lblStatusTitle->Text = L"Состояние:";
        lblStatusTitle->Location = Drawing::Point(10, yPos);
        lblStatusTitle->Size = Drawing::Size(labelWidth, 25);
        lblStatusTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblStatusTitle);

        lblStatus = gcnew Label();
        lblStatus->Location = Drawing::Point(labelWidth + 20, yPos);
        lblStatus->Size = Drawing::Size(valueWidth, 25);
        lblStatus->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblStatus);
        yPos += 30;

        // Владелец
        Label^ lblOwnerTitle = gcnew Label();
        lblOwnerTitle->Text = L"Владелец:";
        lblOwnerTitle->Location = Drawing::Point(10, yPos);
        lblOwnerTitle->Size = Drawing::Size(labelWidth, 25);
        lblOwnerTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblOwnerTitle);

        lblOwner = gcnew Label();
        lblOwner->Location = Drawing::Point(labelWidth + 20, yPos);
        lblOwner->Size = Drawing::Size(valueWidth, 25);
        lblOwner->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblOwner);
        yPos += 30;

        // Доп. информация
        Label^ lblInfoTitle = gcnew Label();
        lblInfoTitle->Text = L"Доп. информация:";
        lblInfoTitle->Location = Drawing::Point(10, yPos);
        lblInfoTitle->Size = Drawing::Size(labelWidth, 25);
        lblInfoTitle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        this->Controls->Add(lblInfoTitle);
        yPos += 30;

        lblAdditionalInfo = gcnew Label();
        lblAdditionalInfo->Location = Drawing::Point(10, yPos);
        lblAdditionalInfo->Size = Drawing::Size(460, 80);
        lblAdditionalInfo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        lblAdditionalInfo->BorderStyle = BorderStyle::FixedSingle;
        lblAdditionalInfo->Padding = System::Windows::Forms::Padding(5);
        this->Controls->Add(lblAdditionalInfo);
        yPos += 90;

        // Кнопки
        btnEdit = gcnew Button();
        btnEdit->Text = L"Редактировать";
        btnEdit->Location = Drawing::Point(100, yPos);
        btnEdit->Size = Drawing::Size(120, 35);
        btnEdit->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnEdit->BackColor = Color::LightYellow;
        btnEdit->Click += gcnew EventHandler(this, &DeviceDetailsForm::btnEdit_Click);
        this->Controls->Add(btnEdit);

        btnClose = gcnew Button();
        btnClose->Text = L"Закрыть";
        btnClose->Location = Drawing::Point(250, yPos);
        btnClose->Size = Drawing::Size(120, 35);
        btnClose->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnClose->BackColor = Color::LightGray;
        btnClose->Click += gcnew EventHandler(this, &DeviceDetailsForm::btnClose_Click);
        this->Controls->Add(btnClose);

        this->ResumeLayout(false);
    }

    void DeviceDetailsForm::LoadDeviceDetails()
    {
        if (device != nullptr)
        {
            lblTitle->Text = String::Format(L"Устройство #{0}", device->Id);
            lblManufacturer->Text = device->Manufacturer;
            lblModel->Text = device->Model;
            lblType->Text = device->Type;
            lblPrice->Text = String::Format(L"${0:F2}", device->Price);
            lblIMEI->Text = String::IsNullOrEmpty(device->IMEI) ? L"Не указан" : device->IMEI;
            lblSerialNumber->Text = String::IsNullOrEmpty(device->SerialNumber) ? L"Не указан" : device->SerialNumber;
            lblStatus->Text = device->Status;
            lblOwner->Text = String::IsNullOrEmpty(device->Owner) ? L"Не закреплено" : device->Owner;
            lblAdditionalInfo->Text = device->AdditionalInfo;
        }
    }

    void DeviceDetailsForm::btnClose_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }

    void DeviceDetailsForm::btnEdit_Click(Object^ sender, EventArgs^ e)
    {
        AddEditForm^ editForm = gcnew AddEditForm(device);
        if (editForm->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
        {
            // Обновляем устройство
            device->Manufacturer = editForm->Manufacturer;
            device->Model = editForm->Model;
            device->Type = editForm->Type;
            device->Price = editForm->Price;
            device->AdditionalInfo = editForm->AdditionalInfo;
            device->IMEI = editForm->IMEI;
            device->SerialNumber = editForm->SerialNumber;
            device->Status = editForm->Status;
            device->Owner = editForm->Owner;

            LoadDeviceDetails();
        }
    }
}