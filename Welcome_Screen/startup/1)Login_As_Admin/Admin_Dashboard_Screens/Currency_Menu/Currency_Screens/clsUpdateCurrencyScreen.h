/*clsUpdateCurrencyScreen Overview
================================================================================
                            clsUpdateCurrencyScreen.h
================================================================================
Overview:
---------
This file defines the Update Currency Screen — a UI screen responsible for
updating the exchange rate of a currency in the system.
It allows the user to search for a currency by its code or country, view its
details, and update its exchange rate to USD.

The screen validates all input and provides feedback on success or errors.

================================================================================
Class Responsibilities:
-----------------------

1. Prompt the user to select a search method:
       - By Currency Code
       - By Country

2. Read input from the user:
       - Validates that input is not "0" to cancel
       - Converts input to uppercase for consistent matching

3. Validate entries using clsCurrency functions:
       - clsCurrency::IsCurrencyExist_code()
       - clsCurrency::IsCountryExist_country()

4. Find the currency using:
       - clsCurrency::FindByCode() or clsCurrency::FindByCountry()

5. Display the currency details using clsCurrency::Print().

6. Read the new exchange rate from the user and update the currency
   using clsCurrency::UpdateRate().

7. Allow the user to repeat updates multiple times until they choose to stop.

================================================================================
Public Method:
--------------

ShowUpdateCurrencyScreen()
-------------------------
Main entry point of the screen.

Steps:
1. Draws screen header using clsScreen tools.
2. Asks user to choose search method (Code or Country).
3. Reads and validates the input.
4. Searches for the currency.
5. Displays the currency details.
6. Prompts user for the new exchange rate and updates it.
7. Prints success message and updated currency.
8. Asks user if they want to update another currency.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation ensures robust and error-free updates.
- Provides clear feedback with color-coded messages:
      - Green for success
      - Red for errors
      - Yellow for warnings
- Uses loops to allow multiple updates until the user decides to stop.
- Uses Sleep() to ensure the user reads important messages before continuing.

================================================================================
Usage Example:
--------------

    clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();

Typically called from:
    - Admin currency management menu
    - Financial system update screens

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
class clsUpdateCurrencyScreen : protected clsScreen
{
private:
public:
    static void ShowUpdateCurrencyScreen()
    {

        bool UpdateAgain = true;
        while (UpdateAgain)
        {
            system("cls");
            _DrawScreenHeader("\tUpdate Currency Screen");
            cout << "Search by [1] Currency Code or [2] Country?";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            short userChoice;
            userChoice = clsInputValidate::ReadIntNumberBetween(0, 2, "Enter 0, 1 or 2 only\n");

            if (userChoice == 0) // cancel and go back to previous menue
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            string CurrencyCode;
            string Country;

            if (userChoice == 1)
            {
                cout << "\nEnter Currency Code to find";
                _SetColor(12);
                cout << "( WAIT TWO SEC TO GO BACK)";
                _SetColor(7);
                cout << ": ";
                CurrencyCode = clsInputValidate::ReadString();

                if (CurrencyCode == "0")
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Go back.\n";
                    _SetColor(7);
                    Sleep(2000); // to make sure user read the message for 1 second
                    continue;
                }
                CurrencyCode = clsString::UpperAllString(CurrencyCode);
                bool cont = false;
                while (!clsCurrency::IsCurrencyExist_code(CurrencyCode))
                {
                    _SetColor(12); // Red
                    cout << "\n⚠ Currency Code not found! Please Enter a valid Currency Code\n";
                    _SetColor(7); // Default color
                    cout << "\nEnter Currency Code to find";
                    _SetColor(12);
                    cout << "( WAIT TWO SEC TO GO BACK)";
                    _SetColor(7);
                    cout << ": ";
                    CurrencyCode = clsInputValidate::ReadString();

                    if (CurrencyCode == "0")
                    {
                        _SetColor(14); // Yellow warning
                        cout << "\n⚠ Go back.\n";
                        _SetColor(7);
                        cont = true;
                        break;
                    }

                    CurrencyCode = clsString::UpperAllString(CurrencyCode);
                }
                if (cont)
                {
                    Sleep(2000); // to make sure user read the message for 1 second
                    continue;
                } // go back to start of do while loop
            }
            else if (userChoice == 2)
            {
                cout << "\nEnter Country to find";
                _SetColor(12);
                cout << "( WAIT TWO SEC TO GO BACK)";
                _SetColor(7);
                cout << ": ";
                Country = clsInputValidate::ReadString();
                if (Country == "0") // cancel and go back to previous menue
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Go back.\n";
                    _SetColor(7);
                    Sleep(2000); // to make sure user read the message for 1 second
                    continue;
                }
                Country = clsString::UpperAllString(Country);
                bool cont = false;
                while (!clsCurrency::IsCountryExist_country(Country))
                {
                    _SetColor(12); // Red
                    cout << "\n⚠ Country not found! Please Enter a valid Country\n";
                    _SetColor(7); // Default color
                    cout << "\nEnter Country to find";
                    _SetColor(12);
                    cout << "( WAIT TWO SEC TO GO BACK)";
                    _SetColor(7);
                    cout << ": ";
                    Country = clsInputValidate::ReadString();
                    if (Country == "0") // cancel and go back to previous menue
                    {
                        _SetColor(14); // Yellow warning
                        cout << "\n⚠ Go back.\n";
                        _SetColor(7);
                        cont = true;
                        break;
                    }
                    Country = clsString::UpperAllString(Country);
                }
                if (cont)
                {
                    Sleep(2000); // to make sure user read the message for 1 second
                    continue;
                } // go back to start of do while loop
            }

            clsCurrency Currencytofind = (userChoice == 1) ? clsCurrency::FindByCode(CurrencyCode) : clsCurrency::FindByCountry(Country);
            Currencytofind.Print();
            cout << "\nEnter new exchange rate for " << Currencytofind.GetCurrencyName() << " : ";
            float NewRate = clsInputValidate::ReadPositiveDouble("Enter valid positive number for the rate: ");
            Currencytofind.UpdateRate(NewRate);
            _SetColor(10); // Green
            cout << "\nCurrency rate updated successfully!\n";
            _SetColor(7); // Default color
            Currencytofind.Print();
            _SetColor(14);
            cout << "Do you want to update another currency rate? [1] Yes [0] No : ";
            _SetColor(7);
            UpdateAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};