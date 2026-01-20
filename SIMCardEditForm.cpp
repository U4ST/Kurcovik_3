#include "stdafx.h"
#include "SIMCardEditForm.h"

namespace DeviceManagementApp {

    void SIMCardEditForm::InitializeComponent()
    {
        this->Text = (simCard->Id == 0) ? L"Добавление SIM-карты" : L"Редактирование SIM-карты";
        this->Size = System::Drawing::Size(500, 550);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = Color::WhiteSmoke;

        Label^ lblTitle = gcnew Label();
        lblTitle->Text = this->Text;
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
        lblTitle->Location = Point(20, 20);
        lblTitle->Size = Drawing::Size(450, 30);
        lblTitle->ForeColor = Color::DarkBlue;
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        int yPos = 60;
        int labelWidth = 150;
        int fieldWidth = 300;

        // Номер телефона
        Label^ lblPhone = gcnew Label();
        lblPhone->Text = L"Номер телефона:";
        lblPhone->Location = Point(20, yPos);
        lblPhone->Size = Drawing::Size(labelWidth, 25);
        lblPhone->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblPhone);

        txtPhoneNumber = gcnew TextBox();
        txtPhoneNumber->Location = Point(180, yPos);
        txtPhoneNumber->Size = Drawing::Size(fieldWidth, 25);
        txtPhoneNumber->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(txtPhoneNumber);

        txtPhoneNumber->Leave += gcnew EventHandler(this, &SIMCardEditForm::txtPhoneNumber_Leave);

        yPos += 35;

        // Оператор
        Label^ lblOperator = gcnew Label();
        lblOperator->Text = L"Оператор:";
        lblOperator->Location = Point(20, yPos);
        lblOperator->Size = Drawing::Size(labelWidth, 25);
        lblOperator->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblOperator);

        cmbOperator = gcnew ComboBox();
        cmbOperator->Location = Point(180, yPos);
        cmbOperator->Size = Drawing::Size(fieldWidth, 25);
        cmbOperator->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbOperator->Items->AddRange(gcnew cli::array<String^>(4) {
            L"МТС", L"Билайн", L"МегаФон", L"Теле2"
        });
        this->Controls->Add(cmbOperator);

        yPos += 35;

        // Тарифный план
        Label^ lblTariff = gcnew Label();
        lblTariff->Text = L"Тарифный план:";
        lblTariff->Location = Point(20, yPos);
        lblTariff->Size = Drawing::Size(labelWidth, 25);
        lblTariff->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblTariff);

        txtTariffPlan = gcnew TextBox();
        txtTariffPlan->Location = Point(180, yPos);
        txtTariffPlan->Size = Drawing::Size(fieldWidth, 25);
        txtTariffPlan->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(txtTariffPlan);

        yPos += 35;

        // Ежемесячная стоимость
        Label^ lblCost = gcnew Label();
        lblCost->Text = L"Ежемесячная стоимость ($):";
        lblCost->Location = Point(20, yPos);
        lblCost->Size = Drawing::Size(labelWidth, 25);
        lblCost->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblCost);

        txtMonthlyCost = gcnew TextBox();
        txtMonthlyCost->Location = Point(180, yPos);
        txtMonthlyCost->Size = Drawing::Size(fieldWidth, 25);
        txtMonthlyCost->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtMonthlyCost->KeyPress += gcnew KeyPressEventHandler(this, &SIMCardEditForm::txtMonthlyCost_KeyPress);
        this->Controls->Add(txtMonthlyCost);

        yPos += 35;

        // Лимит трафика
        Label^ lblData = gcnew Label();
        lblData->Text = L"Лимит трафика (ГБ):";
        lblData->Location = Point(20, yPos);
        lblData->Size = Drawing::Size(labelWidth, 25);
        lblData->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblData);

        txtDataLimit = gcnew TextBox();
        txtDataLimit->Location = Point(180, yPos);
        txtDataLimit->Size = Drawing::Size(fieldWidth, 25);
        txtDataLimit->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtDataLimit->KeyPress += gcnew KeyPressEventHandler(this, &SIMCardEditForm::txtDataLimit_KeyPress);
        this->Controls->Add(txtDataLimit);

        yPos += 35;

        // Дата окончания
        Label^ lblExpiry = gcnew Label();
        lblExpiry->Text = L"Дата окончания контракта:";
        lblExpiry->Location = Point(20, yPos);
        lblExpiry->Size = Drawing::Size(labelWidth, 25);
        lblExpiry->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblExpiry);

        dtpExpiryDate = gcnew DateTimePicker();
        dtpExpiryDate->Location = Point(180, yPos);
        dtpExpiryDate->Size = Drawing::Size(fieldWidth, 25);
        dtpExpiryDate->Format = DateTimePickerFormat::Short;
        this->Controls->Add(dtpExpiryDate);

        yPos += 35;

        // Активность
        Label^ lblActive = gcnew Label();
        lblActive->Text = L"Активна:";
        lblActive->Location = Point(20, yPos);
        lblActive->Size = Drawing::Size(labelWidth, 25);
        lblActive->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblActive);

        chkActive = gcnew CheckBox();
        chkActive->Location = Point(180, yPos);
        chkActive->Size = Drawing::Size(100, 25);
        chkActive->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(chkActive);

        yPos += 35;

        //IMEI
        Label^ lblIMEI = gcnew Label();
        lblIMEI->Text = L"IMEI устройства:";
        lblIMEI->Location = Point(20, yPos);
        lblIMEI->Size = Drawing::Size(labelWidth, 25);
        lblIMEI->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblIMEI);

        txtDeviceIMEI = gcnew TextBox();
        txtDeviceIMEI->Location = Point(180, yPos);
        txtDeviceIMEI->Size = Drawing::Size(fieldWidth, 25);
        txtDeviceIMEI->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(txtDeviceIMEI);

        txtDeviceIMEI->Leave += gcnew EventHandler(this, &SIMCardEditForm::txtDeviceIMEI_Leave);

        yPos += 35;

        // Примечания
        Label^ lblNotes = gcnew Label();
        lblNotes->Text = L"Примечания:";
        lblNotes->Location = Point(20, yPos);
        lblNotes->Size = Drawing::Size(labelWidth, 25);
        lblNotes->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblNotes);

        txtNotes = gcnew TextBox();
        txtNotes->Location = Point(180, yPos);
        txtNotes->Multiline = true;
        txtNotes->Size = Drawing::Size(fieldWidth, 60);
        txtNotes->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtNotes->ScrollBars = ScrollBars::Vertical;
        this->Controls->Add(txtNotes);

        yPos += 70;

        // Кнопки
        btnSave = gcnew Button();
        btnSave->Text = L"Сохранить";
        btnSave->Location = Point(150, yPos);
        btnSave->Size = Drawing::Size(120, 35);
        btnSave->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
        btnSave->BackColor = Color::LightGreen;
        btnSave->Click += gcnew EventHandler(this, &SIMCardEditForm::btnSave_Click);
        this->Controls->Add(btnSave);

        btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(280, yPos);
        btnCancel->Size = Drawing::Size(120, 35);
        btnCancel->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
        btnCancel->BackColor = Color::LightGray;
        btnCancel->Click += gcnew EventHandler(this, &SIMCardEditForm::btnCancel_Click);
        this->Controls->Add(btnCancel);

        this->AcceptButton = btnSave;
        this->CancelButton = btnCancel;

        txtPhoneNumber->KeyPress += gcnew KeyPressEventHandler(this, &SIMCardEditForm::txtPhoneNumber_KeyPress);

        txtDeviceIMEI->KeyPress += gcnew KeyPressEventHandler(this, &SIMCardEditForm::txtDeviceIMEI_KeyPress);

        txtMonthlyCost->Leave += gcnew EventHandler(this, &SIMCardEditForm::txtMonthlyCost_Leave);
        txtDataLimit->Leave += gcnew EventHandler(this, &SIMCardEditForm::txtDataLimit_Leave);
    }

    void SIMCardEditForm::LoadDataToForm()
    {
        txtPhoneNumber->Text = simCard->PhoneNumber;
        txtTariffPlan->Text = simCard->TariffPlan;
        txtMonthlyCost->Text = simCard->MonthlyCost.ToString();
        txtDataLimit->Text = simCard->DataLimitGB.ToString();
        dtpExpiryDate->Value = simCard->ExpiryDate;
        chkActive->Checked = simCard->IsActive;
        txtDeviceIMEI->Text = simCard->DeviceIMEI;
        txtNotes->Text = simCard->Notes;

        // Установка оператора
        if (!String::IsNullOrEmpty(simCard->Operator))
        {
            for each (String ^ item in cmbOperator->Items)
            {
                if (item == simCard->Operator)
                {
                    cmbOperator->SelectedItem = item;
                    break;
                }
            }
        }

        if (cmbOperator->SelectedIndex == -1 && cmbOperator->Items->Count > 0)
            cmbOperator->SelectedIndex = 0;
    }

    void SIMCardEditForm::btnSave_Click(Object^ sender, EventArgs^ e)
    {
        // Проверка номера телефона
        if (String::IsNullOrWhiteSpace(txtPhoneNumber->Text))
        {
            MessageBox::Show(L"Введите номер телефона!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtPhoneNumber->Focus();
            return;
        }

        // Проверка формата номера телефона
        String^ phone = txtPhoneNumber->Text->Trim();

        // Проверяем, что номер начинается с + и содержит только цифры после +
        if (!phone->StartsWith("+"))
        {
            MessageBox::Show(L"Номер должен начинаться с '+'!",
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtPhoneNumber->Focus();
            return;
        }

        // Проверка длины номера: минимум + и 10 цифр, максимум + и 15 цифр
        int digitCount = 0;
        for (int i = 1; i < phone->Length; i++)
        {
            if (!Char::IsDigit(phone[i]))
            {
                MessageBox::Show(L"Номер должен содержать только цифры после '+'!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtPhoneNumber->Focus();
                return;
            }
            digitCount++;
        }

        if (digitCount < 10 || digitCount > 15)
        {
            MessageBox::Show(L"Номер должен содержать от 10 до 15 цифр после '+'!",
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtPhoneNumber->Focus();
            return;
        }

        //Проверка оператора
        if (cmbOperator->SelectedIndex == -1 || String::IsNullOrWhiteSpace(cmbOperator->Text))
        {
            MessageBox::Show(L"Выберите оператора!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            cmbOperator->Focus();
            return;
        }

        //Проверка тарифного плана
        if (String::IsNullOrWhiteSpace(txtTariffPlan->Text))
        {
            MessageBox::Show(L"Введите тарифный план!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtTariffPlan->Focus();
            return;
        }

        //Проверка стоимости
        double cost;
        if (!Double::TryParse(txtMonthlyCost->Text, cost) || cost < 0)
        {
            MessageBox::Show(L"Введите корректную стоимость (неотрицательное число)!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtMonthlyCost->Focus();
            return;
        }

        //Проверка лимита трафика
        int dataLimit;
        if (!Int32::TryParse(txtDataLimit->Text, dataLimit) || dataLimit < 0)
        {
            MessageBox::Show(L"Введите корректный лимит трафика (неотрицательное целое число)!", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtDataLimit->Focus();
            return;
        }

        //Проверка IMEI (если указан)
        if (!String::IsNullOrWhiteSpace(txtDeviceIMEI->Text))
        {
            String^ imei = txtDeviceIMEI->Text->Trim();

            // IMEI должен содержать только цифры
            for (int i = 0; i < imei->Length; i++)
            {
                if (!Char::IsDigit(imei[i]))
                {
                    MessageBox::Show(L"IMEI должен содержать только цифры!", L"Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    txtDeviceIMEI->Focus();
                    return;
                }
            }

            // Стандартная длина IMEI - 15 цифр
            if (imei->Length != 15)
            {
                MessageBox::Show(L"IMEI должен содержать 15 цифр!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtDeviceIMEI->Focus();
                return;
            }
        }

        //сохраняем данные
        simCard->PhoneNumber = phone;
        simCard->Operator = cmbOperator->SelectedItem->ToString();
        simCard->TariffPlan = txtTariffPlan->Text;
        simCard->MonthlyCost = cost;
        simCard->DataLimitGB = dataLimit;
        simCard->ExpiryDate = dtpExpiryDate->Value;
        simCard->IsActive = chkActive->Checked;
        simCard->DeviceIMEI = txtDeviceIMEI->Text;
        simCard->Notes = txtNotes->Text;

        if (simCard->Id == 0)
            simCard->ActivationDate = DateTime::Now;

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }

    void SIMCardEditForm::btnCancel_Click(Object^ sender, EventArgs^ e)
    {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    void SIMCardEditForm::txtMonthlyCost_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        if (!Char::IsDigit(e->KeyChar) && e->KeyChar != '.' && e->KeyChar != 0x08)
        {
            e->Handled = true;
        }
    }

    void SIMCardEditForm::txtDataLimit_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
        {
            e->Handled = true;
        }
    }

    void SIMCardEditForm::txtPhoneNumber_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);
        String^ currentText = textBox->Text;

        if (e->KeyChar == 0x08)
            return;

        // Разрешаем + только в начале
        if (currentText->Length == 0 && e->KeyChar == '+')
            return;

        // Если уже есть +, разрешаем только цифры
        if (currentText->StartsWith("+"))
        {
            if (!Char::IsDigit(e->KeyChar))
            {
                e->Handled = true;
                return;
            }

            // Ограничение длины: максимум 15 цифр после +
            int digitsAfterPlus = 0;
            for (int i = 1; i < currentText->Length; i++)
            {
                if (Char::IsDigit(currentText[i]))
                    digitsAfterPlus++;
            }

            if (digitsAfterPlus >= 15)
            {
                e->Handled = true;
                return;
            }
        }
        else
        {
            // Если нет +, первый символ должен быть +
            if (e->KeyChar != '+')
            {
                e->Handled = true;
                return;
            }
        }
    }

    void SIMCardEditForm::txtDeviceIMEI_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        // Разрешаем только цифры и backspace
        if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
        {
            e->Handled = true;
        }
    }

    void SIMCardEditForm::txtPhoneNumber_Leave(Object^ sender, EventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);
        String^ phone = textBox->Text->Trim();

        if (!String::IsNullOrEmpty(phone))
        {
            // Автоматически добавляем +, если его нет
            if (!phone->StartsWith("+"))
            {
                phone = "+" + phone;
                textBox->Text = phone;
            }

            // Удаляем все нецифровые символы после +
            String^ cleaned = "+";
            for (int i = 1; i < phone->Length; i++)
            {
                if (Char::IsDigit(phone[i]))
                    cleaned += phone[i];
            }

            if (cleaned != phone)
            {
                textBox->Text = cleaned;
            }

            // Проверяем длину
            int digitCount = cleaned->Length - 1;
            if (digitCount > 0 && (digitCount < 10 || digitCount > 15))
            {
                MessageBox::Show(L"Номер должен содержать от 10 до 15 цифр после '+'!",
                    L"Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBox->Focus();
            }
        }
    }

    void SIMCardEditForm::txtDeviceIMEI_Leave(Object^ sender, EventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);
        String^ imei = textBox->Text->Trim();

        if (!String::IsNullOrEmpty(imei))
        {
            // Удаляем все нецифровые символы
            String^ cleaned = "";
            for (int i = 0; i < imei->Length; i++)
            {
                if (Char::IsDigit(imei[i]))
                    cleaned += imei[i];
            }

            if (cleaned != imei)
            {
                textBox->Text = cleaned;
            }

            // Проверяем длину
            if (cleaned->Length > 0 && cleaned->Length != 15)
            {
                MessageBox::Show(L"IMEI должен содержать 15 цифр!",
                    L"Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBox->Focus();
            }
        }
    }

    void SIMCardEditForm::txtMonthlyCost_Leave(Object^ sender, EventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);
        String^ text = textBox->Text->Trim();

        if (!String::IsNullOrEmpty(text))
        {
            double value;
            if (!Double::TryParse(text, value) || value < 0)
            {
                MessageBox::Show(L"Введите корректную стоимость (неотрицательное число)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBox->Focus();
            }
        }
    }

    void SIMCardEditForm::txtDataLimit_Leave(Object^ sender, EventArgs^ e)
    {
        TextBox^ textBox = safe_cast<TextBox^>(sender);
        String^ text = textBox->Text->Trim();

        if (!String::IsNullOrEmpty(text))
        {
            int value;
            if (!Int32::TryParse(text, value) || value < 0)
            {
                MessageBox::Show(L"Введите корректный лимит трафика (неотрицательное целое число)!",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBox->Focus();
            }
        }
    }
}