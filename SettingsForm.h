#pragma once

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SettingsForm : public System::Windows::Forms::Form
    {
    public:
        SettingsForm()
        {
            InitializeComponent();
        }

    private:
        void InitializeComponent();
    };
}