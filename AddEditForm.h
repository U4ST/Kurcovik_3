#pragma once

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "DeviceData.h"
#include "FileManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Globalization;

namespace DeviceManagementApp {

    public ref class AddEditForm : public System::Windows::Forms::Form
    {
    public:
        property String^ Manufacturer
        {
            String^ get() { return _manufacturer; }
            void set(String^ value) { _manufacturer = value; }
        }
        property String^ Model
        {
            String^ get() { return _model; }
            void set(String^ value) { _model = value; }
        }
        property String^ Type
        {
            String^ get() { return _type; }
            void set(String^ value) { _type = value; }
        }
        property double Price
        {
            double get() { return _price; }
            void set(double value) { _price = value; }
        }
        property String^ AdditionalInfo
        {
            String^ get() { return _additionalInfo; }
            void set(String^ value) { _additionalInfo = value; }
        }

        property String^ IMEI
        {
            String^ get() { return _imei; }
            void set(String^ value) { _imei = value; }
        }

        property String^ SerialNumber
        {
            String^ get() { return _serialNumber; }
            void set(String^ value) { _serialNumber = value; }
        }

        property String^ Status
        {
            String^ get() { return _status; }
            void set(String^ value) { _status = value; }
        }

        property String^ Owner
        {
            String^ get() { return _owner; }
            void set(String^ value) { _owner = value; }
        }

    private:
        TextBox^ txtManufacturer;
        TextBox^ txtModel;
        ComboBox^ cmbType;
        TextBox^ txtPrice;
        TextBox^ txtAdditional;
        Button^ btnSave;
        Button^ btnCancel;
        Label^ lblId;
        DeviceData^ editingDevice;

        TextBox^ txtIMEI;
        TextBox^ txtSerialNumber;
        ComboBox^ cmbStatus;
        TextBox^ txtOwner;

        String^ _manufacturer;
        String^ _model;
        String^ _type;
        double _price;
        String^ _additionalInfo;

        String^ _imei;
        String^ _serialNumber;
        String^ _status;
        String^ _owner;

    public:
        AddEditForm() : editingDevice(nullptr)
        {
            InitializeComponent();
            this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
        }

        AddEditForm(DeviceData^ device) : editingDevice(device)
        {
            InitializeComponent();
            this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
        }

    private:
        void InitializeComponent();
        void LoadDataToForm();
        void btnSave_Click(Object^ sender, EventArgs^ e);
        bool ValidateInput();
        void SaveFormData();
        void ShowError(String^ message);

        void txtPrice_KeyPress(Object^ sender, KeyPressEventArgs^ e);
        void txtIMEI_KeyPress(Object^ sender, KeyPressEventArgs^ e);
        void txtSerialNumber_KeyPress(Object^ sender, KeyPressEventArgs^ e);
    };
}