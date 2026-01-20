#pragma once

#include "DeviceData.h"
#include "RepairData.h"
#include "RepairCompleteForm.h"
#include <vector>

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::ComponentModel;

    public ref class RepairJournalForm : public System::Windows::Forms::Form
    {
    private:
        BindingList<RepairData^>^ repairs;
        List<DeviceData^>^ availableDevices;
        String^ lastFilterStatus; 

        // UI элементы
        Label^ lblTitle;
        DataGridView^ dgvRepairs;
        Button^ btnNewRepair;
        Button^ btnCompleteRepair;
        Button^ btnRefresh;
        Button^ btnExport;
        Button^ btnClose;
        ComboBox^ cmbStatusFilter;

    public:
        RepairJournalForm::RepairJournalForm(List<DeviceData^>^ devices)
        {
            repairs = gcnew BindingList<RepairData^>();
            availableDevices = devices;
            lastFilterStatus = L"Все статусы";  
            InitializeComponent();
            LoadRepairs();
        }

    private:
        void InitializeComponent();
        void LoadRepairs();
        void SetupDataGridView();
        void btnNewRepair_Click(Object^ sender, EventArgs^ e);
        void btnCompleteRepair_Click(Object^ sender, EventArgs^ e);
        void btnRefresh_Click(Object^ sender, EventArgs^ e);
        void btnExport_Click(Object^ sender, EventArgs^ e);
        void btnClose_Click(Object^ sender, EventArgs^ e);
        void cmbStatusFilter_Changed(Object^ sender, EventArgs^ e);
        void dgvRepairs_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e);
        void ShowRepairDetails(RepairData^ repair);

        // Методы фильтрации
        void ApplyStatusFilter();
        void UpdateTitleWithCount();

        // Методы работы с данными
        List<RepairData^>^ LoadRepairsFromFile();
        void SaveRepairsToFile();
        void AddTestData();
    };
}