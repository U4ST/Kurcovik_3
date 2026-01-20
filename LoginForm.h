#include "stdafx.h"
#pragma once
#include "MainForm.h"
#include "FileManager.h"

namespace DeviceManagementApp {

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    private:
        TextBox^ txtUsername;
        TextBox^ txtPassword;
        Button^ btnLogin;
        CheckBox^ chkShowPassword;
        Label^ lblStatus;
        Label^ lblTitle;

    public:
        LoginForm(void)
        {
            InitializeComponent();
            FileManager::CreateDefaultUsers();
        }

    private:
        void InitializeComponent()
        {
            this->SuspendLayout();

            //Настройки формы
            this->Text = L"Вход в систему";
            this->Size = System::Drawing::Size(350, 300);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = System::Drawing::Color::WhiteSmoke;

            // Заголовок
            lblTitle = gcnew Label();
            lblTitle->Text = L"Учет электронных устройств";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
            lblTitle->ForeColor = Color::DarkBlue;
            lblTitle->Location = Drawing::Point(20, 20);
            lblTitle->Size = Drawing::Size(300, 30);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(lblTitle);

            // Логин
            Label^ lblUsername = gcnew Label();
            lblUsername->Text = L"Логин:";
            lblUsername->Location = Drawing::Point(50, 70);
            lblUsername->Size = Drawing::Size(80, 25);
            lblUsername->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            this->Controls->Add(lblUsername);

            txtUsername = gcnew TextBox();
            txtUsername->Location = Drawing::Point(140, 70);
            txtUsername->Size = Drawing::Size(150, 25);
            txtUsername->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            this->Controls->Add(txtUsername);

            // Пароль
            Label^ lblPassword = gcnew Label();
            lblPassword->Text = L"Пароль:";
            lblPassword->Location = Drawing::Point(50, 110);
            lblPassword->Size = Drawing::Size(80, 25);
            lblPassword->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            this->Controls->Add(lblPassword);

            txtPassword = gcnew TextBox();
            txtPassword->Location = Drawing::Point(140, 110);
            txtPassword->Size = Drawing::Size(150, 25);
            txtPassword->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            txtPassword->UseSystemPasswordChar = true;
            this->Controls->Add(txtPassword);

            // CheckBox для показа пароля
            chkShowPassword = gcnew CheckBox();
            chkShowPassword->Text = L"Показать пароль";
            chkShowPassword->Location = Drawing::Point(140, 145);
            chkShowPassword->Size = Drawing::Size(150, 25);
            chkShowPassword->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            chkShowPassword->CheckedChanged += gcnew EventHandler(this, &LoginForm::chkShowPassword_CheckedChanged);
            this->Controls->Add(chkShowPassword);

            // Кнопка входа
            btnLogin = gcnew Button();
            btnLogin->Text = L"Войти";
            btnLogin->Location = Drawing::Point(120, 185);
            btnLogin->Size = Drawing::Size(100, 35);
            btnLogin->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            btnLogin->BackColor = Color::LightBlue;
            btnLogin->Click += gcnew EventHandler(this, &LoginForm::btnLogin_Click);
            this->Controls->Add(btnLogin);

            // Статусная метка
            lblStatus = gcnew Label();
            lblStatus->Text = L"Введите логин и пароль";
            lblStatus->Location = Drawing::Point(20, 235);
            lblStatus->Size = Drawing::Size(300, 25);
            lblStatus->TextAlign = ContentAlignment::MiddleCenter;
            lblStatus->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            lblStatus->ForeColor = Color::Gray;
            this->Controls->Add(lblStatus);

            // Тестовые данные для быстрой проверки
            txtUsername->Text = L"admin";
            txtPassword->Text = L"admin123";

            this->AcceptButton = btnLogin;
            this->CancelButton = btnLogin;
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void btnLogin_Click(Object^ sender, EventArgs^ e)
        {
            bool isAdmin = false;

            //Аутентификация пользователя
            if (FileManager::CheckUser(txtUsername->Text, txtPassword->Text, isAdmin))
            {
                lblStatus->Text = L"Вход выполнен!";
                lblStatus->ForeColor = Color::Green;

                MainForm^ mainForm = gcnew MainForm(isAdmin);
                mainForm->Show();
                this->Hide();
            }
            else
            {
                lblStatus->Text = L"Неверный логин или пароль!";
                lblStatus->ForeColor = Color::Red;
                txtPassword->Text = L"";
                txtPassword->Focus();
            }
        }

        void chkShowPassword_CheckedChanged(Object^ sender, EventArgs^ e)
        {
            txtPassword->UseSystemPasswordChar = !chkShowPassword->Checked;
        }

    private:
        System::Void LoginForm_Load(System::Object^ sender, System::EventArgs^ e)
        {
            // Фокусируемся на поле ввода логина
            txtUsername->Focus();
            txtUsername->SelectAll();
        }
    };
}
