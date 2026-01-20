#pragma once

using namespace System;

public ref class RepairData
{
public:
    property int Id;
    property int DeviceId;
    property String^ DeviceIMEI;
    property String^ DeviceModel;
    property String^ ProblemDescription;
    property String^ Urgency; // "Низкая", "Средняя", "Высокая"
    property String^ ContactInfo;
    property String^ Status; // "Создана", "В работе", "Выполнена", "Закрыта"
    property DateTime CreatedDate;
    property DateTime RepairDate;
    property double RepairCost;
    property String^ WorkDescription;
    property int WarrantyDays;
    property String^ TechnicianName;
    property DateTime CompletedDate;

    RepairData()
    {
        Id = 0;
        DeviceId = 0;
        RepairCost = 0.0;
        WarrantyDays = 0;
        CreatedDate = DateTime::Now;
        Status = L"Создана";
        Urgency = L"Средняя";
    }
};