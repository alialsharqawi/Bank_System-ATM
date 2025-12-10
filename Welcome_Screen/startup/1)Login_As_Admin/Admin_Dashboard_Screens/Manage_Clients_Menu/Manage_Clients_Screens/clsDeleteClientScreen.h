/*clsDeleteClientScreen Overview
================================================================================
                        clsDeleteClientScreen.h
================================================================================
Overview:
----------
This file defines the clsDeleteClientScreen class, which handles deleting
a client from the banking system via a console interface.

Main Features:
--------------
1. Prompts the user to Enter an account number to delete.
2. Validates if the account exists and handles cancellations (input "0").
3. Displays the client's details before deletion for confirmation.
4. Asks the user to confirm deletion (y/n).
5. Deletes the client and shows success or error messages.

Key Functions:
--------------
- _ReadAccountNumber(): Private helper to read the account number from the user.
- ShowDeleteClientScreen(): Public function that manages the deletion workflow, including validation, confirmation, and feedback.

Notes:
------
- The class inherits protectedly from clsScreen to use screen drawing utilities.
- Relies on clsBankClient for checking existence, retrieving, and deleting client records.
- Uses clsInputValidate for input validation and _SetColor for colored console messages.

Usage Example:
--------------
clsDeleteClientScreen::ShowDeleteClientScreen();
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


class clsDeleteClientScreen : protected clsScreen
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
    static void ShowDeleteClientScreen()
    {
        _DrawScreenHeader("\tDelete Client Screen");
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
            cout << "\nAccount Number [ " << AccountNumber << " ] Not Found , Enter another one.\n";
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

        Client1.Print();

        cout << "\nAre you sure you want to delete this client y/n? ";
        char Answer = clsInputValidate::ReadYesOrNo();

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client1.Delete())
            {
                _SetColor(10); // green
                cout << "\nClient Deleted Successfully :-)\n";
                _SetColor(7); // defualt
                Client1.Print();
            }
            else
            {
                _SetColor(12);
                cout << "\nError Client Was not Deleted\n";
                _SetColor(7);
            }
        }
    }
};
