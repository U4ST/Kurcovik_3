#include "MainForm.h"
#include "RepairJournalForm.h"
#include "SIMCardsForm.h"
#include "ReportsForm.h"
#include "SettingsForm.h"
#include <msclr/marshal_cppstd.h>

namespace DeviceManagementApp {

    //ИНИЦИАЛИЗАЦИЯ КОМПОНЕНТОВ

    void MainForm::InitializeComponent()
    {
        this->Text = L"Система учета устройств";
        this->Size = System::Drawing::Size(1200, 750);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::WhiteSmoke;

        // Заголовок
        lblTitle = gcnew Label();
        lblTitle->Text = L"Устройства в наличии";
        lblTitle->Font = gcnew Drawing::Font(L"Arial", 16, FontStyle::Bold);
        lblTitle->Location = Point(20, 20);
        lblTitle->Size = System::Drawing::Size(300, 30);
        lblTitle->ForeColor = Color::DarkBlue;
        this->Controls->Add(lblTitle);

        // DataGridView
        dgvDevices = gcnew DataGridView();
        dgvDevices->Location = Point(20, 60);
        dgvDevices->Size = System::Drawing::Size(1140, 350);
        dgvDevices->ReadOnly = true;
        dgvDevices->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        dgvDevices->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        dgvDevices->AllowUserToAddRows = false;
        dgvDevices->AllowUserToDeleteRows = false;
        dgvDevices->RowHeadersVisible = false;
        dgvDevices->BackgroundColor = Color::White;
        dgvDevices->BorderStyle = BorderStyle::Fixed3D;
        this->Controls->Add(dgvDevices);

        // Кнопки сортировки
        int sortYPos = 420;
        int sortXPos = 20;

        btnSortManufacturer = gcnew Button();
        btnSortManufacturer->Text = L"Сорт. по производителю";
        btnSortManufacturer->Location = Point(sortXPos, sortYPos);
        btnSortManufacturer->Size = System::Drawing::Size(150, 30);
        btnSortManufacturer->Font = gcnew Drawing::Font(L"Segoe UI", 8.5F);
        btnSortManufacturer->BackColor = Color::LightGray;
        btnSortManufacturer->Click += gcnew EventHandler(this, &MainForm::btnSortManufacturer_Click);
        this->Controls->Add(btnSortManufacturer);

        btnSortPrice = gcnew Button();
        btnSortPrice->Text = L"Сорт. по цене";
        btnSortPrice->Location = Point(sortXPos + 160, sortYPos);
        btnSortPrice->Size = System::Drawing::Size(120, 30);
        btnSortPrice->Font = gcnew Drawing::Font(L"Segoe UI", 8.5F);
        btnSortPrice->BackColor = Color::LightGray;
        btnSortPrice->Click += gcnew EventHandler(this, &MainForm::btnSortPrice_Click);
        this->Controls->Add(btnSortPrice);

        btnSortType = gcnew Button();
        btnSortType->Text = L"Сорт. по типу";
        btnSortType->Location = Point(sortXPos + 290, sortYPos);
        btnSortType->Size = System::Drawing::Size(120, 30);
        btnSortType->Font = gcnew Drawing::Font(L"Segoe UI", 8.5F);
        btnSortType->BackColor = Color::LightGray;
        btnSortType->Click += gcnew EventHandler(this, &MainForm::btnSortType_Click);
        this->Controls->Add(btnSortType);

        // Основные кнопки управления
        int yPos = 460;
        int xPos = 20;
        int buttonWidth = 100;
        int buttonHeight = 35;
        int buttonSpacing = 110;

        btnRefresh = gcnew Button();
        btnRefresh->Text = L"Обновить";
        btnRefresh->Location = Point(xPos, yPos);
        btnRefresh->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnRefresh->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnRefresh->BackColor = Color::LightGray;
        btnRefresh->Click += gcnew EventHandler(this, &MainForm::btnRefresh_Click);
        this->Controls->Add(btnRefresh);

        btnAdd = gcnew Button();
        btnAdd->Text = L"Добавить";
        btnAdd->Location = Point(xPos + buttonSpacing, yPos);
        btnAdd->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnAdd->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        btnAdd->BackColor = Color::LightGreen;
        btnAdd->Enabled = isAdminMode;
        btnAdd->Click += gcnew EventHandler(this, &MainForm::btnAdd_Click);
        this->Controls->Add(btnAdd);

        btnEdit = gcnew Button();
        btnEdit->Text = L"Изменить";
        btnEdit->Location = Point(xPos + buttonSpacing * 2, yPos);
        btnEdit->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnEdit->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnEdit->BackColor = Color::LightYellow;
        btnEdit->Enabled = isAdminMode;
        btnEdit->Click += gcnew EventHandler(this, &MainForm::btnEdit_Click);
        this->Controls->Add(btnEdit);

        btnDelete = gcnew Button();
        btnDelete->Text = L"Удалить";
        btnDelete->Location = Point(xPos + buttonSpacing * 3, yPos);
        btnDelete->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnDelete->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnDelete->BackColor = Color::LightCoral;
        btnDelete->Enabled = isAdminMode;
        btnDelete->Click += gcnew EventHandler(this, &MainForm::btnDelete_Click);
        this->Controls->Add(btnDelete);

        btnStats = gcnew Button();
        btnStats->Text = L"Статистика";
        btnStats->Location = Point(xPos + buttonSpacing * 4, yPos);
        btnStats->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnStats->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnStats->BackColor = Color::LightBlue;
        btnStats->Click += gcnew EventHandler(this, &MainForm::btnStats_Click);
        this->Controls->Add(btnStats);

        btnExport = gcnew Button();
        btnExport->Text = L"Экспорт";
        btnExport->Location = Point(xPos + buttonSpacing * 5, yPos);
        btnExport->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnExport->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnExport->BackColor = Color::LightCyan;
        btnExport->Click += gcnew EventHandler(this, &MainForm::btnExport_Click);
        this->Controls->Add(btnExport);

        btnRepairs = gcnew Button();
        btnRepairs->Text = L"Ремонты";
        btnRepairs->Location = Point(xPos + buttonSpacing * 6, yPos);
        btnRepairs->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnRepairs->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnRepairs->BackColor = Color::LightGoldenrodYellow;
        btnRepairs->Click += gcnew EventHandler(this, &MainForm::btnRepairs_Click);
        this->Controls->Add(btnRepairs);

        btnSIMCards = gcnew Button();
        btnSIMCards->Text = L"SIM-карты";
        btnSIMCards->Location = Point(xPos + buttonSpacing * 7, yPos);
        btnSIMCards->Size = System::Drawing::Size(buttonWidth, buttonHeight);
        btnSIMCards->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnSIMCards->BackColor = Color::LightSteelBlue;
        btnSIMCards->Click += gcnew EventHandler(this, &MainForm::btnSIMCards_Click);
        this->Controls->Add(btnSIMCards);

        // Система поиска
        int searchYPos = 510;

        // Выбор типа поиска
        lblSearchType = gcnew Label();
        lblSearchType->Text = L"Тип поиска:";
        lblSearchType->Location = Point(xPos, searchYPos);
        lblSearchType->Size = System::Drawing::Size(80, 25);
        lblSearchType->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblSearchType);

        cmbSearchType = gcnew ComboBox();
        cmbSearchType->Location = Point(xPos + 85, searchYPos);
        cmbSearchType->Size = System::Drawing::Size(150, 25);
        cmbSearchType->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbSearchType->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbSearchType->Items->AddRange(gcnew cli::array<String^>(3) {
            L"Текстовый поиск",
                L"Поиск по цене",
                L"Комбинированный поиск"
        });
        cmbSearchType->SelectedIndex = 0;
        cmbSearchType->SelectedIndexChanged += gcnew EventHandler(this, &MainForm::cmbSearchType_Changed);
        this->Controls->Add(cmbSearchType);

        // Панель для текстового поиска
        pnlTextSearch = gcnew Panel();
        pnlTextSearch->Location = Point(xPos, searchYPos + 35);
        pnlTextSearch->Size = System::Drawing::Size(400, 30);
        pnlTextSearch->Visible = true;
        this->Controls->Add(pnlTextSearch);

        Label^ lblTextSearch = gcnew Label();
        lblTextSearch->Text = L"Текст поиска:";
        lblTextSearch->Location = Point(0, 5);
        lblTextSearch->Size = System::Drawing::Size(90, 20);
        lblTextSearch->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlTextSearch->Controls->Add(lblTextSearch);

        txtTextSearch = gcnew TextBox();
        txtTextSearch->Location = Point(95, 3);
        txtTextSearch->Size = System::Drawing::Size(200, 25);
        txtTextSearch->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlTextSearch->Controls->Add(txtTextSearch);

        // Панель для поиска по цене
        pnlPriceSearch = gcnew Panel();
        pnlPriceSearch->Location = Point(xPos, searchYPos + 35);
        pnlPriceSearch->Size = System::Drawing::Size(500, 30);
        pnlPriceSearch->Visible = false;
        this->Controls->Add(pnlPriceSearch);

        lblPriceFrom = gcnew Label();
        lblPriceFrom->Text = L"Цена от:";
        lblPriceFrom->Location = Point(0, 5);
        lblPriceFrom->Size = System::Drawing::Size(60, 25);
        lblPriceFrom->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlPriceSearch->Controls->Add(lblPriceFrom);

        txtPriceFrom = gcnew TextBox();
        txtPriceFrom->Location = Point(65, 3);
        txtPriceFrom->Size = System::Drawing::Size(70, 25);
        txtPriceFrom->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtPriceFrom->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::txtPrice_KeyPress);
        pnlPriceSearch->Controls->Add(txtPriceFrom);

        lblPriceTo = gcnew Label();
        lblPriceTo->Text = L"до:";
        lblPriceTo->Location = Point(140, 5);
        lblPriceTo->Size = System::Drawing::Size(30, 25);
        lblPriceTo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlPriceSearch->Controls->Add(lblPriceTo);

        txtPriceTo = gcnew TextBox();
        txtPriceTo->Location = Point(175, 3);
        txtPriceTo->Size = System::Drawing::Size(70, 25);
        txtPriceTo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtPriceTo->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::txtPrice_KeyPress);
        pnlPriceSearch->Controls->Add(txtPriceTo);

        // Панель для комбинированного поиска
        pnlCombinedSearch = gcnew Panel();
        pnlCombinedSearch->Location = Point(xPos, searchYPos + 35);
        pnlCombinedSearch->Size = System::Drawing::Size(800, 80);
        pnlCombinedSearch->Visible = false;
        this->Controls->Add(pnlCombinedSearch);

        // Первая строка комбинированного поиска
        Label^ lblCombinedText = gcnew Label();
        lblCombinedText->Text = L"Текст:";
        lblCombinedText->Location = Point(0, 5);
        lblCombinedText->Size = System::Drawing::Size(50, 20);
        lblCombinedText->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlCombinedSearch->Controls->Add(lblCombinedText);

        txtCombinedText = gcnew TextBox();
        txtCombinedText->Location = Point(55, 3);
        txtCombinedText->Size = System::Drawing::Size(150, 25);
        txtCombinedText->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlCombinedSearch->Controls->Add(txtCombinedText);

        Label^ lblCombinedPrice = gcnew Label();
        lblCombinedPrice->Text = L"Цена:";
        lblCombinedPrice->Location = Point(210, 5);
        lblCombinedPrice->Size = System::Drawing::Size(40, 20);
        lblCombinedPrice->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlCombinedSearch->Controls->Add(lblCombinedPrice);

        txtCombinedPriceFrom = gcnew TextBox();
        txtCombinedPriceFrom->Location = Point(255, 3);
        txtCombinedPriceFrom->Size = System::Drawing::Size(60, 25);
        txtCombinedPriceFrom->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtCombinedPriceFrom->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::txtPrice_KeyPress);
        pnlCombinedSearch->Controls->Add(txtCombinedPriceFrom);

        Label^ lblCombinedDash = gcnew Label();
        lblCombinedDash->Text = L"-";
        lblCombinedDash->Location = Point(320, 5);
        lblCombinedDash->Size = System::Drawing::Size(10, 20);
        pnlCombinedSearch->Controls->Add(lblCombinedDash);

        txtCombinedPriceTo = gcnew TextBox();
        txtCombinedPriceTo->Location = Point(335, 3);
        txtCombinedPriceTo->Size = System::Drawing::Size(60, 25);
        txtCombinedPriceTo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        txtCombinedPriceTo->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::txtPrice_KeyPress);
        pnlCombinedSearch->Controls->Add(txtCombinedPriceTo);

        // Вторая строка комбинированного поиска
        Label^ lblCombinedType = gcnew Label();
        lblCombinedType->Text = L"Тип:";
        lblCombinedType->Location = Point(0, 40);
        lblCombinedType->Size = System::Drawing::Size(40, 20);
        lblCombinedType->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlCombinedSearch->Controls->Add(lblCombinedType);

        cmbCombinedType = gcnew ComboBox();
        cmbCombinedType->Location = Point(45, 38);
        cmbCombinedType->Size = System::Drawing::Size(120, 25);
        cmbCombinedType->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbCombinedType->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbCombinedType->Items->Add(L"Любой");
        cmbCombinedType->Items->AddRange(gcnew cli::array<String^>(3) {
            L"Мобильное устройство",
                L"Планшет",
                L"Умные часы"
        });
        cmbCombinedType->SelectedIndex = 0;
        pnlCombinedSearch->Controls->Add(cmbCombinedType);

        Label^ lblCombinedStatus = gcnew Label();
        lblCombinedStatus->Text = L"Статус:";
        lblCombinedStatus->Location = Point(170, 40);
        lblCombinedStatus->Size = System::Drawing::Size(50, 20);
        lblCombinedStatus->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        pnlCombinedSearch->Controls->Add(lblCombinedStatus);

        cmbCombinedStatus = gcnew ComboBox();
        cmbCombinedStatus->Location = Point(225, 38);
        cmbCombinedStatus->Size = System::Drawing::Size(120, 25);
        cmbCombinedStatus->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbCombinedStatus->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbCombinedStatus->Items->Add(L"Любой");
        cmbCombinedStatus->Items->AddRange(gcnew cli::array<String^>(5) {
            L"На складе",
                L"В эксплуатации",
                L"На ремонте",
                L"Списан",
                L"Резерв"
        });
        cmbCombinedStatus->SelectedIndex = 0;
        pnlCombinedSearch->Controls->Add(cmbCombinedStatus);

        // Кнопки поиска и сброса
        btnSearch = gcnew Button();
        btnSearch->Text = L"Найти";
        btnSearch->Location = Point(600, searchYPos);
        btnSearch->Size = System::Drawing::Size(80, 25);
        btnSearch->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnSearch->BackColor = Color::LightSteelBlue;
        btnSearch->Click += gcnew EventHandler(this, &MainForm::btnSearch_Click);
        this->Controls->Add(btnSearch);

        btnResetSearch = gcnew Button();
        btnResetSearch->Text = L"Сбросить";
        btnResetSearch->Location = Point(690, searchYPos);
        btnResetSearch->Size = System::Drawing::Size(80, 25);
        btnResetSearch->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnResetSearch->BackColor = Color::LightSalmon;
        btnResetSearch->Click += gcnew EventHandler(this, &MainForm::btnResetSearch_Click);
        this->Controls->Add(btnResetSearch);

        // Кнопка выхода
        btnLogout = gcnew Button();
        btnLogout->Text = L"✕ Выход";
        btnLogout->Location = Point(1080, 10);
        btnLogout->Size = System::Drawing::Size(80, 35);
        btnLogout->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        btnLogout->BackColor = Color::LightCoral;
        btnLogout->ForeColor = Color::White;
        btnLogout->FlatStyle = FlatStyle::Flat;
        btnLogout->FlatAppearance->BorderSize = 0;
        btnLogout->Cursor = Cursors::Hand;
        btnLogout->Click += gcnew EventHandler(this, &MainForm::btnLogout_Click);
        this->Controls->Add(btnLogout);

        // Статистика
        lblStats = gcnew Label();
        lblStats->Location = Point(30, 680);
        lblStats->Size = System::Drawing::Size(1140, 30);
        lblStats->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        lblStats->TextAlign = ContentAlignment::MiddleLeft;
        this->Controls->Add(lblStats);

        if (isAdminMode)
            this->Text += L" [АДМИНИСТРАТОР]";
        else
            this->Text += L" [ПОЛЬЗОВАТЕЛЬ]";

        // Подключение обработчиков событий
        dgvDevices->CellDoubleClick += gcnew DataGridViewCellEventHandler(
            this, &MainForm::dgvDevices_CellDoubleClick);
    }

    //МЕТОДЫ ДЛЯ ТАБЛИЦЫ 

    void MainForm::SetupDataGridView()
    {
        dgvDevices->AutoGenerateColumns = false;
        dgvDevices->Columns->Clear();

        // ID
        DataGridViewTextBoxColumn^ colId = gcnew DataGridViewTextBoxColumn();
        colId->HeaderText = L"ID";
        colId->DataPropertyName = L"Id";
        colId->Width = 50;
        colId->ReadOnly = true;
        dgvDevices->Columns->Add(colId);

        // Производитель
        DataGridViewTextBoxColumn^ colManufacturer = gcnew DataGridViewTextBoxColumn();
        colManufacturer->HeaderText = L"Производитель";
        colManufacturer->DataPropertyName = L"Manufacturer";
        colManufacturer->Width = 150;
        dgvDevices->Columns->Add(colManufacturer);

        // Модель
        DataGridViewTextBoxColumn^ colModel = gcnew DataGridViewTextBoxColumn();
        colModel->HeaderText = L"Модель";
        colModel->DataPropertyName = L"Model";
        colModel->Width = 150;
        dgvDevices->Columns->Add(colModel);

        // Тип
        DataGridViewTextBoxColumn^ colType = gcnew DataGridViewTextBoxColumn();
        colType->HeaderText = L"Тип";
        colType->DataPropertyName = L"Type";
        colType->Width = 120;
        dgvDevices->Columns->Add(colType);

        // Цена
        DataGridViewTextBoxColumn^ colPrice = gcnew DataGridViewTextBoxColumn();
        colPrice->HeaderText = L"Цена ($)";
        colPrice->DataPropertyName = L"Price";
        colPrice->Width = 80;
        colPrice->DefaultCellStyle->Format = "F2";
        colPrice->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
        dgvDevices->Columns->Add(colPrice);

        // Доп. информация
        DataGridViewTextBoxColumn^ colAdditional = gcnew DataGridViewTextBoxColumn();
        colAdditional->HeaderText = L"Доп. информация";
        colAdditional->DataPropertyName = L"AdditionalInfo";
        colAdditional->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
        dgvDevices->Columns->Add(colAdditional);
    }

    void MainForm::LoadDevices()
    {
        RefreshGrid();
        lblStats->Text = String::Format(L"Данные в памяти: {0} устройств | {1}",
            devices->Count, DateTime::Now.ToString("HH:mm:ss"));
    }

    void MainForm::RefreshGrid()
    {
        dgvDevices->DataSource = nullptr;
        dgvDevices->DataSource = devices;

        dgvDevices->Refresh();
        dgvDevices->Update();
        UpdateStats();
    }

    //СИСТЕМА ПОИСКА

    void MainForm::cmbSearchType_Changed(Object^ sender, EventArgs^ e)
    {
        int selectedIndex = cmbSearchType->SelectedIndex;

        pnlTextSearch->Visible = (selectedIndex == 0);
        pnlPriceSearch->Visible = (selectedIndex == 1);
        pnlCombinedSearch->Visible = (selectedIndex == 2);
    }

    void MainForm::btnSearch_Click(Object^ sender, EventArgs^ e)
    {
        int searchType = cmbSearchType->SelectedIndex;
        List<DeviceData^>^ filtered = gcnew List<DeviceData^>();

        switch (searchType)
        {
        case 0: // Текстовый поиск
            filtered = PerformTextSearch();
            break;
        case 1: // Поиск по цене
            filtered = PerformPriceSearch();
            break;
        case 2: // Комбинированный поиск
            filtered = PerformCombinedSearch();
            break;
        }

        if (filtered->Count == 0)
        {
            MessageBox::Show(L"Устройств по указанным критериям не найдено",
                L"Результат поиска", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        ShowFilteredResults(filtered, GetSearchDescription(searchType));
    }

    List<DeviceData^>^ MainForm::PerformTextSearch()
    {
        List<DeviceData^>^ filtered = gcnew List<DeviceData^>();
        String^ query = txtTextSearch->Text->ToLower()->Trim();

        if (String::IsNullOrEmpty(query))
        {
            // Если запрос пустой, возвращаем все устройства
            for each (DeviceData ^ d in devices)
                filtered->Add(d);
            return filtered;
        }

        for each (DeviceData ^ d in devices)
        {
            if (d->Manufacturer->ToLower()->Contains(query) ||
                d->Model->ToLower()->Contains(query) ||
                d->Type->ToLower()->Contains(query) ||
                d->AdditionalInfo->ToLower()->Contains(query) ||
                d->SerialNumber->ToLower()->Contains(query) ||
                d->IMEI->ToLower()->Contains(query))
            {
                filtered->Add(d);
            }
        }

        return filtered;
    }

    List<DeviceData^>^ MainForm::PerformPriceSearch()
    {
        List<DeviceData^>^ filtered = gcnew List<DeviceData^>();

        double priceFrom = 0;
        double priceTo = Double::MaxValue;

        // Проверяем ввод минимальной цены
        if (!String::IsNullOrWhiteSpace(txtPriceFrom->Text))
        {
            String^ fromText = txtPriceFrom->Text->Replace(",", ".");
            if (!Double::TryParse(fromText, priceFrom))
            {
                MessageBox::Show(L"Неверный формат цены 'от'", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtPriceFrom->Focus();
                return filtered;
            }
        }

        // Проверяем ввод максимальной цены
        if (!String::IsNullOrWhiteSpace(txtPriceTo->Text))
        {
            String^ toText = txtPriceTo->Text->Replace(",", ".");
            if (!Double::TryParse(toText, priceTo))
            {
                MessageBox::Show(L"Неверный формат цены 'до'", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtPriceTo->Focus();
                return filtered;
            }
        }

        // Проверяем, что "от" не больше "до"
        if (priceFrom > priceTo)
        {
            MessageBox::Show(L"Цена 'от' не может быть больше цены 'до'", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtPriceFrom->Focus();
            return filtered;
        }

        for each (DeviceData ^ d in devices)
        {
            if (d->Price >= priceFrom && d->Price <= priceTo)
            {
                filtered->Add(d);
            }
        }

        return filtered;
    }

    List<DeviceData^>^ MainForm::PerformCombinedSearch()
    {
        List<DeviceData^>^ filtered = gcnew List<DeviceData^>();

        String^ textQuery = txtCombinedText->Text->ToLower()->Trim();
        bool hasTextQuery = !String::IsNullOrWhiteSpace(textQuery);

        double priceFrom = 0;
        double priceTo = Double::MaxValue;
        bool hasPriceQuery = false;

        // Проверяем цену "от"
        if (!String::IsNullOrWhiteSpace(txtCombinedPriceFrom->Text))
        {
            String^ fromText = txtCombinedPriceFrom->Text->Replace(",", ".");
            if (!Double::TryParse(fromText, priceFrom))
            {
                MessageBox::Show(L"Неверный формат цены 'от'", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtCombinedPriceFrom->Focus();
                return filtered;
            }
            hasPriceQuery = true;
        }

        // Проверяем цену "до"
        if (!String::IsNullOrWhiteSpace(txtCombinedPriceTo->Text))
        {
            String^ toText = txtCombinedPriceTo->Text->Replace(",", ".");
            if (!Double::TryParse(toText, priceTo))
            {
                MessageBox::Show(L"Неверный формат цены 'до'", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtCombinedPriceTo->Focus();
                return filtered;
            }
            hasPriceQuery = true;
        }

        // Проверяем корректность диапазона цен
        if (hasPriceQuery && priceFrom > priceTo)
        {
            MessageBox::Show(L"Цена 'от' не может быть больше цены 'до'", L"Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            txtCombinedPriceFrom->Focus();
            return filtered;
        }

        String^ selectedType = cmbCombinedType->SelectedItem->ToString();
        bool filterByType = (selectedType != "Любой");

        String^ selectedStatus = cmbCombinedStatus->SelectedItem->ToString();
        bool filterByStatus = (selectedStatus != "Любой");

        for each (DeviceData ^ d in devices)
        {
            bool matches = true;

            // Проверка текстового запроса
            if (hasTextQuery)
            {
                matches = matches && (
                    d->Manufacturer->ToLower()->Contains(textQuery) ||
                    d->Model->ToLower()->Contains(textQuery) ||
                    d->Type->ToLower()->Contains(textQuery) ||
                    d->AdditionalInfo->ToLower()->Contains(textQuery) ||
                    d->SerialNumber->ToLower()->Contains(textQuery) ||
                    d->IMEI->ToLower()->Contains(textQuery));
            }

            // Проверка цены
            if (hasPriceQuery)
            {
                matches = matches && (d->Price >= priceFrom && d->Price <= priceTo);
            }

            // Проверка типа
            if (filterByType)
            {
                matches = matches && (d->Type == selectedType);
            }

            // Проверка статуса
            if (filterByStatus)
            {
                matches = matches && (d->Status == selectedStatus);
            }

            if (matches)
            {
                filtered->Add(d);
            }
        }

        return filtered;
    }

    String^ MainForm::GetSearchDescription(int searchType)
    {
        switch (searchType)
        {
        case 0: // Текстовый поиск
            return String::Format(L"Текстовый поиск: '{0}'", txtTextSearch->Text);

        case 1: // Поиск по цене
        {
            String^ from = txtPriceFrom->Text;
            String^ to = txtPriceTo->Text;
            if (String::IsNullOrWhiteSpace(from)) from = "0";
            if (String::IsNullOrWhiteSpace(to)) to = "∞";
            return String::Format(L"Поиск по цене: от ${0} до ${1}", from, to);
        }

        case 2: // Комбинированный поиск
        {
            List<String^>^ criteria = gcnew List<String^>();

            if (!String::IsNullOrWhiteSpace(txtCombinedText->Text))
                criteria->Add(String::Format(L"текст: '{0}'", txtCombinedText->Text));

            if (!String::IsNullOrWhiteSpace(txtCombinedPriceFrom->Text) ||
                !String::IsNullOrWhiteSpace(txtCombinedPriceTo->Text))
            {
                String^ from = String::IsNullOrWhiteSpace(txtCombinedPriceFrom->Text) ?
                    "0" : txtCombinedPriceFrom->Text;
                String^ to = String::IsNullOrWhiteSpace(txtCombinedPriceTo->Text) ?
                    "∞" : txtCombinedPriceTo->Text;
                criteria->Add(String::Format(L"цена: ${0}-${1}", from, to));
            }

            if (cmbCombinedType->SelectedItem->ToString() != "Любой")
                criteria->Add(String::Format(L"тип: {0}", cmbCombinedType->SelectedItem));

            if (cmbCombinedStatus->SelectedItem->ToString() != "Любой")
                criteria->Add(String::Format(L"статус: {0}", cmbCombinedStatus->SelectedItem));

            if (criteria->Count == 0)
                return L"Все критерии";

            return String::Format(L"Комбинированный поиск: {0}", String::Join(L", ", criteria->ToArray()));
        }

        default:
            return L"Поиск";
        }
    }

    void MainForm::ShowFilteredResults(List<DeviceData^>^ filtered, String^ searchInfo)
    {
        BindingList<DeviceData^>^ filteredBinding = gcnew BindingList<DeviceData^>();
        for each (DeviceData ^ d in filtered)
            filteredBinding->Add(d);

        dgvDevices->DataSource = filteredBinding;
        dgvDevices->Refresh();

        lblStats->Text = String::Format(L"Найдено устройств: {0} | {1}",
            filtered->Count, searchInfo);
    }

    void MainForm::btnResetSearch_Click(Object^ sender, EventArgs^ e)
    {
        // Очищаем все поля поиска
        txtTextSearch->Text = L"";
        txtPriceFrom->Text = L"";
        txtPriceTo->Text = L"";
        txtCombinedText->Text = L"";
        txtCombinedPriceFrom->Text = L"";
        txtCombinedPriceTo->Text = L"";
        cmbCombinedType->SelectedIndex = 0;
        cmbCombinedStatus->SelectedIndex = 0;

        // Показываем все устройства
        RefreshGrid();
        lblStats->Text = L"Поиск сброшен, показаны все устройства";
    }

    //ЗАЩИТА ВВОДА 

    void MainForm::txtPrice_KeyPress(Object^ sender, KeyPressEventArgs^ e)
    {
        // Разрешаем только цифры, backspace, точку и запятую
        if (!Char::IsDigit(e->KeyChar) &&
            e->KeyChar != 0x08 &&
            e->KeyChar != '.' &&
            e->KeyChar != ',')
        {
            e->Handled = true;
            return;
        }

        // Проверяем, чтобы точка или запятая были только одна
        TextBox^ textBox = safe_cast<TextBox^>(sender);
        if ((e->KeyChar == '.' || e->KeyChar == ',') &&
            (textBox->Text->Contains(".") || textBox->Text->Contains(",")))
        {
            e->Handled = true;
        }
    }

    //СОРТИРОВКА

    void MainForm::btnSortManufacturer_Click(Object^ sender, EventArgs^ e)
    {
        SortDevices(L"Manufacturer");
    }

    void MainForm::btnSortPrice_Click(Object^ sender, EventArgs^ e)
    {
        SortDevices(L"Price");
    }

    void MainForm::btnSortType_Click(Object^ sender, EventArgs^ e)
    {
        SortDevices(L"Type");
    }

    void MainForm::SortDevices(String^ column)
    {
        if (sortColumn == column)
        {
            sortAscending = !sortAscending;
        }
        else
        {
            sortColumn = column;
            sortAscending = true;
        }

        List<DeviceData^>^ devicesList = gcnew List<DeviceData^>();
        for each (DeviceData ^ d in devices)
            devicesList->Add(d);

        if (column == L"Manufacturer")
        {
            if (sortAscending)
                devicesList->Sort(gcnew Comparison<DeviceData^>(CompareByManufacturerAsc));
            else
                devicesList->Sort(gcnew Comparison<DeviceData^>(CompareByManufacturerDesc));
        }
        else if (column == L"Price")
        {
            if (sortAscending)
                devicesList->Sort(gcnew Comparison<DeviceData^>(CompareByPriceAsc));
            else
                devicesList->Sort(gcnew Comparison<DeviceData^>(CompareByPriceDesc));
        }
        else if (column == L"Type")
        {
            if (sortAscending)
                devicesList->Sort(gcnew Comparison<DeviceData^>(CompareByTypeAsc));
            else
                devicesList->Sort(gcnew Comparison<DeviceData^>(CompareByTypeDesc));
        }

        devices->Clear();
        for each (DeviceData ^ d in devicesList)
            devices->Add(d);

        RefreshGrid();
        UpdateSortButtonStyles();
    }

    int MainForm::CompareByManufacturerAsc(DeviceData^ x, DeviceData^ y)
    {
        return String::Compare(x->Manufacturer, y->Manufacturer);
    }

    int MainForm::CompareByManufacturerDesc(DeviceData^ x, DeviceData^ y)
    {
        return String::Compare(y->Manufacturer, x->Manufacturer);
    }

    int MainForm::CompareByPriceAsc(DeviceData^ x, DeviceData^ y)
    {
        return x->Price.CompareTo(y->Price);
    }

    int MainForm::CompareByPriceDesc(DeviceData^ x, DeviceData^ y)
    {
        return y->Price.CompareTo(x->Price);
    }

    int MainForm::CompareByTypeAsc(DeviceData^ x, DeviceData^ y)
    {
        return String::Compare(x->Type, y->Type);
    }

    int MainForm::CompareByTypeDesc(DeviceData^ x, DeviceData^ y)
    {
        return String::Compare(y->Type, x->Type);
    }

    void MainForm::UpdateSortButtonStyles()
    {
        btnSortManufacturer->BackColor = (sortColumn == L"Manufacturer") ?
            Color::LightSkyBlue : Color::LightGray;
        btnSortPrice->BackColor = (sortColumn == L"Price") ?
            Color::LightSkyBlue : Color::LightGray;
        btnSortType->BackColor = (sortColumn == L"Type") ?
            Color::LightSkyBlue : Color::LightGray;

        // Добавляем индикатор направления сортировки
        String^ arrow = sortAscending ? L" ↑" : L" ↓";

        btnSortManufacturer->Text = (sortColumn == L"Manufacturer") ?
            L"Сорт. по производителю" + arrow : L"Сорт. по производителю";
        btnSortPrice->Text = (sortColumn == L"Price") ?
            L"Сорт. по цене" + arrow : L"Сорт. по цене";
        btnSortType->Text = (sortColumn == L"Type") ?
            L"Сорт. по типу" + arrow : L"Сорт. по типу";
    }

    //ОСНОВНЫЕ МЕТОДЫ УПРАВЛЕНИЯ

    void MainForm::btnAdd_Click(Object^ sender, EventArgs^ e)
    {
        AddEditForm^ form = gcnew AddEditForm();
        if (form->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
        {
            try
            {
                // Определяем новый ID
                int newId = 1;
                for each (DeviceData ^ d in devices)
                    if (d->Id >= newId) newId = d->Id + 1;

                DeviceData^ newDevice = gcnew DeviceData();
                newDevice->Id = newId;
                newDevice->Manufacturer = form->Manufacturer;
                newDevice->Model = form->Model;
                newDevice->Type = form->Type;
                newDevice->Price = form->Price;
                newDevice->AdditionalInfo = form->AdditionalInfo;
                newDevice->IMEI = form->IMEI;
                newDevice->SerialNumber = form->SerialNumber;
                newDevice->Status = form->Status;
                newDevice->Owner = form->Owner;

                devices->Add(newDevice);

                // Сохраняем в файл
                List<DeviceData^>^ devicesList = gcnew List<DeviceData^>();
                for each (DeviceData ^ d in devices)
                    devicesList->Add(d);

                FileManager::SaveDevices(devicesList);
                RefreshGrid();

                MessageBox::Show(
                    L"Устройство успешно добавлено!",
                    L"Успешно",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );
            }
            catch (Exception^ ex)
            {
                MessageBox::Show(
                    L"Ошибка при добавлении: " + ex->Message,
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );
            }
        }
    }

    void MainForm::btnEdit_Click(Object^ sender, EventArgs^ e)
    {
        if (dgvDevices->SelectedRows->Count == 0)
        {
            MessageBox::Show(L"Выберите устройство для редактирования!",
                L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        try
        {
            int selectedIndex = dgvDevices->SelectedRows[0]->Index;
            if (selectedIndex >= 0 && selectedIndex < devices->Count)
            {
                DeviceData^ selected = devices[selectedIndex];

                AddEditForm^ form = gcnew AddEditForm(selected);
                if (form->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
                {
                    selected->Manufacturer = form->Manufacturer;
                    selected->Model = form->Model;
                    selected->Type = form->Type;
                    selected->Price = form->Price;
                    selected->AdditionalInfo = form->AdditionalInfo;
                    selected->IMEI = form->IMEI;
                    selected->SerialNumber = form->SerialNumber;
                    selected->Status = form->Status;
                    selected->Owner = form->Owner;

                    // Сохраняем в файл
                    List<DeviceData^>^ devicesList = gcnew List<DeviceData^>();
                    for each (DeviceData ^ d in devices)
                        devicesList->Add(d);

                    FileManager::SaveDevices(devicesList);
                    RefreshGrid();

                    MessageBox::Show(L"Устройство успешно обновлено!",
                        L"Готово", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(L"Ошибка редактирования: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void MainForm::btnDelete_Click(Object^ sender, EventArgs^ e)
    {
        if (dgvDevices->SelectedRows->Count == 0)
        {
            MessageBox::Show(
                L"Выберите устройство для удаления!",
                L"Информация",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );
            return;
        }

        if (MessageBox::Show(
            L"Удалить выбранное устройство?",
            L"Подтверждение",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question
        ) == System::Windows::Forms::DialogResult::Yes)
        {
            try
            {
                int selectedIndex = dgvDevices->SelectedRows[0]->Index;
                if (selectedIndex >= 0 && selectedIndex < devices->Count)
                {
                    devices->RemoveAt(selectedIndex);

                    // Сохраняем в файл
                    List<DeviceData^>^ devicesList = gcnew List<DeviceData^>();
                    for each (DeviceData ^ d in devices)
                        devicesList->Add(d);

                    FileManager::SaveDevices(devicesList);
                    RefreshGrid();

                    MessageBox::Show(
                        L"Устройство успешно удалено!",
                        L"Готово",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information
                    );
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show(
                    L"Ошибка удаления: " + ex->Message,
                    L"Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );
            }
        }
    }

    void MainForm::btnStats_Click(Object^ sender, EventArgs^ e)
    {
        if (devices->Count == 0)
        {
            MessageBox::Show(L"Нет данных для статистики");
            return;
        }

        double total = 0;
        double minPrice = devices[0]->Price;
        double maxPrice = devices[0]->Price;

        for each (DeviceData ^ d in devices)
        {
            total += d->Price;
            if (d->Price < minPrice) minPrice = d->Price;
            if (d->Price > maxPrice) maxPrice = d->Price;
        }

        String^ stats = String::Format(
            L"Статистика устройств:\n\n" +
            L"Всего устройств: {0}\n" +
            L"Общая стоимость: ${1:F2}\n" +
            L"Средняя цена: ${2:F2}\n" +
            L"Минимальная цена: ${3:F2}\n" +
            L"Максимальная цена: ${4:F2}",
            devices->Count, total, total / devices->Count, minPrice, maxPrice
        );

        MessageBox::Show(stats, L"Статистика");
    }

    void MainForm::btnExport_Click(Object^ sender, EventArgs^ e)
    {
        try
        {
            DateTime now = DateTime::Now;
            String^ timestamp = now.ToString("yyyyMMdd_HHmmss");
            String^ fileName = String::Format("devices_export_{0}.txt", timestamp);

            System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(fileName, false, System::Text::Encoding::UTF8);

            writer->WriteLine("=== Экспорт данных об устройствах ===");
            writer->WriteLine(String::Format("Дата экспорта: {0}", now.ToString("dd.MM.yyyy HH:mm:ss")));
            writer->WriteLine("=====================================");
            writer->WriteLine();

            for each (DeviceData ^ d in devices)
            {
                writer->WriteLine("ID: {0}", d->Id);
                writer->WriteLine("Производитель: {0}", d->Manufacturer);
                writer->WriteLine("Модель: {0}", d->Model);
                writer->WriteLine("Тип: {0}", d->Type);
                writer->WriteLine("Цена: ${0:F2}", d->Price);

                if (!String::IsNullOrEmpty(d->AdditionalInfo))
                    writer->WriteLine("Доп. информация: {0}", d->AdditionalInfo);

                writer->WriteLine("---");
            }

            writer->WriteLine();
            writer->WriteLine(String::Format("Всего устройств: {0}", devices->Count));

            double totalCost = 0;
            for each (DeviceData ^ d in devices)
                totalCost += d->Price;

            writer->WriteLine(String::Format("Общая стоимость: ${0:F2}", totalCost));
            writer->Close();

            MessageBox::Show(
                String::Format("Данные экспортированы в файл:\n{0}", fileName),
                "Экспорт завершен",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(
                String::Format("Ошибка при экспорте:\n{0}", ex->Message),
                "Ошибка",
                MessageBoxButtons::OK,
                MessageBoxIcon::Error
            );
        }
    }

    void MainForm::btnRefresh_Click(Object^ sender, EventArgs^ e)
    {
        try
        {
            // Просто загружаем устройства и сбрасываем поиск
            LoadDevices();
            btnResetSearch_Click(sender, e);
            lblStats->Text = L"Данные обновлены: " + DateTime::Now.ToString("HH:mm:ss");
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(
                L"Ошибка при обновлении: " + ex->Message,
                L"Ошибка",
                MessageBoxButtons::OK,
                MessageBoxIcon::Error
            );
        }
    }

    void MainForm::UpdateStats()
    {
        lblStats->Text = String::Format(
            L"Устройств: {0} | Режим: {1} | Последнее обновление: {2}",
            devices->Count,
            isAdminMode ? L"Администратор" : L"Пользователь",
            DateTime::Now.ToString("HH:mm:ss")
        );
    }

    void MainForm::btnLogout_Click(Object^ sender, EventArgs^ e)
    {
        if (MessageBox::Show(
            L"Выйти из системы?",
            L"Подтверждение",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question
        ) == System::Windows::Forms::DialogResult::Yes)
        {
            this->Close();
        }
    }

    void MainForm::dgvDevices_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex >= 0 && e->RowIndex < devices->Count)
        {
            DeviceData^ selectedDevice = devices[e->RowIndex];

            DeviceDetailsForm^ detailsForm = gcnew DeviceDetailsForm(selectedDevice);

            detailsForm->ShowDialog(this);

            List<DeviceData^>^ devicesList = gcnew List<DeviceData^>();
            for each (DeviceData ^ d in devices)
                devicesList->Add(d);

            FileManager::SaveDevices(devicesList);
            RefreshGrid();
        }
    }


    void MainForm::btnRepairs_Click(Object^ sender, EventArgs^ e)
    {
        RepairJournalForm^ repairsForm = gcnew RepairJournalForm(nullptr);
        repairsForm->ShowDialog(this);
    }

    void MainForm::btnSIMCards_Click(Object^ sender, EventArgs^ e)
    {
        SIMCardsForm^ simForm = gcnew SIMCardsForm();
        simForm->ShowDialog(this);
    }

    void MainForm::btnReports_Click(Object^ sender, EventArgs^ e)
    {
        ReportsForm^ reportsForm = gcnew ReportsForm();
        reportsForm->ShowDialog(this);
    }

    void MainForm::btnSettings_Click(Object^ sender, EventArgs^ e)
    {
        SettingsForm^ settingsForm = gcnew SettingsForm();
        settingsForm->ShowDialog(this);
    }

    void MainForm::SetupUI()
    {
        UpdateStats();
    }
}