#include "stdafx.h"
#include "SIMCardsForm.h"
#include <msclr/marshal_cppstd.h>

namespace DeviceManagementApp {

    SIMCardInfoForm::SIMCardInfoForm(SIMCardData^ simCard)
    {
        card = simCard;
        InitializeComponent();
    }

    void SIMCardInfoForm::InitializeComponent()
    {
        this->Text = L"Информация о SIM-карте";
        this->Size = System::Drawing::Size(400, 350);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = System::Drawing::Color::WhiteSmoke;

        // Заголовок
        Label^ lblTitle = gcnew Label();
        lblTitle->Text = L"Детальная информация";
        lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold);
        lblTitle->Location = System::Drawing::Point(20, 15);
        lblTitle->Size = System::Drawing::Size(350, 25);
        lblTitle->ForeColor = System::Drawing::Color::DarkBlue;
        lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        // Отображаем информацию
        RichTextBox^ rtbInfo = gcnew RichTextBox();
        rtbInfo->Location = System::Drawing::Point(20, 50);
        rtbInfo->Size = System::Drawing::Size(340, 220);
        rtbInfo->ReadOnly = true;
        rtbInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
        rtbInfo->BackColor = System::Drawing::Color::White;
        rtbInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

        // Формируем информацию
        String^ info = String::Format(
            L"Номер телефона: {0}\n" +
            L"Оператор связи: {1}\n" +
            L"Тарифный план: {2}\n" +
            L"Ежемесячная стоимость: ${3:F2}\n" +
            L"Трафик: {4}/{5} ГБ ({6}%)\n" +
            L"Минуты: {7}/{8}\n" +
            L"SMS: {9}/{10}\n" +
            L"Статус: {11}\n" +
            L"IMEI устройства: {12}\n" +
            L"Модель устройства: {13}\n" +
            L"Дата активации: {14:dd.MM.yyyy}\n" +
            L"Дата окончания: {15:dd.MM.yyyy}\n" +
            L"Осталось дней: {16}",
            card->PhoneNumber,
            card->Operator,
            card->TariffPlan,
            card->MonthlyCost,
            card->DataUsedGB,
            card->DataLimitGB,
            card->DataLimitGB > 0 ? (int)((double)card->DataUsedGB / card->DataLimitGB * 100) : 0,
            card->MinutesUsed,
            card->MinutesLimit,
            card->SMSUsed,
            card->SMSLimit,
            card->IsActive ? L"АКТИВНА ✓" : L"НЕАКТИВНА ✗",
            String::IsNullOrEmpty(card->DeviceIMEI) ? L"Не указано" : card->DeviceIMEI,
            String::IsNullOrEmpty(card->DeviceModel) ? L"Не привязано" : card->DeviceModel,
            card->ActivationDate,
            card->ExpiryDate,
            (card->ExpiryDate - DateTime::Today).Days
        );

        // Добавляем примечания, если они есть
        if (!String::IsNullOrEmpty(card->Notes))
        {
            info += L"\n\nПримечания:\n" + card->Notes;
        }

        rtbInfo->Text = info;
        this->Controls->Add(rtbInfo);

        // Кнопка закрытия
        Button^ btnClose = gcnew Button();
        btnClose->Text = L"Закрыть";
        btnClose->Location = System::Drawing::Point(150, 280);
        btnClose->Size = System::Drawing::Size(100, 30);
        btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Bold);
        btnClose->BackColor = System::Drawing::Color::LightGray;
        btnClose->Click += gcnew System::EventHandler(this, &SIMCardInfoForm::btnClose_Click);
        this->Controls->Add(btnClose);

        this->AcceptButton = btnClose;
    }

    void SIMCardInfoForm::btnClose_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }

    void SIMCardsForm::InitializeComponent()
    {
        this->Text = L"SIM-карты и тарифы";
        this->Size = System::Drawing::Size(1100, 600);
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        this->BackColor = System::Drawing::Color::WhiteSmoke;

        lblTitle = gcnew Label();
        lblTitle->Text = L"Управление SIM-картами";
        lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold);
        lblTitle->Location = System::Drawing::Point(20, 20);
        lblTitle->Size = System::Drawing::Size(400, 30);
        lblTitle->ForeColor = System::Drawing::Color::DarkBlue;
        this->Controls->Add(lblTitle);

        // Панель предупреждений
        pnlWarnings = gcnew Panel();
        pnlWarnings->Location = System::Drawing::Point(20, 60);
        pnlWarnings->Size = System::Drawing::Size(1050, 50);
        pnlWarnings->BackColor = System::Drawing::Color::LightYellow;
        pnlWarnings->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        pnlWarnings->Visible = false;
        this->Controls->Add(pnlWarnings);

        lblWarnings = gcnew Label();
        lblWarnings->Location = System::Drawing::Point(10, 10);
        lblWarnings->Size = System::Drawing::Size(1030, 30);
        lblWarnings->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Bold);
        lblWarnings->ForeColor = System::Drawing::Color::DarkRed;
        lblWarnings->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
        pnlWarnings->Controls->Add(lblWarnings);

        // DataGridView
        dgvSIMCards = gcnew DataGridView();
        dgvSIMCards->Location = System::Drawing::Point(20, 120);
        dgvSIMCards->Size = System::Drawing::Size(1050, 350);
        dgvSIMCards->ReadOnly = true;
        dgvSIMCards->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        dgvSIMCards->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
        dgvSIMCards->AllowUserToAddRows = false;
        dgvSIMCards->RowHeadersVisible = false;
        dgvSIMCards->BackgroundColor = System::Drawing::Color::White;

        // обработчик двойного щелчка
        dgvSIMCards->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(
            this, &SIMCardsForm::dgvSIMCards_CellDoubleClick);

        this->Controls->Add(dgvSIMCards);

        // Кнопки
        int yPos = 490;
        int xPos = 20;
        int buttonWidth = 120;
        int buttonHeight = 35;

        btnAdd = gcnew Button();
        btnAdd->Text = L"Добавить";
        btnAdd->Location = System::Drawing::Point(xPos, yPos);
        btnAdd->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnAdd->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, System::Drawing::FontStyle::Bold);
        btnAdd->BackColor = System::Drawing::Color::LightGreen;
        btnAdd->Click += gcnew System::EventHandler(this, &SIMCardsForm::btnAdd_Click);
        this->Controls->Add(btnAdd);

        btnEdit = gcnew Button();
        btnEdit->Text = L"Изменить";
        btnEdit->Location = System::Drawing::Point(xPos + 130, yPos);
        btnEdit->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnEdit->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
        btnEdit->BackColor = System::Drawing::Color::LightYellow;
        btnEdit->Click += gcnew System::EventHandler(this, &SIMCardsForm::btnEdit_Click);
        this->Controls->Add(btnEdit);

        btnDelete = gcnew Button();
        btnDelete->Text = L"Удалить";
        btnDelete->Location = System::Drawing::Point(xPos + 260, yPos);
        btnDelete->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnDelete->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
        btnDelete->BackColor = System::Drawing::Color::LightCoral;
        btnDelete->Click += gcnew System::EventHandler(this, &SIMCardsForm::btnDelete_Click);
        this->Controls->Add(btnDelete);

        btnRefresh = gcnew Button();
        btnRefresh->Text = L"Обновить";
        btnRefresh->Location = System::Drawing::Point(xPos + 390, yPos);
        btnRefresh->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
        btnRefresh->BackColor = System::Drawing::Color::LightGray;
        btnRefresh->Click += gcnew System::EventHandler(this, &SIMCardsForm::btnRefresh_Click);
        this->Controls->Add(btnRefresh);

        btnClose = gcnew Button();
        btnClose->Text = L"Закрыть";
        btnClose->Location = System::Drawing::Point(950, yPos);
        btnClose->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
        btnClose->BackColor = System::Drawing::Color::LightCoral;
        btnClose->Click += gcnew System::EventHandler(this, &SIMCardsForm::btnClose_Click);
        this->Controls->Add(btnClose);

        SetupDataGridView();
    }

    void SIMCardsForm::SetupDataGridView()
    {
        dgvSIMCards->AutoGenerateColumns = false;
        dgvSIMCards->Columns->Clear();

        // Номер телефона
        DataGridViewTextBoxColumn^ colPhone = gcnew DataGridViewTextBoxColumn();
        colPhone->HeaderText = L"Номер телефона";
        colPhone->DataPropertyName = L"PhoneNumber";
        colPhone->Width = 120;
        dgvSIMCards->Columns->Add(colPhone);

        // Оператор
        DataGridViewTextBoxColumn^ colOperator = gcnew DataGridViewTextBoxColumn();
        colOperator->HeaderText = L"Оператор";
        colOperator->DataPropertyName = L"Operator";
        colOperator->Width = 100;
        dgvSIMCards->Columns->Add(colOperator);

        // Тариф
        DataGridViewTextBoxColumn^ colTariff = gcnew DataGridViewTextBoxColumn();
        colTariff->HeaderText = L"Тарифный план";
        colTariff->DataPropertyName = L"TariffPlan";
        colTariff->Width = 120;
        dgvSIMCards->Columns->Add(colTariff);

        // Статус
        DataGridViewTextBoxColumn^ colStatus = gcnew DataGridViewTextBoxColumn();
        colStatus->HeaderText = L"Статус";
        colStatus->DataPropertyName = L"IsActive";
        colStatus->Width = 80;
        colStatus->DefaultCellStyle->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
        dgvSIMCards->Columns->Add(colStatus);

        // Устройство
        DataGridViewTextBoxColumn^ colDevice = gcnew DataGridViewTextBoxColumn();
        colDevice->HeaderText = L"Устройство";
        colDevice->DataPropertyName = L"DeviceModel";
        colDevice->Width = 120;
        dgvSIMCards->Columns->Add(colDevice);

        // Дата окончания
        DataGridViewTextBoxColumn^ colExpiry = gcnew DataGridViewTextBoxColumn();
        colExpiry->HeaderText = L"Окончание";
        colExpiry->DataPropertyName = L"ExpiryDate";
        colExpiry->Width = 100;
        colExpiry->DefaultCellStyle->Format = "dd.MM.yyyy";
        dgvSIMCards->Columns->Add(colExpiry);

        // Использование трафика
        DataGridViewTextBoxColumn^ colData = gcnew DataGridViewTextBoxColumn();
        colData->HeaderText = L"Трафик (ГБ)";
        colData->DataPropertyName = L"DataUsedGB";
        colData->Width = 80;
        colData->DefaultCellStyle->Format = "N1";
        dgvSIMCards->Columns->Add(colData);

        // Ежемесячная стоимость
        DataGridViewTextBoxColumn^ colCost = gcnew DataGridViewTextBoxColumn();
        colCost->HeaderText = L"Стоимость ($)";
        colCost->DataPropertyName = L"MonthlyCost";
        colCost->Width = 90;
        colCost->DefaultCellStyle->Format = "N2";
        dgvSIMCards->Columns->Add(colCost);
    }

    void SIMCardsForm::SetupWarningTimer()
    {
        warningTimer = gcnew System::Windows::Forms::Timer();
        warningTimer->Interval = 60000; // 1 минута
        warningTimer->Tick += gcnew System::EventHandler(this, &SIMCardsForm::warningTimer_Tick);
        warningTimer->Start();

        // Первая проверка
        CheckForWarnings();
    }

    void SIMCardsForm::warningTimer_Tick(Object^ sender, EventArgs^ e)
    {
        CheckForWarnings();
    }

    void SIMCardsForm::CheckForWarnings()
    {
        UpdateWarningsDisplay();
    }

    void SIMCardsForm::UpdateWarningsDisplay()
    {
        List<String^>^ warnings = gcnew List<String^>();
        DateTime today = DateTime::Today;

        for each (SIMCardData ^ sim in simCards)
        {
            // Проверка на окончание контракта
            if ((sim->ExpiryDate - today).TotalDays <= 30)
            {
                warnings->Add(String::Format(L"SIM {0}: контракт заканчивается {1:dd.MM.yyyy}",
                    sim->PhoneNumber, sim->ExpiryDate));
            }

            // Проверка лимита трафика (если использовано более 90%)
            if (sim->DataLimitGB > 0 && sim->DataUsedGB >= sim->DataLimitGB * 0.9)
            {
                warnings->Add(String::Format(L"SIM {0}: использовано {1}/{2} ГБ трафика",
                    sim->PhoneNumber, sim->DataUsedGB, sim->DataLimitGB));
            }
        }

        if (warnings->Count > 0)
        {
            pnlWarnings->Visible = true;
            lblWarnings->Text = String::Join(L" | ", warnings->ToArray());
        }
        else
        {
            pnlWarnings->Visible = false;
        }
    }

    void SIMCardsForm::LoadSIMCards()
    {
        simCards->Clear();
        List<SIMCardData^>^ loadedCards = LoadSIMCardsFromFile();

        for each (SIMCardData ^ card in loadedCards)
        {
            simCards->Add(card);
        }

        dgvSIMCards->DataSource = simCards;

        // Добавляем тестовые данные, если файл пустой
        if (simCards->Count == 0)
        {
            AddTestData();
        }

        UpdateWarningsDisplay();
    }

    List<SIMCardData^>^ SIMCardsForm::LoadSIMCardsFromFile()
    {
        List<SIMCardData^>^ cardsList = gcnew List<SIMCardData^>();
        String^ filePath = "simcards.txt";

        if (!System::IO::File::Exists(filePath))
            return cardsList;

        try
        {
            array<String^>^ lines = System::IO::File::ReadAllLines(filePath, System::Text::Encoding::UTF8);

            for each (String ^ line in lines)
            {
                if (String::IsNullOrEmpty(line))
                    continue;

                array<String^>^ parts = line->Split('|');
                if (parts->Length >= 10)
                {
                    SIMCardData^ card = gcnew SIMCardData();
                    card->Id = Int32::Parse(parts[0]);
                    card->PhoneNumber = parts[1];
                    card->Operator = parts[2];
                    card->TariffPlan = parts[3];
                    card->MonthlyCost = Double::Parse(parts[4]);
                    card->DataLimitGB = Int32::Parse(parts[5]);
                    card->MinutesLimit = Int32::Parse(parts[6]);
                    card->SMSLimit = Int32::Parse(parts[7]);
                    card->ActivationDate = DateTime::Parse(parts[8]);
                    card->ExpiryDate = DateTime::Parse(parts[9]);
                    card->IsActive = Boolean::Parse(parts[10]);
                    card->DeviceIMEI = parts[11];
                    card->DeviceModel = parts[12];

                    if (parts->Length > 13 && !String::IsNullOrEmpty(parts[13]))
                        card->DataUsedGB = Int32::Parse(parts[13]);
                    if (parts->Length > 14 && !String::IsNullOrEmpty(parts[14]))
                        card->MinutesUsed = Int32::Parse(parts[14]);
                    if (parts->Length > 15 && !String::IsNullOrEmpty(parts[15]))
                        card->SMSUsed = Int32::Parse(parts[15]);

                    cardsList->Add(card);
                }
            }
        }
        catch (Exception^ ex)
        {
            System::Diagnostics::Debug::WriteLine("Ошибка загрузки SIM-карт: " + ex->Message);
        }

        return cardsList;
    }

    void SIMCardsForm::SaveSIMCardsToFile()
    {
        String^ filePath = "simcards.txt";
        List<String^>^ lines = gcnew List<String^>();

        for each (SIMCardData ^ card in simCards)
        {
            String^ line = String::Format("{0}|{1}|{2}|{3}|{4}|{5}|{6}|{7}|{8}|{9}|{10}|{11}|{12}|{13}|{14}|{15}",
                card->Id,
                card->PhoneNumber,
                card->Operator,
                card->TariffPlan,
                card->MonthlyCost,
                card->DataLimitGB,
                card->MinutesLimit,
                card->SMSLimit,
                card->ActivationDate.ToString("o"),
                card->ExpiryDate.ToString("o"),
                card->IsActive,
                card->DeviceIMEI,
                card->DeviceModel,
                card->DataUsedGB,
                card->MinutesUsed,
                card->SMSUsed);

            lines->Add(line);
        }

        System::IO::File::WriteAllLines(filePath, lines->ToArray(), System::Text::Encoding::UTF8);
    }

    void SIMCardsForm::AddTestData()
    {
        SIMCardData^ card1 = gcnew SIMCardData();
        card1->Id = 1;
        card1->PhoneNumber = L"+79001234567";
        card1->Operator = L"МТС";
        card1->TariffPlan = L"Безлимит";
        card1->MonthlyCost = 500.0;
        card1->DataLimitGB = 30;
        card1->DeviceModel = L"iPhone 13";
        card1->ExpiryDate = DateTime::Now.AddMonths(1);
        card1->DataUsedGB = 28;
        simCards->Add(card1);

        SIMCardData^ card2 = gcnew SIMCardData();
        card2->Id = 2;
        card2->PhoneNumber = L"+79007654321";
        card2->Operator = L"Билайн";
        card2->TariffPlan = L"Стандарт";
        card2->MonthlyCost = 300.0;
        card2->DataLimitGB = 10;
        card2->DeviceModel = L"Samsung Galaxy";
        card2->ExpiryDate = DateTime::Now.AddMonths(6);
        card2->DataUsedGB = 5;
        simCards->Add(card2);

        SaveSIMCardsToFile();
    }

    void SIMCardsForm::btnAdd_Click(Object^ sender, EventArgs^ e)
    {
        SIMCardEditForm^ editForm = gcnew SIMCardEditForm(nullptr);
        if (editForm->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
        {
            SIMCardData^ newCard = editForm->SIMCard;
            newCard->Id = simCards->Count + 1;
            simCards->Add(newCard);
            SaveSIMCardsToFile();
            UpdateWarningsDisplay();
        }
    }

    void SIMCardsForm::btnEdit_Click(Object^ sender, EventArgs^ e)
    {
        if (dgvSIMCards->SelectedRows->Count == 0)
        {
            MessageBox::Show(L"Выберите SIM-карту для редактирования!",
                L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        int selectedIndex = dgvSIMCards->SelectedRows[0]->Index;
        if (selectedIndex >= 0 && selectedIndex < simCards->Count)
        {
            SIMCardData^ selectedCard = simCards[selectedIndex];
            SIMCardEditForm^ editForm = gcnew SIMCardEditForm(selectedCard);

            if (editForm->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
            {
                SaveSIMCardsToFile();
                UpdateWarningsDisplay();
            }
        }
    }

    void SIMCardsForm::btnDelete_Click(Object^ sender, EventArgs^ e)
    {
        if (dgvSIMCards->SelectedRows->Count == 0)
        {
            MessageBox::Show(L"Выберите SIM-карту для удаления!",
                L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        if (MessageBox::Show(L"Удалить выбранную SIM-карту?", L"Подтверждение",
            MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            int selectedIndex = dgvSIMCards->SelectedRows[0]->Index;
            if (selectedIndex >= 0 && selectedIndex < simCards->Count)
            {
                simCards->RemoveAt(selectedIndex);
                SaveSIMCardsToFile();
                UpdateWarningsDisplay();
            }
        }
    }

    void SIMCardsForm::btnRefresh_Click(Object^ sender, EventArgs^ e)
    {
        LoadSIMCards();
    }

    void SIMCardsForm::btnClose_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }

    void SIMCardsForm::dgvSIMCards_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex >= 0 && e->RowIndex < simCards->Count)
        {
            SIMCardData^ selectedCard = simCards[e->RowIndex];

            // Создаем и показываем форму с детальной информацией
            SIMCardInfoForm^ infoForm = gcnew SIMCardInfoForm(selectedCard);
            infoForm->ShowDialog();
        }
    }
}