/*clsListCurrencysScreen Overview
================================================================================
                            clsListCurrencysScreen.h
================================================================================
Overview:
---------
This file defines the List Currencies Screen — a UI screen responsible for
displaying all currencies along with their country, code, name, and USD rate.

It allows the user to:
1. View all currencies stored in the system.
2. See the exchange rate of each currency relative to USD.
3. Display the currencies in a formatted, tabular style.

================================================================================
Class Responsibilities:
-----------------------

1. Fetch all currency records from the system using clsCurrency::GetAllUSDRates().
2. Display a formatted header for the currency table.
3. Print each currency record line with:
       - Country
       - Currency Code
       - Currency Name
       - Exchange Rate per USD
4. Display the total number of currencies.

================================================================================
Private Methods:
----------------

_PrintCurrencysListHeader()
---------------------------
Prints the header line for the currency table.

PrintCurrencyRecordLine(const clsCurrency& Currency)
----------------------------------------------------
Prints a single currency record in tabular format.

================================================================================
Public Method:
--------------

ShowCurrencysList()
------------------
Main entry point of the screen.

Steps:
1. Retrieves all currencies using clsCurrency::GetAllUSDRates().
2. Draws the screen header using clsScreen tools.
3. Prints the table header.
4. Iterates over all currencies and prints each one.
5. Draws the bottom border of the table.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Displays currency data in a clean and readable tabular format.
- Automatically calculates the number of currencies and displays it in the subtitle.
- Modular design with separate functions for header and row printing.

================================================================================
Usage Example:
--------------

    clsListCurrencysScreen::ShowCurrencysList();

Typically called from:
    - Currency Exchange Menu
    - Administrative financial tools
    - Reporting interfaces

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

class clsListCurrencysScreen : protected clsScreen
{
private:
    static void _PrintCurrencysListHeader()
    {
        cout << setw(8) << left << "" << "\n\t" << string(102, '_') << endl;
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)" << "|\n";
        cout << "\t" << string(102, '_') << endl;
    }

    static void PrintCurrencyRecordLine(const clsCurrency &Currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.GetCountry();
        cout << "| " << left << setw(8) << Currency.GetCurrencyCode();
        cout << "| " << left << setw(45) << Currency.GetCurrencyName();
        cout << "| " << left << setw(10) << Currency.GetRate() << "|\n";
    }

public:
    static void ShowCurrencysList()
    {
        vector<clsCurrency> vCurrencys = clsCurrency::GetAllUSDRates();

        string Title = "\t Currencies List Screen";
        string SubTitle = "\t (" + to_string(vCurrencys.size()) + ") Currency";

        _DrawScreenHeader(Title, SubTitle);

        _PrintCurrencysListHeader();
        if (vCurrencys.empty())
        {
            _SetColor(14); // yellow
            cout << "\t\t\t\tNo Currencys Available In the System!\n";
            _SetColor(7);
        }else{

            for (const clsCurrency &C : vCurrencys)
            PrintCurrencyRecordLine(C);
            
        }

        cout << "\t" << string(102, '_') << "\n\n";
    }
};
