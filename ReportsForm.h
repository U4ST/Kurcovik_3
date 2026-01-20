#pragma once

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ReportsForm : public System::Windows::Forms::Form
    {
    public:
        ReportsForm()
        {
            InitializeComponent();
        }

    private:
        void InitializeComponent();
    };
}