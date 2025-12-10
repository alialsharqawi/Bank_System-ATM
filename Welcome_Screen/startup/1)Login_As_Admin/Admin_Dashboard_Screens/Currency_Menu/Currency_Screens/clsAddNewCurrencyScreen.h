/*clsAddNewCurrencyScreen Overview
================================================================================
                            clsAddNewCurrencyScreen.h
================================================================================
Overview:
---------
This file defines the Add New Currency Screen — a UI screen responsible for
allowing the admin to add a new currency to the system.
It collects currency information from the user, validates it, and saves it using
the `clsCurrency` class.

The screen ensures no duplicate countries or currency codes are added.

================================================================================
Class Responsibilities:
-----------------------

1. Read currency details from user input:
       - Country
       - Currency Code
       - Currency Name
       - Exchange Rate to USD

2. Validate entries:
       - Prevent duplicate country names using clsCurrency::IsCountryExist_country()
       - Prevent duplicate currency codes using clsCurrency::IsCurrencyExist_code()
       - Validate numeric input for exchange rate

3. Save the new currency using:
       clsCurrency::Save()

4. Display the added currency in a formatted output.

5. Allow the user to repeat the process multiple times until they choose to exit.

================================================================================
Public Method:
--------------

ShowAddNewCurrencyScreen()
-------------------------
Main entry point of the screen.

Steps:
1. Draws screen header using clsScreen tools.
2. Reads currency information from the user.
3. Validates input for duplicates and numeric correctness.
4. Creates a new clsCurrency object.
5. Saves the currency and shows a success or failure message.
6. Prompts the user to add another currency or exit.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation ensures robustness and prevents duplicate entries.
- Provides clear feedback to the user for each step.
- Uses loops to allow multiple entries until the user decides to stop.
- All messages are color-coded for clarity (green for success, red for errors, yellow for warnings).

================================================================================
Usage Example:
--------------

    clsAddNewCurrencyScreen::ShowAddNewCurrencyScreen();

Typically called from:
    - Admin currency management menu
    - Financial system setup screens

================================================================================
End of Documentation
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../../utils/clsInputValidate.h"
#include "../../../../../../core/clsCurrency.h"
#include "../../../../../base_screen/clsScreen.h"


using namespace std;
class clsAddNewCurrencyScreen : protected clsScreen
{
private:
public:
    static void ShowAddNewCurrencyScreen()
    {

        bool AddAgain = true;
        while (AddAgain)
        {
            system("cls");
            _DrawScreenHeader("\tAdd New Currency Screen");

            //////////////////////////////////////////
            // Read Currency Info From User
            string Country, CurrencyCode, CurrencyName;
            float Rate;

            cout << "\nEnter Country";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            Country = clsInputValidate::ReadString();
            if (Country == "0") // cancel and go back to previous menue
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            while (clsCurrency::IsCountryExist_country(Country))
            {
                _SetColor(12); // Red
                cout << "\n⚠ Country already exists! Please Enter a different Country\n";
                _SetColor(7); // Default color
                cout << "\nEnter Country";
                _SetColor(12);
                cout << "(0 to cancel)";
                _SetColor(7);
                cout << ": ";
                Country = clsInputValidate::ReadString();
                if (Country == "0") // cancel and go back to previous menue
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }
            cout << "\nEnter Currency Code";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            CurrencyCode = clsInputValidate::ReadString();
            if (CurrencyCode == "0") // cancel and go back to previous menue
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            while (clsCurrency::IsCurrencyExist_code(CurrencyCode))
            {
                _SetColor(12); // Red
                cout << "\n⚠ Currency Code already exists! Please Enter a different Currency Code\n";
                _SetColor(7); // Default color
                cout << "\nEnter Currency Code";
                _SetColor(12);
                cout << "(0 to cancel)";
                _SetColor(7);
                cout << ": ";
                CurrencyCode = clsInputValidate::ReadString();
                if (CurrencyCode == "0") // cancel and go back to previous menue
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }
            cout << "\nEnter Currency Name: ";
            CurrencyName = clsInputValidate::ReadString();
            cout << "\nEnter Exchange Rate to USD: ";
            Rate = clsInputValidate::ReadPositiveDouble();
            /////////////////////////////////////////
            clsCurrency newcurrency = clsCurrency::GetAddNewCurrencyObject(Country, CurrencyCode, CurrencyName, Rate);
            //////////////////////////////////////////
            clsCurrency::enSaveResults Result;
            Result = newcurrency.Save();
            switch (Result)
            {
            case clsCurrency::enSaveResults::svSucceeded:
                _SetColor(10); // green
                cout << "Currency Added Succefulley! \n";
                _SetColor(7);
                newcurrency.Print();
                break;
            case clsCurrency::enSaveResults::svFaild:
                _SetColor(12); // Red
                cout << "Currency Added Succefulley! \n";
                _SetColor(7);
                break;
            default:
                break;
            }
            // ask for add agin
            _SetColor(14);
            cout << "Do You Want to Add Another Currency? [1] Yes [0] No : ";
            _SetColor(7);
            AddAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};