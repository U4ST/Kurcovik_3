#include "stdafx.h"
#include "RepairJournalForm.h"
#include "DeviceData.h"
#include "RepairForm.h"
#include <msclr/marshal_cppstd.h>

#include "MainForm.h"

namespace DeviceManagementApp {


    void RepairJournalForm::InitializeComponent()
    {
        this->Text = L"Журнал ремонтов";
        this->Size = System::Drawing::Size(1000, 600);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::WhiteSmoke;

        lblTitle = gcnew Label();
        lblTitle->Text = L"Журнал ремонтов";
        lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
        lblTitle->Location = Point(20, 20);
        lblTitle->Size = Drawing::Size(300, 30);
        lblTitle->ForeColor = Color::DarkBlue;
        this->Controls->Add(lblTitle);

        // Фильтр по статусу
        Label^ lblFilter = gcnew Label();
        lblFilter->Text = L"Фильтр по статусу:";
        lblFilter->Location = Point(20, 65);
        lblFilter->Size = Drawing::Size(120, 25);
        lblFilter->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        this->Controls->Add(lblFilter);

        cmbStatusFilter = gcnew ComboBox();
        cmbStatusFilter->Location = Point(150, 65);
        cmbStatusFilter->Size = Drawing::Size(150, 25);
        cmbStatusFilter->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        cmbStatusFilter->DropDownStyle = ComboBoxStyle::DropDownList;
        cmbStatusFilter->Items->Add(L"Все статусы");
        cmbStatusFilter->Items->AddRange(gcnew cli::array<String^>(4) {
            L"Создана", L"В работе", L"Выполнена", L"Закрыта"
        });
        cmbStatusFilter->SelectedIndex = 0;
        cmbStatusFilter->SelectedIndexChanged += gcnew EventHandler(this, &RepairJournalForm::cmbStatusFilter_Changed);
        this->Controls->Add(cmbStatusFilter);

        // DataGridView
        dgvRepairs = gcnew DataGridView();
        dgvRepairs->Location = Point(20, 100);
        dgvRepairs->Size = Drawing::Size(940, 350);
        dgvRepairs->ReadOnly = true;
        dgvRepairs->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        dgvRepairs->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        dgvRepairs->AllowUserToAddRows = false;
        dgvRepairs->RowHeadersVisible = false;
        dgvRepairs->BackgroundColor = Color::White;
        this->Controls->Add(dgvRepairs);

        // Кнопки
        int yPos = 470;
        int xPos = 20;
        int buttonWidth = 120;
        int buttonHeight = 35;

        btnNewRepair = gcnew Button();
        btnNewRepair->Text = L"Новая заявка";
        btnNewRepair->Location = Point(xPos, yPos);
        btnNewRepair->Size = Drawing::Size(buttonWidth, buttonHeight);
        btnNewRepair->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
        btnNewRepair->BackColor = Color::LightGreen;
        btnNewRepair->Click += gcnew EventHandler(this, &RepairJournalForm::btnNewRepair_Click);
        this->Controls->Add(btnNewRepair);

        btnCompleteRepair = gcnew Button();
        btnCompleteRepair->Text = L"Завершить ремонт";
        btnCompleteRepair->Location = Point(xPos + 130, yPos);
        btnCompleteRepair->Size = Drawing::Size(buttonWidth, buttonHeight);
        btnCompleteRepair->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnCompleteRepair->BackColor = Color::LightBlue;
        btnCompleteRepair->Click += gcnew EventHandler(this, &RepairJournalForm::btnCompleteRepair_Click);
        this->Controls->Add(btnCompleteRepair);

        btnRefresh = gcnew Button();
        btnRefresh->Text = L"Обновить";
        btnRefresh->Location = Point(xPos + 260, yPos);
        btnRefresh->Size = Drawing::Size(buttonWidth, buttonHeight);
        btnRefresh->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnRefresh->BackColor = Color::LightGray;
        btnRefresh->Click += gcnew EventHandler(this, &RepairJournalForm::btnRefresh_Click);
        this->Controls->Add(btnRefresh);

        btnExport = gcnew Button();
        btnExport->Text = L"Экспорт";
        btnExport->Location = Point(xPos + 390, yPos);
        btnExport->Size = Drawing::Size(buttonWidth, buttonHeight);
        btnExport->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnExport->BackColor = Color::LightCyan;
        btnExport->Click += gcnew EventHandler(this, &RepairJournalForm::btnExport_Click);
        this->Controls->Add(btnExport);

        btnClose = gcnew Button();
        btnClose->Text = L"Закрыть";
        btnClose->Location = Point(840, yPos);
        btnClose->Size = Drawing::Size(buttonWidth, buttonHeight);
        btnClose->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
        btnClose->BackColor = Color::LightCoral;
        btnClose->Click += gcnew EventHandler(this, &RepairJournalForm::btnClose_Click);
        this->Controls->Add(btnClose);

        // Добавляем обработчик двойного клика
        dgvRepairs->CellDoubleClick += gcnew DataGridViewCellEventHandler(
            this, &RepairJournalForm::dgvRepairs_CellDoubleClick);

     

        SetupDataGridView();
    }
 

    void RepairJournalForm::dgvRepairs_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex >= 0 && e->RowIndex < repairs->Count)
        {
            RepairData^ selectedRepair = repairs[e->RowIndex];
            ShowRepairDetails(selectedRepair);
        }
    }

    void RepairJournalForm::SetupDataGridView()
    {
        dgvRepairs->AutoGenerateColumns = false;
        dgvRepairs->Columns->Clear();

        // ID
        DataGridViewTextBoxColumn^ colId = gcnew DataGridViewTextBoxColumn();
        colId->HeaderText = L"ID";
        colId->DataPropertyName = L"Id";
        colId->Width = 50;
        dgvRepairs->Columns->Add(colId);

        // Устройство
        DataGridViewTextBoxColumn^ colDevice = gcnew DataGridViewTextBoxColumn();
        colDevice->HeaderText = L"Устройство";
        colDevice->DataPropertyName = L"DeviceModel";
        colDevice->Width = 150;
        dgvRepairs->Columns->Add(colDevice);

        // IMEI
        DataGridViewTextBoxColumn^ colIMEI = gcnew DataGridViewTextBoxColumn();
        colIMEI->HeaderText = L"IMEI";
        colIMEI->DataPropertyName = L"DeviceIMEI";
        colIMEI->Width = 120;
        dgvRepairs->Columns->Add(colIMEI);

        // Статус
        DataGridViewTextBoxColumn^ colStatus = gcnew DataGridViewTextBoxColumn();
        colStatus->HeaderText = L"Статус";
        colStatus->DataPropertyName = L"Status";
        colStatus->Width = 100;
        dgvRepairs->Columns->Add(colStatus);

        // Срочность
        DataGridViewTextBoxColumn^ colUrgency = gcnew DataGridViewTextBoxColumn();
        colUrgency->HeaderText = L"Срочность";
        colUrgency->DataPropertyName = L"Urgency";
        colUrgency->Width = 80;
        dgvRepairs->Columns->Add(colUrgency);

        // Дата создания
        DataGridViewTextBoxColumn^ colCreated = gcnew DataGridViewTextBoxColumn();
        colCreated->HeaderText = L"Дата создания";
        colCreated->DataPropertyName = L"CreatedDate";
        colCreated->Width = 120;
        colCreated->DefaultCellStyle->Format = "dd.MM.yyyy";
        dgvRepairs->Columns->Add(colCreated);

        // Описание проблемы
        DataGridViewTextBoxColumn^ colProblem = gcnew DataGridViewTextBoxColumn();
        colProblem->HeaderText = L"Описание проблемы";
        colProblem->DataPropertyName = L"ProblemDescription";
        colProblem->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
        dgvRepairs->Columns->Add(colProblem);
    }

    void RepairJournalForm::LoadRepairs()
    {
        repairs->Clear();
        List<RepairData^>^ loadedRepairs = LoadRepairsFromFile();

        for each (RepairData ^ repair in loadedRepairs)
        {
            repairs->Add(repair);
        }

        // Восстанавливаем предыдущий фильтр, если был
        if (!String::IsNullOrEmpty(lastFilterStatus))
        {
            for (int i = 0; i < cmbStatusFilter->Items->Count; i++)
            {
                if (cmbStatusFilter->Items[i]->ToString() == lastFilterStatus)
                {
                    cmbStatusFilter->SelectedIndex = i;
                    break;
                }
            }
        }

        ApplyStatusFilter();

        if (repairs->Count == 0)
        {
            AddTestData();
            ApplyStatusFilter();
        }
    }

    List<RepairData^>^ RepairJournalForm::LoadRepairsFromFile()
    {
        List<RepairData^>^ repairsList = gcnew List<RepairData^>();
        String^ filePath = "repairs.txt";

        if (!System::IO::File::Exists(filePath))
            return repairsList;

        try
        {
            array<String^>^ lines = System::IO::File::ReadAllLines(filePath, System::Text::Encoding::UTF8);

            for each (String ^ line in lines)
            {
                if (String::IsNullOrEmpty(line))
                    continue;

                array<String^>^ parts = line->Split('|');
                if (parts->Length >= 8)
                {
                    RepairData^ repair = gcnew RepairData();
                    repair->Id = Int32::Parse(parts[0]);
                    repair->DeviceId = Int32::Parse(parts[1]);
                    repair->DeviceIMEI = parts[2];
                    repair->DeviceModel = parts[3];
                    repair->ProblemDescription = parts[4];
                    repair->Urgency = parts[5];
                    repair->ContactInfo = parts[6];
                    repair->Status = parts[7];
                    repair->CreatedDate = DateTime::Parse(parts[8]);

                    if (parts->Length > 9 && !String::IsNullOrEmpty(parts[9]))
                        repair->RepairDate = DateTime::Parse(parts[9]);

                    if (parts->Length > 10 && !String::IsNullOrEmpty(parts[10]))
                        repair->RepairCost = Double::Parse(parts[10]);

                    repairsList->Add(repair);
                }
            }
        }
        catch (Exception^ ex)
        {
            System::Diagnostics::Debug::WriteLine("Ошибка загрузки ремонтов: " + ex->Message);
        }

        return repairsList;
    }

    void RepairJournalForm::SaveRepairsToFile()
    {
        String^ filePath = "repairs.txt";
        List<String^>^ lines = gcnew List<String^>();

        for each (RepairData ^ repair in repairs)
        {
            String^ line = String::Format("{0}|{1}|{2}|{3}|{4}|{5}|{6}|{7}|{8}|{9}|{10}|{11}",
                repair->Id,
                repair->DeviceId,
                repair->DeviceIMEI,
                repair->DeviceModel,
                repair->ProblemDescription,
                repair->Urgency,
                repair->ContactInfo,
                repair->Status,
                repair->CreatedDate.ToString("o"),
                (repair->RepairDate == DateTime::MinValue) ? "" : repair->RepairDate.ToString("o"),
                repair->RepairCost,
                repair->WarrantyDays);

            lines->Add(line);
        }

        System::IO::File::WriteAllLines(filePath, lines->ToArray(), System::Text::Encoding::UTF8);
    }

    void RepairJournalForm::AddTestData()
    {
        // Добавляем тестовые данные
        RepairData^ repair1 = gcnew RepairData();
        repair1->Id = 1;
        repair1->DeviceModel = L"iPhone 13";
        repair1->DeviceIMEI = L"123456789012345";
        repair1->ProblemDescription = L"Не работает экран";
        repair1->Urgency = L"Высокая";
        repair1->Status = L"В работе";
        repair1->CreatedDate = DateTime::Now.AddDays(-2);
        repairs->Add(repair1);

        RepairData^ repair2 = gcnew RepairData();
        repair2->Id = 2;
        repair2->DeviceModel = L"Samsung Galaxy S21";
        repair2->DeviceIMEI = L"987654321098765";
        repair2->ProblemDescription = L"Не держит заряд батареи";
        repair2->Urgency = L"Средняя";
        repair2->Status = L"Создана";
        repair2->CreatedDate = DateTime::Now.AddDays(-1);
        repairs->Add(repair2);

        SaveRepairsToFile();
    }

    void RepairJournalForm::btnNewRepair_Click(Object^ sender, EventArgs^ e)
    {
        try
        {
            // Если нет устройств, создаем простые тестовые
            if (availableDevices == nullptr || availableDevices->Count == 0)
            {
                availableDevices = gcnew List<DeviceData^>();

                // Просто 2 тестовых устройства
                DeviceData^ device1 = gcnew DeviceData();
                device1->Id = 1;
                device1->Model = L"Тестовый смартфон 1";
                device1->IMEI = L"111111111111111";
                device1->SerialNumber = L"TEST001";
                availableDevices->Add(device1);

                DeviceData^ device2 = gcnew DeviceData();
                device2->Id = 2;
                device2->Model = L"Тестовый смартфон 2";
                device2->IMEI = L"222222222222222";
                device2->SerialNumber = L"TEST002";
                availableDevices->Add(device2);
            }

            // Создаем форму ремонта
            RepairForm^ repairForm = gcnew RepairForm(availableDevices);

            if (repairForm->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
            {
                RepairData^ newRepair = repairForm->Repair;

                // Простой ID - следующий номер
                newRepair->Id = repairs->Count + 1;
                repairs->Add(newRepair);
                SaveRepairsToFile();

                // Обновляем фильтр
                ApplyStatusFilter();

                MessageBox::Show(String::Format(L"Заявка на ремонт создана! ID: {0}", newRepair->Id),
                    L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }

        }
        catch (Exception^ ex)
        {
            MessageBox::Show(L"Ошибка: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void RepairJournalForm::btnCompleteRepair_Click(Object^ sender, EventArgs^ e)
    {
        if (dgvRepairs->SelectedRows->Count == 0)
        {
            MessageBox::Show(L"Выберите заявку для завершения!",
                L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        int selectedIndex = dgvRepairs->SelectedRows[0]->Index;
        RepairData^ selectedRepair = nullptr;

        // Получаем выбранную заявку с учетом фильтра
        BindingList<RepairData^>^ currentDataSource = safe_cast<BindingList<RepairData^>^>(dgvRepairs->DataSource);
        if (selectedIndex >= 0 && selectedIndex < currentDataSource->Count)
        {
            selectedRepair = currentDataSource[selectedIndex];
        }

        if (selectedRepair != nullptr)
        {
            if (selectedRepair->Status == L"Выполнена" || selectedRepair->Status == L"Закрыта")
            {
                MessageBox::Show(L"Этот ремонт уже завершен!",
                    L"Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            RepairCompleteForm^ completeForm = gcnew RepairCompleteForm(selectedRepair);
            if (completeForm->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
            {
                selectedRepair->Status = L"Выполнена";
                selectedRepair->CompletedDate = DateTime::Now;
                SaveRepairsToFile();

                // Обновляем фильтр
                ApplyStatusFilter();

                MessageBox::Show(L"Ремонт успешно завершен!",
                    L"Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
    }

    void RepairJournalForm::btnRefresh_Click(Object^ sender, EventArgs^ e)
    {
        LoadRepairs();
        ApplyStatusFilter();  // Применить текущий фильтр после загрузки
    }

    void RepairJournalForm::btnExport_Click(Object^ sender, EventArgs^ e)
    {
        try
        {
            DateTime now = DateTime::Now;
            String^ fileName = String::Format("repairs_export_{0:yyyyMMdd_HHmmss}.csv", now);

            System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(fileName, false, System::Text::Encoding::UTF8);

            writer->WriteLine("ID;Устройство;IMEI;Статус;Срочность;Дата создания;Описание проблемы");

            for each (RepairData ^ repair in repairs)
            {
                writer->WriteLine(String::Format("{0};{1};{2};{3};{4};{5:dd.MM.yyyy};{6}",
                    repair->Id,
                    repair->DeviceModel,
                    repair->DeviceIMEI,
                    repair->Status,
                    repair->Urgency,
                    repair->CreatedDate,
                    repair->ProblemDescription));
            }

            writer->Close();

            MessageBox::Show(String::Format("Данные экспортированы в файл:\n{0}", fileName),
                "Экспорт завершен", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(String::Format("Ошибка при экспорте:\n{0}", ex->Message),
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void RepairJournalForm::btnClose_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }

    void RepairJournalForm::cmbStatusFilter_Changed(Object^ sender, EventArgs^ e)
    {
        if (cmbStatusFilter->SelectedIndex >= 0)
        {
            lastFilterStatus = cmbStatusFilter->SelectedItem->ToString();
            ApplyStatusFilter();
        }
    }

    void RepairJournalForm::ApplyStatusFilter()
    {
        if (cmbStatusFilter->SelectedIndex == 0)
        {
            // "Все статусы" - показываем все записи
            dgvRepairs->DataSource = repairs;
        }
        else
        {
            String^ selectedStatus = cmbStatusFilter->SelectedItem->ToString();

            // Создаем фильтрованный список
            BindingList<RepairData^>^ filteredRepairs = gcnew BindingList<RepairData^>();

            for each (RepairData ^ repair in repairs)
            {
                if (repair->Status == selectedStatus)
                {
                    filteredRepairs->Add(repair);
                }
            }

            // Показываем отфильтрованные данные
            dgvRepairs->DataSource = filteredRepairs;
        }

        // Обновляем заголовок с количеством записей
        UpdateTitleWithCount();
    }

   

    void RepairJournalForm::UpdateTitleWithCount()
    {
        int totalCount = repairs->Count;
        int filteredCount = 0;

        if (cmbStatusFilter->SelectedIndex == 0)
        {
            filteredCount = totalCount;
        }
        else
        {
            String^ selectedStatus = cmbStatusFilter->SelectedItem->ToString();
            for each (RepairData ^ repair in repairs)
            {
                if (repair->Status == selectedStatus)
                {
                    filteredCount++;
                }
            }
        }

        String^ statusText = cmbStatusFilter->SelectedItem->ToString();
        lblTitle->Text = String::Format(L"Журнал ремонтов ({0}/{1}) - {2}",
            filteredCount, totalCount, statusText);
    }

    void RepairJournalForm::ShowRepairDetails(RepairData^ repair)
    {
        try
        {
            // Формируем текст для MessageBox
            String^ details = String::Format(
                L"Детали заявки на ремонт\n\n" +
                L"ID: {0}\n" +
                L"Устройство: {1}\n" +
                L"IMEI: {2}\n" +
                L"Проблема: {3}\n" +
                L"Статус: {4}\n" +
                L"Срочность: {5}\n" +
                L"Дата: {6:dd.MM.yyyy}",
                repair->Id,
                repair->DeviceModel,
                repair->DeviceIMEI,
                repair->ProblemDescription,
                repair->Status,
                repair->Urgency,
                repair->CreatedDate
            );
            MessageBox::Show(details, L"Информация о ремонте",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex)
        {
            MessageBox::Show(L"Ошибка: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}