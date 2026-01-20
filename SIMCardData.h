#pragma once

using namespace System;

public ref class SIMCardData
{
public:
    property int Id;
    property String^ PhoneNumber;
    property String^ Operator;
    property String^ TariffPlan;
    property double MonthlyCost;
    property int DataLimitGB;
    property int MinutesLimit;
    property int SMSLimit;
    property DateTime ActivationDate;
    property DateTime ExpiryDate;
    property bool IsActive;
    property String^ DeviceIMEI;
    property String^ DeviceModel;
    property String^ Notes;
    property int DataUsedGB;
    property int MinutesUsed;
    property int SMSUsed;

    SIMCardData()
    {
        Id = 0;
        MonthlyCost = 0.0;
        DataLimitGB = 0;
        MinutesLimit = 0;
        SMSLimit = 0;
        IsActive = true;
        ActivationDate = DateTime::Now;
        ExpiryDate = DateTime::Now.AddYears(1);
        DataUsedGB = 0;
        MinutesUsed = 0;
        SMSUsed = 0;
    }
};