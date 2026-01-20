#pragma once

#include "SIMCardData.h"
#include "SIMCardEditForm.h"

namespace DeviceManagementApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::ComponentModel;

    ref class SIMCardInfoForm : public System::Windows::Forms::Form
    {
    private:
        SIMCardData^ card;
        void btnClose_Click(Object^ sender, EventArgs^ e);

    public:
        SIMCardInfoForm(SIMCardData^ simCard);

    private:
        void InitializeComponent();
    };

    // Основной класс формы
    public ref class SIMCardsForm : public System::Windows::Forms::Form
    {
    private:
        BindingList<SIMCardData^>^ simCards;
        System::Windows::Forms::Timer^ warningTimer;

        // UI элементы
        Label^ lblTitle;
        DataGridView^ dgvSIMCards;
        Button^ btnAdd;
        Button^ btnEdit;
        Button^ btnDelete;
        Button^ btnRefresh;
        Button^ btnClose;
        Panel^ pnlWarnings;
        Label^ lblWarnings;

    public:
        SIMCardsForm()
        {
            simCards = gcnew BindingList<SIMCardData^>();
            InitializeComponent();
            LoadSIMCards();
            SetupWarningTimer();
        }

        ~SIMCardsForm()
        {
            if (warningTimer != nullptr)
            {
                warningTimer->Stop();
                delete warningTimer;
            }
        }

    private:
        void InitializeComponent();
        void LoadSIMCards();
        void SetupDataGridView();
        void SetupWarningTimer();
        void CheckForWarnings();
        void UpdateWarningsDisplay();

        void btnAdd_Click(Object^ sender, EventArgs^ e);
        void btnEdit_Click(Object^ sender, EventArgs^ e);
        void btnDelete_Click(Object^ sender, EventArgs^ e);
        void btnRefresh_Click(Object^ sender, EventArgs^ e);
        void btnClose_Click(Object^ sender, EventArgs^ e);
        void warningTimer_Tick(Object^ sender, EventArgs^ e);
        void dgvSIMCards_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e);

        // Методы работы с данными
        List<SIMCardData^>^ LoadSIMCardsFromFile();
        void SaveSIMCardsToFile();
        void AddTestData();
    };
}