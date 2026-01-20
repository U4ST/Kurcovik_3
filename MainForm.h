#pragma once

#include "DeviceData.h"
#include "FileManager.h"
#include "AddEditForm.h"
#include "DeviceDetailsForm.h"

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::ComponentModel;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    private:
        BindingList<DeviceData^>^ devices;
        bool isAdminMode;
        String^ sortColumn;
        bool sortAscending;

        // UI элементы
        Label^ lblTitle;
        DataGridView^ dgvDevices;
        Button^ btnRefresh;
        Button^ btnAdd;
        Button^ btnEdit;
        Button^ btnDelete;
        Button^ btnStats;
        Button^ btnExport;
        Button^ btnLogout;

        // Элементы для комбинированного поиска
        Label^ lblSearchType;
        ComboBox^ cmbSearchType;
        Panel^ pnlTextSearch;
        Panel^ pnlPriceSearch;
        Panel^ pnlCombinedSearch;
        Button^ btnSearch;
        Button^ btnResetSearch;
        Label^ lblStats;

        // Элементы для текстового поиска
        TextBox^ txtTextSearch;

        // Элементы для поиска по цене
        Label^ lblPriceFrom;
        TextBox^ txtPriceFrom;
        Label^ lblPriceTo;
        TextBox^ txtPriceTo;

        // Элементы для комбинированного поиска
        TextBox^ txtCombinedText;
        TextBox^ txtCombinedPriceFrom;
        TextBox^ txtCombinedPriceTo;
        ComboBox^ cmbCombinedType;
        ComboBox^ cmbCombinedStatus;

        // Кнопки сортировки
        Button^ btnSortManufacturer;
        Button^ btnSortPrice;
        Button^ btnSortType;

        //Кнопки для ремонта и Sim-cards
        Button^ btnRepairs;
        Button^ btnSIMCards;
        Button^ btnReports;
        Button^ btnSettings;
    public:
        MainForm(bool adminMode)
        {
            isAdminMode = adminMode;
            devices = gcnew BindingList<DeviceData^>();
            sortColumn = L"";
            sortAscending = true;
            InitializeComponent();
            LoadDevices();
            SetupDataGridView();
            UpdateStats();
        }

        property List<DeviceData^>^ Devices
        {
            List<DeviceData^>^ get()
            {
                List<DeviceData^>^ list = gcnew List<DeviceData^>();
                for each (DeviceData ^ device in devices)
                    list->Add(device);
                return list;
            }
        }

    private:
        void InitializeComponent();
        void SetupDataGridView();

        // Методы загрузки и обновления данных
        void LoadDevices();
        void RefreshGrid();
        void UpdateStats();
        void UpdateSortButtonStyles();

        // Методы сортировки
        void SortDevices(String^ column);
        void btnSortManufacturer_Click(Object^ sender, EventArgs^ e);
        void btnSortPrice_Click(Object^ sender, EventArgs^ e);
        void btnSortType_Click(Object^ sender, EventArgs^ e);

        static int CompareByManufacturerAsc(DeviceData^ x, DeviceData^ y);
        static int CompareByManufacturerDesc(DeviceData^ x, DeviceData^ y);
        static int CompareByPriceAsc(DeviceData^ x, DeviceData^ y);
        static int CompareByPriceDesc(DeviceData^ x, DeviceData^ y);
        static int CompareByTypeAsc(DeviceData^ x, DeviceData^ y);
        static int CompareByTypeDesc(DeviceData^ x, DeviceData^ y);

        // Методы поиска
        void cmbSearchType_Changed(Object^ sender, EventArgs^ e);
        void btnSearch_Click(Object^ sender, EventArgs^ e);
        void btnResetSearch_Click(Object^ sender, EventArgs^ e);

        List<DeviceData^>^ PerformTextSearch();
        List<DeviceData^>^ PerformPriceSearch();
        List<DeviceData^>^ PerformCombinedSearch();
        String^ GetSearchDescription(int searchType);
        void ShowFilteredResults(List<DeviceData^>^ filtered, String^ searchInfo);

        // Методы защиты ввода
        void txtPrice_KeyPress(Object^ sender, KeyPressEventArgs^ e);

        // Основные методы управления
        void btnAdd_Click(Object^ sender, EventArgs^ e);
        void btnEdit_Click(Object^ sender, EventArgs^ e);
        void btnDelete_Click(Object^ sender, EventArgs^ e);
        void btnStats_Click(Object^ sender, EventArgs^ e);
        void btnExport_Click(Object^ sender, EventArgs^ e);
        void btnRefresh_Click(Object^ sender, EventArgs^ e);
        void btnLogout_Click(Object^ sender, EventArgs^ e);


        void btnRepairs_Click(Object^ sender, EventArgs^ e);
        void btnSIMCards_Click(Object^ sender, EventArgs^ e);
        void btnReports_Click(Object^ sender, EventArgs^ e);
        void btnSettings_Click(Object^ sender, EventArgs^ e);



        void dgvDevices_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e);
        void SetupUI();
    };
}