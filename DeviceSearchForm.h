#pragma once

#include "DeviceData.h"

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    ref class DeviceSearchForm : public System::Windows::Forms::Form
    {
    private:
        DataGridView^ dgvDevices;
        TextBox^ txtSearch;
        List<DeviceData^>^ availableDevices;
        int selectedIndex;

        void InitializeComponent();
        void LoadDevices();
        void txtSearch_TextChanged(Object^ sender, EventArgs^ e);
        void btnSelect_Click(Object^ sender, EventArgs^ e);

    public:
        DeviceSearchForm(List<DeviceData^>^ devices);

        property int SelectedIndex
        {
            int get() { return selectedIndex; }
        }
    };
}