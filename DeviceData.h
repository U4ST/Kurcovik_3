#pragma once

using namespace System;
using namespace System::Collections::Generic;

public ref class DeviceData
{
private:
    int _id;
    String^ _manufacturer;
    String^ _model;
    String^ _type;
    double _price;
    String^ _additionalInfo;
    String^ _owner;
    String^ _imei;
    String^ _serialNumber;
    DateTime _purchaseDate;
    String^ _status;
    String^ _currentOwner;
    String^ _os;
    int _storageGB;
    double _cost;
    DateTime _commissioningDate;

public:
   
    property int Id
    {
        int get() { return _id; }
        void set(int value) { _id = value; }
    }

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

    property DateTime PurchaseDate
    {
        DateTime get() { return _purchaseDate; }
        void set(DateTime value) { _purchaseDate = value; }
    }

    property String^ Status
    {
        String^ get() { return _status; }
        void set(String^ value) { _status = value; }
    }

    property String^ CurrentOwner
    {
        String^ get() { return _currentOwner; }
        void set(String^ value) { _currentOwner = value; }
    }

    property String^ OS
    {
        String^ get() { return _os; }
        void set(String^ value) { _os = value; }
    }

    property int StorageGB
    {
        int get() { return _storageGB; }
        void set(int value) { _storageGB = value; }
    }

    property double Cost
    {
        double get() { return _cost; }
        void set(double value) { _cost = value; }
    }

    property DateTime CommissioningDate
    {
        DateTime get() { return _commissioningDate; }
        void set(DateTime value) { _commissioningDate = value; }
    }

    property String^ Owner  
    {
        String^ get() { return _owner; }
        void set(String^ value) { _owner = value; }
    }

    // Существующий конструктор 
    DeviceData(int id, String^ manufacturer, String^ model, String^ type,
        double price, String^ additionalInfo)
    {
        _id = id;
        _manufacturer = manufacturer;
        _model = model;
        _type = type;
        _price = price;
        _additionalInfo = additionalInfo;

        
        _imei = L"";
        _serialNumber = L"";
        _purchaseDate = DateTime::Now;
        _status = L"На складе";
        _currentOwner = L"";
        _os = L"Не указана";
        _storageGB = 0;
        _cost = price;
        _commissioningDate = DateTime::Now;
        _owner = L"";
    }

    DeviceData(int id, String^ manufacturer, String^ model, String^ type,
        double price, String^ additionalInfo,
        String^ imei, String^ serialNumber, String^ status, String^ owner)
    {
        _id = id;
        _manufacturer = manufacturer;
        _model = model;
        _type = type;
        _price = price;
        _additionalInfo = additionalInfo;
        _imei = (imei != nullptr) ? imei : L"";
        _serialNumber = (serialNumber != nullptr) ? serialNumber : L"";
        _status = (status != nullptr) ? status : L"На складе";
        _owner = (owner != nullptr) ? owner : L"";

       
        _purchaseDate = DateTime::Now;
        _currentOwner = L"";
        _os = L"Не указана";
        _storageGB = 0;
        _cost = price;
        _commissioningDate = DateTime::Now;
    }

    DeviceData()
    {
        _id = 0;
        _price = 0.0;
        _cost = 0.0;
        _storageGB = 0;
        _purchaseDate = DateTime::Now;
        _commissioningDate = DateTime::Now;
        _status = L"На складе";
        _os = L"Не указана";
        _imei = L"";
        _serialNumber = L"";
        _owner = L"";
        _manufacturer = L"";
        _model = L"";
        _type = L"";
        _additionalInfo = L"";
    }
};