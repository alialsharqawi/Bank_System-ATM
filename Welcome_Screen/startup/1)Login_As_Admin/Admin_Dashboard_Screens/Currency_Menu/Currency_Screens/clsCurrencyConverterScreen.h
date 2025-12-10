/*clsCurrencyConverterScreen Overview
================================================================================
                            clsCurrencyConverterScreen.h
================================================================================
Overview:
---------
This file defines the Currency Converter Screen — a UI screen responsible for
performing currency conversion calculations between two currencies.

It allows the user to:
1. Enter the source currency code.
2. Enter the target currency code.
3. Enter the amount to convert.
4. Perform the conversion using exchange rates stored in the system.
5. Display the converted amount with formatted output.

================================================================================
Class Responsibilities:
-----------------------

1. Prompt the user to Enter the source (From) currency code.
2. Validate input:
       - Ensure currency code exists.
       - Provide option to cancel using "0".
3. Prompt the user to Enter the target (To) currency code.
4. Validate input:
       - Ensure currency code exists.
       - Provide option to cancel using "0".
5. Prompt the user to Enter the amount to convert.
6. Perform the conversion calculation:
       - Formula: Amount * (RateTo / RateFrom)
7. Display the converted amount with 4 decimal places.
8. Allow the user to repeat conversions multiple times until they choose to stop.

================================================================================
Public Method:
--------------

ShowCurrencyConverterScreen()
-----------------------------
Main entry point of the screen.

Steps:
1. Draws screen header using clsScreen tools.
2. Reads and validates source currency code.
3. Reads and validates target currency code.
4. Reads the amount to convert.
5. Finds currency objects using clsCurrency::FindByCode().
6. Performs conversion and prints the result.
7. Asks user if they want to perform another calculation.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation ensures robust and error-free conversions.
- Provides clear feedback with color-coded messages:
      - Green for conversion results
      - Red for errors
      - Yellow for warnings or cancellations
- Supports multiple conversions in a single session.
- Uses fixed precision formatting for consistent result display.

================================================================================
Usage Example:
--------------

    clsCurrencyConverterScreen::ShowCurrencyConverterScreen();

Typically called from:
    - Financial system main menu
    - Currency management interface
    - Calculator or utility tools within the system

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
class clsCurrencyConverterScreen : protected clsScreen
{
private:
public:
    static void ShowCurrencyConverterScreen()
    {
        bool CalcAgain = true;
        while (CalcAgain)
        {

            system("cls");
            _DrawScreenHeader("\tCurrency Calculation Screen");

            string CurrencyCodeFrom, CurrencyCodeTo;
            double Amount;
            cout << "\nEnter Currency Code (From)";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            CurrencyCodeFrom = clsInputValidate::ReadString();
            if (CurrencyCodeFrom == "0") // cancel and go back to previous menue
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            while (!clsCurrency::IsCurrencyExist_code(CurrencyCodeFrom))
            {
                _SetColor(12); // Red
                cout << "\n⚠ Currency Code not found! Please Enter a valid Currency Code\n";
                _SetColor(7); // Default color
                cout << "\nEnter Currency Code (From)";
                _SetColor(12);
                cout << "(0 to cancel)";
                _SetColor(7);
                cout << ": ";
                CurrencyCodeFrom = clsInputValidate::ReadString();
                if (CurrencyCodeFrom == "0") // cancel and go back to previous menue
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }
            cout << "\nEnter Currency Code (TO)";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            CurrencyCodeTo = clsInputValidate::ReadString();
            if (CurrencyCodeTo == "0") // cancel and go back to previous menue
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            while (!clsCurrency::IsCurrencyExist_code(CurrencyCodeTo))
            {
                _SetColor(12); // Red
                cout << "\n⚠ Currency Code not found! Please Enter a valid Currency Code\n";
                _SetColor(7); // Default color
                cout << "\nEnter Currency Code (TO)";
                _SetColor(12);
                cout << "(0 to cancel)";
                _SetColor(7);
                cout << ": ";
                CurrencyCodeTo = clsInputValidate::ReadString();
                if (CurrencyCodeTo == "0") // cancel and go back to previous menue
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }
            cout << "\nEnter Amount: ";
            Amount = clsInputValidate::ReadPositiveDouble();

            clsCurrency currency1 = clsCurrency::FindByCode(CurrencyCodeFrom);
            clsCurrency currency2 = clsCurrency::FindByCode(CurrencyCodeTo);

            double Aftercalc = Amount * (currency2.GetRate() / currency1.GetRate());
            cout << fixed << setprecision(4); 

            cout << Amount << " [ " << currency1.GetCurrencyCode() << " ]"
                 << " = ";
            _SetColor(10);
            cout << Aftercalc << " [ " << currency2.GetCurrencyCode() << " ]\n";
            _SetColor(14);
            cout << "Do You Want Preform another calculation? [1] Yes [0] No : ";
            _SetColor(7);
            CalcAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};