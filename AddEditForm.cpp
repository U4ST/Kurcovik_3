#include "AddEditForm.h"

namespace DeviceManagementApp {

    void AddEditForm::InitializeComponent()
    {
        this->SuspendLayout();

        // Настройки формы
        this->Text = editingDevice ? L"Редактировать устройство" : L"Добавить устройство";
        this->Size = System::Drawing::Size(450, 550);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->Padding = System::Windows::Forms::Padding(10);
        this->BackColor = System::Drawing::Color::WhiteSmoke;
        this->Name = L"AddEditForm";

        // Заголовок
        Label^ lblTitle = gcnew Label();
        lblTitle->Text = editingDevice ? L"Редактирование устройства" : L"Добавление нового устройства";
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
        lblTitle->ForeColor = Color::DarkBlue;
        lblTitle->Location = Drawing::Point(0, 5);
        lblTitle->Size = Drawing::Size(430, 25);
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        // ID (только для редактирования)
        if (editingDevice)
        {
            lblId = gcnew Label();
            lblId->Text = String::Format("ID: {0}", editingDevice->Id);
            lblId->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Italic);
            lblId->ForeColor = Color::Gray;
            lblId->Location = Drawing::Point(10, 35);
            lblId->Size = Drawing::Size(100, 20);
            lblId->TextAlign = ContentAlignment::MiddleLeft;
            this->Controls->Add(lblId);
        }

        // Поля ввода
        int yPos = editingDevice ? 65 : 45;
        int labelWidth = 130;
        int fieldWidth = 280;
        int rowHeight = 30;

        // Производитель (обязательное поле)
        Label^ lblManuf = gcnew Label();
        lblManuf->Text = L"Производитель *:";
        lblManuf->Location = Drawing::Point(10, yPos);
        lblManuf->Size = Drawing::Size(labelWidth, 23);
        lblManuf->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblManuf);

        txtManufacturer = gcnew TextBox();
        txtManufacturer->Name = L"txtManufacturer";
        txtManufacturer->Location = Drawing::Point(150, yPos);
        txtManufacturer->Size = Drawing::Size(fieldWidth, 23);
        txtManufacturer->MaxLength = 50;
        this->Controls->Add(txtManufacturer);
        yPos += rowHeight;

        // Модель (обязательное поле)
        Label^ lblModel = gcnew Label();
        lblModel->Text = L"Модель *:";
        lblModel->Location = Drawing::Point(10, yPos);
        lblModel->Size = Drawing::Size(labelWidth, 23);
        lblModel->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblModel);

        txtModel = gcnew TextBox();
        txtModel->Name = L"txtModel";
        txtModel->Location = Drawing::Point(150, yPos);
        txtModel->Size = Drawing::Size(fieldWidth, 23);
        txtModel->MaxLength = 50;
        this->Controls->Add(txtModel);
        yPos += rowHeight;

        // Тип (обязательное поле)
        Label^ lblType = gcnew Label();
        lblType->Text = L"Тип устройства *:";
        lblType->Location = Drawing::Point(10, yPos);
        lblType->Size = Drawing::Size(labelWidth, 23);
        lblType->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblType);

        cmbType = gcnew ComboBox();
        cmbType->Name = L"cmbType";
        cmbType->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbType->Location = Drawing::Point(150, yPos);
        cmbType->Size = Drawing::Size(fieldWidth, 23);
        cmbType->Items->AddRange(gcnew cli::array<String^>(3) {
            L"Мобильное устройство",
                L"Планшет",
                L"Умные часы"
        });
        this->Controls->Add(cmbType);
        yPos += rowHeight;

        // IMEI (только цифры, 15 символов)
        Label^ lblIMEI = gcnew Label();
        lblIMEI->Text = L"IMEI номер (15 цифр):";
        lblIMEI->Location = Drawing::Point(10, yPos);
        lblIMEI->Size = Drawing::Size(labelWidth, 23);
        lblIMEI->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblIMEI);

        txtIMEI = gcnew TextBox();
        txtIMEI->Name = L"txtIMEI";
        txtIMEI->Location = Drawing::Point(150, yPos);
        txtIMEI->Size = Drawing::Size(fieldWidth, 23);
        txtIMEI->MaxLength = 15;
        txtIMEI->KeyPress += gcnew KeyPressEventHandler(this, &AddEditForm::txtIMEI_KeyPress);
        this->Controls->Add(txtIMEI);
        yPos += rowHeight;

        // Серийный номер (цифры и буквы)
        Label^ lblSerial = gcnew Label();
        lblSerial->Text = L"Серийный номер:";
        lblSerial->Location = Drawing::Point(10, yPos);
        lblSerial->Size = Drawing::Size(labelWidth, 23);
        lblSerial->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblSerial);

        txtSerialNumber = gcnew TextBox();
        txtSerialNumber->Name = L"txtSerialNumber";
        txtSerialNumber->Location = Drawing::Point(150, yPos);
        txtSerialNumber->Size = Drawing::Size(fieldWidth, 23);
        txtSerialNumber->MaxLength = 20;
        txtSerialNumber->KeyPress += gcnew KeyPressEventHandler(this, &AddEditForm::txtSerialNumber_KeyPress);
        this->Controls->Add(txtSerialNumber);
        yPos += rowHeight;

        // Статус
        Label^ lblStatus = gcnew Label();
        lblStatus->Text = L"Состояние:";
        lblStatus->Location = Drawing::Point(10, yPos);
        lblStatus->Size = Drawing::Size(labelWidth, 23);
        lblStatus->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblStatus);

        cmbStatus = gcnew ComboBox();
        cmbStatus->Name = L"cmbStatus";
        cmbStatus->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbStatus->Location = Drawing::Point(150, yPos);
        cmbStatus->Size = Drawing::Size(fieldWidth, 23);
        cmbStatus->Items->AddRange(gcnew cli::array<String^>(5) {
            L"На складе",
                L"В эксплуатации",
                L"На ремонте",
                L"Списан",
                L"Резерв"
        });
        this->Controls->Add(cmbStatus);
        yPos += rowHeight;

        // Владелец (необязательное)
        Label^ lblOwner = gcnew Label();
        lblOwner->Text = L"Владелец:";
        lblOwner->Location = Drawing::Point(10, yPos);
        lblOwner->Size = Drawing::Size(labelWidth, 23);
        lblOwner->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblOwner);

        txtOwner = gcnew TextBox();
        txtOwner->Name = L"txtOwner";
        txtOwner->Location = Drawing::Point(150, yPos);
        txtOwner->Size = Drawing::Size(fieldWidth, 23);
        txtOwner->MaxLength = 50;
        this->Controls->Add(txtOwner);
        yPos += rowHeight;

        // Цена (обязательное, только цифры)
        Label^ lblPrice = gcnew Label();
        lblPrice->Text = L"Цена ($) *:";
        lblPrice->Location = Drawing::Point(10, yPos);
        lblPrice->Size = Drawing::Size(labelWidth, 23);
        lblPrice->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblPrice);

        txtPrice = gcnew TextBox();
        txtPrice->Name = L"txtPrice";
        txtPrice->Location = Drawing::Point(150, yPos);
        txtPrice->Size = Drawing::Size(fieldWidth, 23);
        txtPrice->MaxLength = 12;
        txtPrice->KeyPress += gcnew KeyPressEventHandler(this, &AddEditForm::txtPrice_KeyPress);
        this->Controls->Add(txtPrice);
        yPos += rowHeight + 10;

        // Дополнительная информация (необязательное)
        Label^ lblInfo = gcnew Label();
        lblInfo->Text = L"Доп. информация:";
        lblInfo->Location = Drawing::Point(10, yPos);
        lblInfo->Size = Drawing::Size(labelWidth, 23);
        lblInfo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblInfo);

        txtAdditional = gcnew TextBox();
        txtAdditional->Name = L"txtAdditional";
        txtAdditional->Multiline = true;
        txtAdditional->ScrollBars = ScrollBars::Vertical;
        txtAdditional->Location = Drawing::Point(150, yPos);
        txtAdditional->Size = Drawing::Size(fieldWidth, 80);
        txtAdditional->MaxLength = 500;
        txtAdditional->AcceptsReturn = true;
        this->Controls->Add(txtAdditional);
        yPos += 100;

        // Примечание (* - обязательные поля)
        Label^ lblNote = gcnew Label();
        lblNote->Text = L"* - обязательные для заполнения поля";
        lblNote->Location = Drawing::Point(10, yPos);
        lblNote->Size = Drawing::Size(420, 20);
        lblNote->Font = gcnew Drawing::Font(L"Segoe UI", 8.0F, FontStyle::Italic);
        lblNote->ForeColor = Color::Gray;
        this->Controls->Add(lblNote);
        yPos += 25;

        // Кнопки
        btnSave = gcnew Button();
        btnSave->Text = L"Сохранить";
        btnSave->Location = Drawing::Point(140, yPos);
        btnSave->Size = Drawing::Size(100, 35);
        btnSave->BackColor = Color::LightGreen;
        btnSave->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        btnSave->Click += gcnew EventHandler(this, &AddEditForm::btnSave_Click);
        this->Controls->Add(btnSave);

        btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Drawing::Point(255, yPos);
        btnCancel->Size = Drawing::Size(100, 35);
        btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        btnCancel->BackColor = Color::LightGray;
        btnCancel->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(btnCancel);

        this->AcceptButton = btnSave;
        this->CancelButton = btnCancel;
        this->ResumeLayout(false);

        // Загрузка данных после инициализации
        LoadDataToForm();
    }

    // ЗАЩИТА ВВОДА: Только цифры для цены
    void AddEditForm::txtPrice_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);

        // Разрешаем: цифры, backspace, точка, запятая
        if (Char::IsDigit(e->KeyChar) ||
            e->KeyChar == 0x08 ||
            e->KeyChar == '.' ||
            e->KeyChar == ',')
        {
            // Проверяем, чтобы точка или запятая были только одна
            if (e->KeyChar == '.' || e->KeyChar == ',')
            {
                if (textBox->Text->Contains(".") || textBox->Text->Contains(","))
                {
                    e->Handled = true;
                    return;
                }

                // Не разрешаем точку/запятую в начале
                if (textBox->Text->Length == 0)
                {
                    e->Handled = true;
                    return;
                }
            }

            e->Handled = false;
        }
        else
        {
            e->Handled = true;
        }
    }

    // ЗАЩИТА ВВОДА: Только цифры для IMEI (15 цифр)
    void AddEditForm::txtIMEI_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);

        // Разрешаем только цифры и Backspace
        if (Char::IsDigit(e->KeyChar) || e->KeyChar == 0x08)
        {
            e->Handled = false;
        }
        else
        {
            e->Handled = true;
        }
    }

    //ЗАЩИТА ВВОДА: Буквы, цифры и дефис для серийного номера
    void AddEditForm::txtSerialNumber_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        // Разрешаем: буквы (русские и английские), цифры, дефис, Backspace
        if (Char::IsLetter(e->KeyChar) ||
            Char::IsDigit(e->KeyChar) ||
            e->KeyChar == '-' ||
            e->KeyChar == 0x08)
        {
            e->Handled = false;
        }
        else
        {
            e->Handled = true;
        }
    }

    void AddEditForm::LoadDataToForm()
    {
        if (editingDevice != nullptr)
        {
            txtManufacturer->Text = editingDevice->Manufacturer;
            txtModel->Text = editingDevice->Model;
            txtPrice->Text = editingDevice->Price.ToString("F2", CultureInfo::InvariantCulture);
            txtAdditional->Text = editingDevice->AdditionalInfo;
            txtIMEI->Text = editingDevice->IMEI;
            txtSerialNumber->Text = editingDevice->SerialNumber;
            txtOwner->Text = editingDevice->Owner;

            // Установка типа
            if (cmbType != nullptr && cmbType->Items->Count > 0)
            {
                bool found = false;
                for each (String ^ item in cmbType->Items)
                {
                    if (item->Equals(editingDevice->Type))
                    {
                        cmbType->SelectedItem = item;
                        found = true;
                        break;
                    }
                }
                if (!found && cmbType->Items->Count > 0)
                    cmbType->SelectedIndex = 0;
            }

            // Установка статуса
            if (cmbStatus != nullptr && cmbStatus->Items->Count > 0)
            {
                bool found = false;
                for each (String ^ item in cmbStatus->Items)
                {
                    if (item->Equals(editingDevice->Status))
                    {
                        cmbStatus->SelectedItem = item;
                        found = true;
                        break;
                    }
                }
                if (!found && cmbStatus->Items->Count > 0)
                    cmbStatus->SelectedIndex = 0;
            }

            txtManufacturer->SelectAll();
            txtManufacturer->Focus();
        }
        else
        {
            // Установка значений по умолчанию для нового устройства
            if (cmbType != nullptr && cmbType->Items->Count > 0)
                cmbType->SelectedIndex = 0;

            if (cmbStatus != nullptr && cmbStatus->Items->Count > 0)
                cmbStatus->SelectedIndex = 0;

            txtManufacturer->Focus();
        }
    }

    void AddEditForm::btnSave_Click(Object^ sender, EventArgs^ e)
    {
       
        if (!ValidateInput())
            return;

        SaveFormData();
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }

    bool AddEditForm::ValidateInput()
    {
        List<String^>^ errors = gcnew List<String^>();

        // Проверка обязательных полей
        if (String::IsNullOrWhiteSpace(txtManufacturer->Text))
        {
            errors->Add(L"Поле 'Производитель' обязательно для заполнения");
        }

        if (String::IsNullOrWhiteSpace(txtModel->Text))
        {
            errors->Add(L"Поле 'Модель' обязательно для заполнения");
        }

        if (cmbType->SelectedIndex == -1)
        {
            errors->Add(L"Выберите тип устройства");
        }

        // Проверка IMEI (если заполнен)
        if (!String::IsNullOrWhiteSpace(txtIMEI->Text))
        {
            if (txtIMEI->Text->Length != 15)
            {
                errors->Add(L"IMEI должен содержать ровно 15 цифр");
            }
            else
            {
                // Проверка, что все символы - цифры
                for each (Char c in txtIMEI->Text)
                {
                    if (!Char::IsDigit(c))
                    {
                        errors->Add(L"IMEI может содержать только цифры");
                        break;
                    }
                }
            }
        }

        // Проверка серийного номера
        if (String::IsNullOrWhiteSpace(txtSerialNumber->Text))
        {
            errors->Add(L"Поле 'Серийный номер' обязательно для заполнения");
        }

        if (cmbStatus->SelectedIndex == -1)
        {
            errors->Add(L"Выберите состояние устройства");
        }

        // Проверка цены
        if (String::IsNullOrWhiteSpace(txtPrice->Text))
        {
            errors->Add(L"Поле 'Цена' обязательно для заполнения");
        }
        else
        {
            double priceValue;
            String^ priceText = txtPrice->Text->Replace(",", ".");

            if (!Double::TryParse(priceText, NumberStyles::Float, CultureInfo::InvariantCulture, priceValue))
            {
                errors->Add(L"Введите корректное числовое значение для цены");
            }
            else if (priceValue <= 0)
            {
                errors->Add(L"Цена должна быть больше 0");
            }
        }

        // Если есть ошибки, показываем их все сразу
        if (errors->Count > 0)
        {
            String^ errorMessage = L"Обнаружены следующие ошибки:\n\n";
            for each (String ^ error in errors)
            {
                errorMessage += L"• " + error + L"\n";
            }

            MessageBox::Show(errorMessage, L"Ошибки ввода",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);

            
            if (String::IsNullOrWhiteSpace(txtManufacturer->Text))
                txtManufacturer->Focus();
            else if (String::IsNullOrWhiteSpace(txtModel->Text))
                txtModel->Focus();
            else if (cmbType->SelectedIndex == -1)
                cmbType->Focus();
            else if (String::IsNullOrWhiteSpace(txtSerialNumber->Text))
                txtSerialNumber->Focus();
            else if (cmbStatus->SelectedIndex == -1)
                cmbStatus->Focus();
            else if (String::IsNullOrWhiteSpace(txtPrice->Text))
                txtPrice->Focus();

            return false;
        }

        return true;
    }

    void AddEditForm::SaveFormData()
    {
        _manufacturer = txtManufacturer->Text->Trim();
        _model = txtModel->Text->Trim();
        _type = cmbType->Text;

        String^ priceText = txtPrice->Text->Replace(",", ".");
        _price = Double::Parse(priceText, CultureInfo::InvariantCulture);

        _additionalInfo = txtAdditional->Text->Trim();
        _imei = txtIMEI->Text->Trim();
        _serialNumber = txtSerialNumber->Text->Trim();
        _status = cmbStatus->Text;
        _owner = txtOwner->Text->Trim();
    }

    void AddEditForm::ShowError(String^ message)
    {
        MessageBox::Show(message, L"Ошибка ввода",
            MessageBoxButtons::OK,
            MessageBoxIcon::Warning);
    }
}