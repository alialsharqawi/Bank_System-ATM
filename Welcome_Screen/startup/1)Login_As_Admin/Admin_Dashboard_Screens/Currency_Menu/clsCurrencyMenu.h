/*clsCurrencyScreen Overview
================================================================================
                            clsCurrencyScreen.h
================================================================================
Overview:
---------
This file defines the Currency Exchange Menu Screen — a central UI screen
responsible for managing all currency-related operations in the system.

It allows the user to:
1. List all currencies.
2. Add a new currency.
3. Find a currency by code or country.
4. Update the exchange rate of a currency.
5. Convert an amount between two currencies.
6. Delete a currency.
7. Navigate back to the main menu.

================================================================================
Class Responsibilities:
-----------------------

1. Display the Currency Exchange Menu with all options.
2. Read and validate user choice between 1 to 7.
3. Call the appropriate screen for each option:
       - List Currencies → clsListCurrencysScreen
       - Add New Currency → clsAddNewCurrencyScreen
       - Find Currency → clsFindCurrencyScreen
       - Update Currency Rate → clsUpdateCurrencyScreen
       - Currency Converter → clsCurrencyConverterScreen
       - Delete Currency → clsDeleteCurrencyScreen
       - Main Menu → exit to main system menu
4. Provide navigation back to the Currency Exchange Menu after performing an action.
5. Maintain a loop to allow multiple operations until the user chooses to return to the main menu.

================================================================================
Private Methods:
----------------

_ReadCurrencyMenueOption()
---------------------------------
Prompts the user to Enter a number between 1 and 7 and validates the input.

_GoBackToCurrencyMenue()
--------------------------------
Pauses and redirects the user back to the currency exchange menu.

_ShowListCurrencyScreen()
------------------------
Calls clsListCurrencysScreen::ShowCurrencysList().

_ShowAddNewCurrencyScreen()
---------------------------
Calls clsAddNewCurrencyScreen::ShowAddNewCurrencyScreen().

_ShowFindCurrencyScreen()
-------------------------
Calls clsFindCurrencyScreen::ShowFindCurrencyScreen().

_ShowUpdateCurrencyScreen()
---------------------------
Calls clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen().

_ShowCurrencyConverterScreen()
------------------------------
Calls clsCurrencyConverterScreen::ShowCurrencyConverterScreen().

_ShowDeleteCurrencyScreen()
---------------------------
Calls clsDeleteCurrencyScreen::ShowDeleteCurrencyScreen().

_PreformCurrencyMenueOption()
-------------------------------------
Executes the appropriate function based on the user's menu choice.

================================================================================
Public Method:
--------------

ShowCurrencyMenue()
---------------------------
Main entry point of the screen.

Steps:
1. Draws screen header using clsScreen tools.
2. Displays the currency exchange menu options.
3. Reads and validates user menu selection.
4. Performs the selected operation by calling the appropriate screen.
5. Returns to the currency exchange menu after completing an operation.
6. Allows repeated interactions until the user chooses to return to the main menu.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation ensures the user Enters only numbers between 1 and 7.
- Supports navigation to multiple currency-related operations from a single menu.
- Provides modular structure by delegating functionality to specific screens.
- Uses enums to manage menu options for readability and maintainability.
- Maintains a clean and user-friendly console interface.

================================================================================
Usage Example:
--------------

    clsCurrencyScreen::ShowCurrencyMenue();

Typically called from:
    - Main system menu
    - Administrative financial tools
    - Currency management interface

================================================================================
End of Documentation
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../utils/clsInputValidate.h"
#include "../../../../../core/clsCurrency.h"
#include "../../../../base_screen/clsScreen.h"

#include "Currency_Screens/clsListCurrencysScreen.h"
#include "Currency_Screens/clsAddNewCurrencyScreen.h"
#include "Currency_Screens/clsFindCurrencyScreen.h"
#include "Currency_Screens/clsUpdateCurrencyScreen.h"
#include "Currency_Screens/clsCurrencyConverterScreen.h"
#include "Currency_Screens/clsDeleteCurrencyScreen.h"

using namespace std;
class clsCurrencyMenu : protected clsScreen
{
private:
    enum enCurrencyMenueOptions
    {
        eListCurrencys = 1,
        eAddNewCurrency = 2,
        eFindCurrency = 3,
        eUpdateCurrency = 4,
        eCurrencyConverter = 5,
        eDeleteCurrency = 6,
        eMainMenue = 7
    };

    static short _ReadCurrencyMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }

    static void _GoBackToCurrencyMenue()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menue...";
        system("pause>0");
        ShowCurrencyMenue();
    }

    static void _ShowListCurrencyScreen()
    {
        clsListCurrencysScreen::ShowCurrencysList();
    }
    static void _ShowAddNewCurrencyScreen()
    {
        clsAddNewCurrencyScreen::ShowAddNewCurrencyScreen();
    }
    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateCurrencyScreen()
    {
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }
    static void _ShowCurrencyConverterScreen()
    {
        clsCurrencyConverterScreen::ShowCurrencyConverterScreen();
    }
    static void _ShowDeleteCurrencyScreen()
    {
        clsDeleteCurrencyScreen::ShowDeleteCurrencyScreen();
    }
    static void _PreformCurrencyMenueOption(enCurrencyMenueOptions CurrencyMenueOption)
    {
        switch (CurrencyMenueOption)
        {
        case enCurrencyMenueOptions::eListCurrencys:
            system("cls");
            _ShowListCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;

        case enCurrencyMenueOptions::eAddNewCurrency:
            system("cls");
            _ShowAddNewCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;

        case enCurrencyMenueOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;

        case enCurrencyMenueOptions::eUpdateCurrency:
            system("cls");
            _ShowUpdateCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;
        case enCurrencyMenueOptions::eCurrencyConverter:
            system("cls");
            _ShowCurrencyConverterScreen();
            _GoBackToCurrencyMenue();
        case enCurrencyMenueOptions::eDeleteCurrency:
            system("cls");
            _ShowDeleteCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;
        case enCurrencyMenueOptions::eMainMenue:
            // do nothing, main screen will handle it :-)
            break;
        }
    }

public:
    static void ShowCurrencyMenue()
    {
        system("cls");
        _DrawScreenHeader("\t   Currency Exchange Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[4] Update Currency Rate.\n";
        cout << setw(37) << left << "" << "\t[5] Currency Converter.\n";
        cout << setw(37) << left << "" << "\t[6] Delete Currency.\n";
        cout << setw(37) << left << "" << "\t[7] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PreformCurrencyMenueOption((enCurrencyMenueOptions)_ReadCurrencyMenueOption());
    }
};