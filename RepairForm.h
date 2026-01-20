#pragma once

#include "DeviceData.h"
#include "RepairData.h"
#include <vector>

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    ref class DeviceSearchForm;

    public ref class RepairForm : public System::Windows::Forms::Form
    {
    private:
        List<DeviceData^>^ availableDevices;
        RepairData^ repairData;

        // UI элементы
        Label^ lblTitle;
        ComboBox^ cmbDevices;
        TextBox^ txtProblemDescription;
        ComboBox^ cmbUrgency;
        TextBox^ txtContactInfo;
        Button^ btnSave;
        Button^ btnCancel;
        Button^ btnSearchDevice;

    public:
        property RepairData^ Repair
        {
            RepairData^ get() { return repairData; }
        }

        RepairForm(List<DeviceData^>^ devices)
        {
            if (devices == nullptr)
                availableDevices = gcnew List<DeviceData^>();
            else
                availableDevices = devices;

            repairData = gcnew RepairData();
            InitializeComponent();
            LoadDevices();
        }

    private:
        void InitializeComponent();
        void LoadDevices();
        void btnSave_Click(Object^ sender, EventArgs^ e);
        void btnCancel_Click(Object^ sender, EventArgs^ e);
        void btnSearchDevice_Click(Object^ sender, EventArgs^ e);
    };

} 