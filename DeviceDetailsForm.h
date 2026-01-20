#pragma once

#include "DeviceData.h"

namespace DeviceManagementApp {
    ref class MainForm; 
}

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class DeviceDetailsForm : public System::Windows::Forms::Form
    {
    private:
        DeviceData^ device;
        MainForm^ parentForm; 

        // UI элементы
        Label^ lblTitle;
        Label^ lblManufacturer;
        Label^ lblModel;
        Label^ lblType;
        Label^ lblPrice;
        Label^ lblIMEI;
        Label^ lblSerialNumber;
        Label^ lblStatus;
        Label^ lblOwner;
        Label^ lblAdditionalInfo;

        Button^ btnClose;
        Button^ btnEdit;

    public:
        DeviceDetailsForm(DeviceData^ deviceData)
        {
            device = deviceData;
            InitializeComponent();
            LoadDeviceDetails();
        }

        DeviceDetailsForm(DeviceData^ deviceData, MainForm^ parent)
        {
            device = deviceData;
            parentForm = parent;
            InitializeComponent();
            LoadDeviceDetails();
        }

    private:
        void InitializeComponent();
        void LoadDeviceDetails();
        void btnClose_Click(Object^ sender, EventArgs^ e);
        void btnEdit_Click(Object^ sender, EventArgs^ e);
    };
}