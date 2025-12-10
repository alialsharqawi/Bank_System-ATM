/*clsCurrency Overview
================================================================================
                            clsCurrency.h
================================================================================
Overview:
----------
This file defines the clsCurrency class, which represents currency information
and handles CRUD operations (Create, Read, Update, Delete) for currencies stored
in a text file "Currencies.txt".

Main Features:
--------------
1. Holds currency data: country, currency code, currency name, and exchange rate.
2. Supports adding new currency, updating existing currency, deleting currency,
   and finding currency by code or country.
3. Reads/writes currency data from/to "Currencies.txt".
4. Provides static methods to load all currencies and check existence.
5. Supports conversion between string lines in the file and clsCurrency objects.

Private Functions:
------------------
- _ConvertLinetoCurrencyObject(): Converts a line from the file into a clsCurrency object.
- _ConverCurrencyObjectToLine(): Converts a clsCurrency object into a string line for saving.
- _LoadCurrencysDataFromFile(): Reads all currencies from the file into a vector.
- _SaveCurrencyDataToFile(): Saves a vector of currencies back to the file.
- _AddDataLineToFile(): Appends a single currency line to the file.
- _Update(): Updates the current currency in the file.
- _GetEmptyCurrencyObject(): Returns an empty currency object.

Public Functions:
-----------------
- clsCurrency constructor: Initializes a currency object with mode, country, code, name, rate.
- GetAddNewCurrencyObject(): Factory method for creating a new currency object in AddMode.
- GetAllUSDRates(): Returns all currencies loaded from the file.
- Getters: GetCountry(), GetCurrencyCode(), GetCurrencyName(), GetRate().
- print() : print currency card
- UpdateRate(): Updates the rate and saves changes to file.
- Delete(): Marks the currency for deletion and updates the file.
- Save(): Saves a new currency to the file.
- FindByCode(), FindByCountry(): Static functions to find currencies.
- IsEmpty(): Checks if a currency object is empty.
- IsCurrencyExist_code(), IsCountryExist_country(): Check existence by code or country.

Usage Example:
--------------
clsCurrency NewCurrency = clsCurrency::GetAddNewCurrencyObject("USA", "USD", "Dollar", 1.0f);
NewCurrency.Save();

clsCurrency FoundCurrency = clsCurrency::FindByCode("USD");
if (!FoundCurrency.IsEmpty()) {
    FoundCurrency.UpdateRate(1.1f);
}

Notes:
------
- _Mode indicates the state of the object (Add, Update, Empty).
- Uses clsString utility class to manipulate strings (like splitting lines).
- Currencies are stored in a simple text file with a separator " || ".
================================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../utils/clsString.h"  // utils/clsString.h

class clsCurrency
{

private:
    enum enMode
    {
        AddMode = 0,
        EmptyMode = 1,
        UpdateMode = 2
    };
    enMode _Mode;
    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;
    bool _markedForDelete = false;

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = " || ")
    {
        vector<string> vCurrencyData;
        vCurrencyData = clsString::Split(Line, Seperator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
                           stod(vCurrencyData[3]));
    }

    static string _ConverCurrencyObjectToLine(const clsCurrency &Currency, string Seperator = " || ")
    {
        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.GetCountry() + Seperator;
        stCurrencyRecord += Currency.GetCurrencyCode() + Seperator;
        stCurrencyRecord += Currency.GetCurrencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.GetRate());

        return stCurrencyRecord;
    }

    static vector<clsCurrency> _LoadCurrencysDataFromFile()
    {
        vector<clsCurrency> vCurrencys;

        fstream MyFile;
        MyFile.open("../data/Currencies.txt", ios::in); // read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                vCurrencys.push_back(Currency);
            }
            MyFile.close();
        }
        return vCurrencys;
    }

    static void _SaveCurrencyDataToFile(const vector<clsCurrency> &vCurrencys)
    {
        fstream MyFile;
        MyFile.open("../data/Currencies.txt", ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (const clsCurrency &C : vCurrencys)
            {
                if (!C._markedForDelete)
                {
                    DataLine = _ConverCurrencyObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;

        MyFile.open("../data/Currencies.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsCurrency> _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (clsCurrency &C : _vCurrencys)
        {
            if (C.GetCurrencyCode() == this->GetCurrencyCode())
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyDataToFile(_vCurrencys);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }
    enum enSaveResults
    {
        svFaild = 0,
        svSucceeded = 1,
    };

    static clsCurrency GetAddNewCurrencyObject(string Country = "", string CurrencyCode = "", string CurrencyName = "", float Rate = 0.0f)
    {
        return clsCurrency(enMode::AddMode, Country, CurrencyCode, CurrencyName, Rate);
    }

    static vector<clsCurrency> GetAllUSDRates()
    {
        return _LoadCurrencysDataFromFile();
    }
    //---------------------------------------------
    // getters
    //---------------------------------------------
    string GetCountry() const
    {
        return _Country;
    }

    string GetCurrencyCode() const
    {
        return _CurrencyCode;
    }

    string GetCurrencyName() const
    {
        return _CurrencyName;
    }

    float GetRate() const
    {
        return _Rate;
    }
    //---------------------------------------------
    // Print currency info
    //---------------------------------------------
    void Print()
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << GetCountry();
        cout << "\nCode       : " << GetCurrencyCode();
        cout << "\nName       : " << GetCurrencyName();
        cout << "\nRate(1$) = : " << GetRate();
        cout << "\n_____________________________\n";
    }
    //---------------------------------------------
    // Update Rate
    //---------------------------------------------
    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }
    //---------------------------------------------
    // Delete Currency
    //---------------------------------------------
    clsCurrency Delete()
    {
        _markedForDelete = true;
        _Update();

        return _GetEmptyCurrencyObject();
    }
    //---------------------------------------------
    // Add Currency
    //---------------------------------------------
    void _AddNew()
    {
        _AddDataLineToFile(_ConverCurrencyObjectToLine(*this));
    }

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::AddMode:
            _AddNew();
            // We need to set the mode to update after add new
            _Mode = enMode::UpdateMode;
            return enSaveResults::svSucceeded;
            break;

        default:
            return enSaveResults::svFaild;
            break;
        }
    }
    //---------------------------------------------
    // Static Find Functions
    //---------------------------------------------
    static clsCurrency FindByCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open("../data/Currencies.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.GetCurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("../data/Currencies.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.GetCountry()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }
    //---------------------------------------------
    // Check if Currency Object is empty
    //---------------------------------------------
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    //---------------------------------------------
    // Static Check Functions
    //---------------------------------------------
    static bool IsCurrencyExist_code(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());
    }

    static bool IsCountryExist_country(string Country)
    {
        clsCurrency C1 = clsCurrency::FindByCountry(Country);
        return (!C1.IsEmpty());
    }
};
