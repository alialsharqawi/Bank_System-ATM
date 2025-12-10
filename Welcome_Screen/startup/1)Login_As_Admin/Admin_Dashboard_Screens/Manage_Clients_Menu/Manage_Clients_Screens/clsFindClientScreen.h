/*clsFindClientScreen Overview
================================================================================
                        clsFindClientScreen.h
================================================================================
Overview:
----------
This file defines the clsFindClientScreen class, which is responsible for
searching and displaying a client's information based on their account number
using a console interface.

Main Features:
--------------
1. Prompts the user to Enter an account number.
2. Validates the input and handles cancellations (input "0").
3. Checks if the account exists; if not, prompts the user to re-Enter.
4. Finds the client using clsBankClient and displays the client details.
5. Allows the user to search for multiple clients in a loop until they choose to stop.

Key Functions:
--------------
- _ReadAccountNumber():
   Private helper function to read the account number from the user.

- ShowFindClientScreen():
   Public function that manages the client search process, validation,
   and displaying search results along with retry functionality.

Notes:
------
- The class inherits protectedly from clsScreen to use screen helper functions.
- Uses clsBankClient for verifying and retrieving client records.
- Uses _SetColor to provide colored feedback messages for success, warnings, and prompts.

Usage Example:
--------------
clsFindClientScreen::ShowFindClientScreen();
================================================================================
*/


#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "../../../../../../utils/clsInputValidate.h"
#include "../../../../../../utils/clsUtil.h"
#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../../core/clsBankClient.h"


class clsFindClientScreen : protected clsScreen
{

private:
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "Please Enter Account Number ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    static void ShowFindClientScreen()
    {
        bool FindAgain = true;
        while (FindAgain)
        {
            system("cls");

            _DrawScreenHeader("\t Find Client Screen");

            string AccountNumber = _ReadAccountNumber();
            if (AccountNumber == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount Number [ " << AccountNumber << " ] is Not Found , Enter another one.\n";
                AccountNumber = _ReadAccountNumber();
                if (AccountNumber == "0")
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);

            _SetColor(10); // green
            cout << "\nClient Found Successfully:-)\n";
            cout << "--------------------------------------\n";
            _SetColor(7); // Defualt

            // print client info
            Client1.Print();

            _SetColor(14); // yellow
            cout << "Do you want Find another Client again? [1] Yes [0] No: ";
            _SetColor(7);
            FindAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};