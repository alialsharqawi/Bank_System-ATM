/*clsAddNewClientScreen Overview
================================================================================
                    clsAddNewClientScreen.h
================================================================================
Overview:
----------
This file defines the clsAddNewClientScreen class, which is responsible for
adding a new client to the banking system via a console-based interface.

Main Features:
--------------
1. Reads a unique account number from the user.
2. Collects client information:
   - First Name
   - Last Name
   - Email
   - Phone
   - Pin Code
   - Account Balance
3. Validates input data using clsInputValidate.
4. Checks for duplicate account numbers and handles cancellations.
5. Saves the new client and displays appropriate messages based on save result.

Key Functions:
--------------
- _ReadAccountNumber():
   Private helper function to read the account number from the user.

- _ReadClientInfo(clsBankClient &Client):
   Private function to read all required client information interactively.

- AddNewClientsScreen():
   Public function that orchestrates the entire process of adding a new client,
   including input, validation, duplication check, saving, and success/failure messages.

Notes:
------
- The class inherits protectedly from clsScreen to utilize screen helper functions.
- Relies on clsBankClient for creating and saving new client records.
- Uses clsUtil and _SetColor to provide colored messages and better user experience.

Usage Example:
--------------
clsAddNewClientScreen::AddNewClientsScreen();
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


using namespace std;

class clsAddNewClientScreen : protected clsScreen
{

private:
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";

        while (true)
        {
            cout << "Please Set Account Number ";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            AccountNumber = clsInputValidate::ReadString();

            if (AccountNumber == "0")
                return AccountNumber;

            
            if (!AccountNumber.empty() && AccountNumber[0] == 'C')
                return AccountNumber;

            _SetColor(12);
            cout << "\nInvalid Account Number! Must start with capital 'C'. Try again.\n";
            _SetColor(7);
        }
    }


    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadEmail());

        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadPhone());

        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadPositiveDouble());
    }

public:
    static void AddNewClientScreen(string Header="\t  Add New Client Screen")
    {
        
        _DrawScreenHeader(Header);

        string AccountNumber = _ReadAccountNumber();
        if (AccountNumber == "0")
        {
            _SetColor(14); // Yellow warning
            cout << "\n⚠ Operation Cancelled.\n\a\a";
            _SetColor(7);
            return;
        }
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number [ " << AccountNumber << " ] Is Already Used, Enter another one.\n";
            AccountNumber = _ReadAccountNumber();
            if (AccountNumber == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            _SetColor(10);
            cout << "\nAccount Addeded Successfully :-)\n";
            _SetColor(7);
            NewClient.Print();
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            _SetColor(14);
            cout << "\nError account was not saved because it's Empty";
            _SetColor(7);
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            _SetColor(4);
            cout << "\nError account was not saved because account number is used!\n";
            _SetColor(7);
            break;
        }
        }
    }
};
