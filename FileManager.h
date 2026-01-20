#include "stdafx.h"
#pragma once
#include "DeviceData.h"
#include <fstream>
#include <sstream>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Text;

public ref class FileManager
{
private:
    static String^ usersFile = "users.txt";
    static String^ devicesFile = "devices.txt";

public:
    static List<DeviceData^>^ LoadDevices()
    {
        List<DeviceData^>^ devices = gcnew List<DeviceData^>();

        if (!File::Exists(devicesFile))
            return devices;

        try
        {
            array<String^>^ lines = File::ReadAllLines(devicesFile, Encoding::UTF8);

            for each (String ^ line in lines)
            {
                if (String::IsNullOrEmpty(line))
                    continue;

                array<String^>^ parts = line->Split(',');

                // Увеличиваем количество полей до 10 (для всех свойств)
                if (parts->Length >= 6)
                {
                    try
                    {
                        int id = Int32::Parse(parts[0]);
                        String^ manufacturer = parts[1];
                        String^ modelName = parts[2];
                        String^ deviceType = parts[3];
                        double price = Double::Parse(parts[4]);
                        String^ additional = parts[5];

                        // Получаем новые поля (с проверкой на длину массива)
                        String^ imei = (parts->Length > 6 && !String::IsNullOrEmpty(parts[6])) ? parts[6] : "";
                        String^ serialNumber = (parts->Length > 7 && !String::IsNullOrEmpty(parts[7])) ? parts[7] : "";
                        String^ status = (parts->Length > 8 && !String::IsNullOrEmpty(parts[8])) ? parts[8] : "На складе";
                        String^ owner = (parts->Length > 9 && !String::IsNullOrEmpty(parts[9])) ? parts[9] : "";

                        //Используем полный конструктор со всеми параметрами
                        DeviceData^ device = gcnew DeviceData(
                            id,
                            manufacturer,
                            modelName,
                            deviceType,
                            price,
                            additional,
                            imei,
                            serialNumber,
                            status,
                            owner
                        );

                        devices->Add(device);
                    }
                    catch (FormatException^ fe)
                    {
                        System::Diagnostics::Debug::WriteLine("Ошибка парсинга строки: " + line + " - " + fe->Message);
                        continue;
                    }
                    catch (Exception^ ex)
                    {
                        System::Diagnostics::Debug::WriteLine("Ошибка создания устройства: " + ex->Message);
                        continue;
                    }
                }
                else
                {
                    System::Diagnostics::Debug::WriteLine("Строка имеет неверный формат: " + line);
                }
            }
        }
        catch (Exception^ ex)
        {
            System::Diagnostics::Debug::WriteLine("Ошибка загрузки устройств: " + ex->Message);
            throw gcnew Exception("Не удалось загрузить устройства: " + ex->Message);
        }

        return devices;
    }

    static void SaveDevices(List<DeviceData^>^ devices)
    {
        try
        {
            List<String^>^ lines = gcnew List<String^>();

            for each (DeviceData ^ device in devices)
            {
                // Сохраняем ВСЕ 10 полей
                String^ line = String::Format("{0},{1},{2},{3},{4:F2},{5},{6},{7},{8},{9}",
                    device->Id,
                    EscapeComma(device->Manufacturer),
                    EscapeComma(device->Model),
                    EscapeComma(device->Type),
                    device->Price,
                    EscapeComma(device->AdditionalInfo),
                    EscapeComma(device->IMEI),
                    EscapeComma(device->SerialNumber),
                    EscapeComma(device->Status),
                    EscapeComma(device->Owner));

                lines->Add(line);
            }

            File::WriteAllLines(devicesFile, lines->ToArray(), Encoding::UTF8);

            System::Diagnostics::Debug::WriteLine(
                String::Format("Сохранено устройств: {0} в файл: {1}",
                    devices->Count, devicesFile));
        }
        catch (Exception^ ex)
        {
            System::Diagnostics::Debug::WriteLine("Ошибка сохранения устройств: " + ex->Message);
            throw gcnew Exception("Не удалось сохранить устройства: " + ex->Message);
        }
    }

private:
    static String^ EscapeComma(String^ text)
    {
        if (String::IsNullOrEmpty(text))
            return "";

        // Заменяем запятые на специальный символ или удаляем
        return text->Replace(",", ";");
    }

    static String^ UnescapeComma(String^ text)
    {
        if (String::IsNullOrEmpty(text))
            return "";

        // Восстанавливаем запятые
        return text->Replace(";", ",");
    }

public:
    static bool CheckUser(String^ username, String^ password, bool% isAdmin)
    {
        if (!File::Exists(usersFile))
            return false;

        try
        {
            array<String^>^ lines = File::ReadAllLines(usersFile, Encoding::UTF8);

            for each (String ^ line in lines)
            {
                if (String::IsNullOrEmpty(line))
                    continue;

                array<String^>^ parts = line->Split(',');

                if (parts->Length >= 2)
                {
                    String^ storedUsername = parts[0];
                    String^ storedPassword = parts[1];
                    bool admin = false;

                    if (parts->Length >= 3 && !String::IsNullOrEmpty(parts[2]))
                    {
                        admin = parts[2]->ToUpper() == "ADMIN";
                    }

                    if (storedUsername == username && storedPassword == password)
                    {
                        isAdmin = admin;
                        return true;
                    }
                }
            }
        }
        catch (Exception^ ex)
        {
            System::Diagnostics::Debug::WriteLine("Ошибка чтения пользователей: " + ex->Message);
        }

        return false;
    }

    static void CreateDefaultUsers()
    {
        if (!File::Exists(usersFile))
        {
            try
            {
                List<String^>^ lines = gcnew List<String^>();
                lines->Add("admin,admin123,ADMIN");
                lines->Add("user,user123,");

                File::WriteAllLines(usersFile, lines->ToArray(), Encoding::UTF8);
            }
            catch (Exception^ ex)
            {
                System::Diagnostics::Debug::WriteLine("Ошибка создания файла пользователей: " + ex->Message);
                throw;
            }
        }
    }

    // Дополнительный метод для отладки
    static String^ GetDevicesFileContent()
    {
        if (!File::Exists(devicesFile))
            return "Файл не существует";

        try
        {
            return File::ReadAllText(devicesFile, Encoding::UTF8);
        }
        catch (Exception^ ex)
        {
            return "Ошибка чтения файла: " + ex->Message;
        }
    }


};