#pragma once

#include "SIMCardData.h"

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SIMCardEditForm : public System::Windows::Forms::Form
    {
    private:
        SIMCardData^ simCard;

        // UI элементы
        TextBox^ txtPhoneNumber;
        ComboBox^ cmbOperator;
        TextBox^ txtTariffPlan;
        TextBox^ txtMonthlyCost;
        TextBox^ txtDataLimit;
        TextBox^ txtMinutesLimit;
        TextBox^ txtSMSLimit;
        DateTimePicker^ dtpExpiryDate;
        CheckBox^ chkActive;
        TextBox^ txtDeviceIMEI;
        TextBox^ txtDeviceModel;
        TextBox^ txtNotes;
        Button^ btnSave;
        Button^ btnCancel;

    public:
        property SIMCardData^ SIMCard
        {
            SIMCardData^ get() { return simCard; }
        }

        SIMCardEditForm(SIMCardData^ card)
        {
            simCard = (card == nullptr) ? gcnew SIMCardData() : card;
            InitializeComponent();
            LoadDataToForm();
        }

    private:
        void InitializeComponent();
        void LoadDataToForm();
        void btnSave_Click(Object^ sender, EventArgs^ e);
        void btnCancel_Click(Object^ sender, EventArgs^ e);
        void txtMonthlyCost_KeyPress(Object^ sender, KeyPressEventArgs^ e);
        void txtDataLimit_KeyPress(Object^ sender, KeyPressEventArgs^ e);
        void txtPhoneNumber_KeyPress(Object^ sender, KeyPressEventArgs^ e);
        void txtDeviceIMEI_KeyPress(Object^ sender, KeyPressEventArgs^ e);

        void txtPhoneNumber_Leave(Object^ sender, EventArgs^ e);
        void txtDeviceIMEI_Leave(Object^ sender, EventArgs^ e);
        void txtMonthlyCost_Leave(Object^ sender, EventArgs^ e);
        void txtDataLimit_Leave(Object^ sender, EventArgs^ e);
    };
}