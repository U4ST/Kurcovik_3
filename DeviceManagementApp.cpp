#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    try
    {
        DeviceManagementApp::LoginForm^ loginForm = gcnew DeviceManagementApp::LoginForm();
        Application::Run(loginForm);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Ошибка запуска приложения: " + ex->Message,
            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return 1;
    }

    return 0;
}