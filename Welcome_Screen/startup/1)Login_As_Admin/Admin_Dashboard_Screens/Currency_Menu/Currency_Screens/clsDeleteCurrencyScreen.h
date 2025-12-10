/*clsDeleteCurrencyScreen Overview
================================================================================
                            clsDeleteCurrencyScreen.h
================================================================================
Overview:
---------
This file defines the Delete Currency Screen — a UI screen responsible for
deleting a currency from the system.

It allows the user to:
1. Search for a currency by its code or by country.
2. Validate input to ensure the currency exists.
3. Confirm deletion before removing the currency.
4. Display the deleted currency details after deletion.
5. Repeat deletion operations until the user chooses to stop.

================================================================================
Class Responsibilities:
-----------------------

1. Prompt the user to select search method: by Currency Code or by Country.
2. Validate input:
       - Ensure currency code or country exists.
       - Provide option to cancel using "0".
3. Find the currency object using clsCurrency::FindByCode() or clsCurrency::FindByCountry().
4. Print the currency details.
5. Confirm deletion with the user.
6. Delete the currency and show a success message.
7. Allow repeated deletions until the user chooses to stop.

================================================================================
Public Method:
--------------

ShowDeleteCurrencyScreen()
--------------------------
Main entry point of the screen.

Steps:
1. Draws screen header using clsScreen tools.
2. Reads and validates the search criteria (code or country).
3. Finds the currency object.
4. Displays currency information.
5. Asks the user for confirmation before deletion.
6. Deletes the currency if confirmed.
7. Asks if the user wants to delete another currency.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation ensures robust and error-free deletion.
- Provides clear feedback with color-coded messages:
      - Green for successful deletion
      - Red for errors
      - Yellow for warnings or cancellations
- Supports multiple deletions in a single session.
- Uses clsString::UpperAllString to standardize user input.

================================================================================
Usage Example:
--------------

    clsDeleteCurrencyScreen::ShowDeleteCurrencyScreen();

Typically called from:
    - Financial system main menu
    - Currency management interface
    - Administrative tools within the system

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
class clsDeleteCurrencyScreen : protected clsScreen
{
private:
public:
    static void ShowDeleteCurrencyScreen()
    {
        bool DeleteAgain = true;
        while (DeleteAgain)
        {
            system("cls");
            _DrawScreenHeader("\tDelete Currency Screen");
            cout << "Delete by [1] Currency Code or [2] Country?";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            int userChoice;
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
            bool confirmDelete = false;
            cout << "Are you sure you want to delete this currency? [1] Yes [0] No : ";
            confirmDelete = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
            if (confirmDelete)
            {
                Currencytofind = Currencytofind.Delete();
                _SetColor(10); // Green
                cout << "\nCurrency deleted successfully.\n";
                _SetColor(7); // Default color
                Currencytofind.Print();
            }
            else
            {
                _SetColor(14); // Yellow
                cout << "\n⚠ Deletion cancelled.\n";
                _SetColor(7); // Default color
            }

            // ASK FOR DELETE AGIAN?
            _SetColor(14);
            cout << "Do you want to delete another currency? [1] Yes [0] No : ";
            _SetColor(7);
            DeleteAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};