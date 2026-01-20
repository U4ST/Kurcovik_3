#pragma once

#include "RepairData.h"

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class RepairCompleteForm : public System::Windows::Forms::Form
    {
    private:
        RepairData^ repairData;

        // UI элементы
        DateTimePicker^ dtpRepairDate;
        TextBox^ txtRepairCost;
        TextBox^ txtWorkDescription;
        TextBox^ txtWarrantyDays;
        TextBox^ txtTechnicianName;
        Button^ btnSave;
        Button^ btnCancel;

    public:
        RepairCompleteForm(RepairData^ repair)
        {
            repairData = repair;
            InitializeComponent();
            LoadRepairData();
        }

    private:
        void InitializeComponent();
        void LoadRepairData();
        void btnSave_Click(Object^ sender, EventArgs^ e);
        void btnCancel_Click(Object^ sender, EventArgs^ e);
        void txtRepairCost_KeyPress(Object^ sender, KeyPressEventArgs^ e);
        void txtWarrantyDays_KeyPress(Object^ sender, KeyPressEventArgs^ e);
    };
}