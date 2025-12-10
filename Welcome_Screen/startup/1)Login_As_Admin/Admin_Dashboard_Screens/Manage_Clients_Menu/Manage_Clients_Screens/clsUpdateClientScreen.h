/*clsUpdateClientScreen Overview
================================================================================
                    clsUpdateClientScreen.h
================================================================================
Overview:
----------
This file defines the clsUpdateClientScreen class, which is responsible for
updating an existing client's information in the banking system via a console interface.

Main Features:
--------------
1. Prompts the user to Enter an account number.
2. Validates the account existence and handles cancellations (input "0").
3. Allows updating individual fields:
   - First Name
   - Last Name
   - Email
   - Phone
   - Pin Code
   - Account Balance
   or all fields at once.
4. Confirms update before saving changes.
5. Saves the updated client and shows success/failure messages.

Key Functions:
--------------
- _ReadAccountNumber():
   Private helper function to read the account number from the user.

- _ReadupdatedClientInfo(clsBankClient &Client):
   Private function to update selected fields of a client interactively.

- UpdateClient():
   Public function that orchestrates the entire client update process,
   including validation, confirmation, updating fields, and saving changes.

Notes:
------
- The class inherits protectedly from clsScreen to use screen helper functions.
- Relies on clsBankClient for retrieving and saving client records.
- Uses clsInputValidate for input validation and _SetColor for colored console messages.

Usage Example:
--------------
clsUpdateClientScreen::UpdateClient();
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


class clsUpdateClientScreen : protected clsScreen

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
    static void _ReadupdatedClientInfo(clsBankClient &Client)
    {
        enum enChoice
        {
            eSaveAndExit = 0,
            eFirstName = 1,
            eLastName = 2,
            eEmail = 3,
            ePhone = 4,
            ePinCode = 5,
            eAccountBalance = 6,
            eAll = 7
        };
        enChoice Choice;
        do
        {
            _SetColor(14);
            cout << "\n===== Update Client Information =====\n";
            _SetColor(7);
            cout << "\nSelect field to update:\n\n";
            cout << "   [1] First Name\n";
            cout << "   [2] Last Name\n";
            cout << "   [3] Email\n";
            cout << "   [4] Phone\n";
            cout << "   [5] Pin Code\n";
            cout << "   [6] Account Balance\n";
            cout << "   [7] All (Update All Fields)\n";
            cout << "   [0] Save and Exit\n\n";
            cout << "Enter Your choice: ";

            Choice = static_cast<enChoice>(clsInputValidate::ReadIntNumberBetween(0, 7, "Please Enter a valid option (0-7): "));

            switch (Choice)
            {
            case eFirstName:
                cout << "\nEnter New First Name: ";
                Client.SetFirstName(clsInputValidate::ReadString());
                break;

            case eLastName:
                cout << "\nEnter New Last Name: ";
                Client.SetLastName(clsInputValidate::ReadString());
                break;

            case eEmail:
                cout << "\nEnter New Email: ";
                Client.SetEmail(clsInputValidate::ReadEmail());
                break;

            case ePhone:
                cout << "\nEnter New Phone: ";
                Client.SetPhone(clsInputValidate::ReadPhone());
                break;

            case ePinCode:
                cout << "\nEnter New Pin Code: ";
                Client.SetPinCode(clsInputValidate::ReadString());
                break;

            case eAccountBalance:
                cout << "\nEnter New Account Balance: ";
                Client.SetAccountBalance(clsInputValidate::ReadPositiveDouble());
                break;

            case eAll:
                _SetColor(10);
                cout << "\n\t\tUpdating All Fields...\n";
                _SetColor(7);
                _ReadClientInfo(Client); 
                break;

            case eSaveAndExit:
                cout << "\nSaving changes and exiting...\n";
                break;

            default:
                _SetColor(12);
                cout << "\nInvalid choice, Please try again.\n";
                _SetColor(7);
            }

            if (Choice != eSaveAndExit)
            {
                _SetColor(10);
                cout << "\nField(s) updated successfully!";
                cout << "\n------------------------------------\n";
                _SetColor(14);
                cout << "Keep Update or Enter (0) To Save and Exit.\n";
                _SetColor(7);
            }

        } while (Choice != eSaveAndExit);
    }

public:
    static void UpdateClient()
    {
        _DrawScreenHeader("\tUpdate Client Screen");
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
        // Return Client info
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _SetColor(10); // green
        cout << "\nClient found successfully\n";
        _SetColor(7); // Defualt

        cout << "--------------------------------------\n";
        Client1.Print();

        // Check befor Update
        cout << "\nAre you sure you want to update this client?(y/n): ";
        char Answer = clsInputValidate::ReadYesOrNo();

        if (tolower(Answer) != 'y')
        {
            _SetColor(12); // Red
            cout << "\nUpdate cancelled. Returning to main menu...\n";
            _SetColor(7);
            return;
        }

        // Updating customer data (optional or complete)✅
        _ReadupdatedClientInfo(Client1);

        // Save changes to the file ✅
        clsBankClient::enSaveResults SaveResult = Client1.Save();

        cout << "\n======================================\n";

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            _SetColor(10); // green
            cout << "Account Updated Successfully!\n";
            _SetColor(7); // green
            cout << "--------------------------------------\n";
            Client1.Print();
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            _SetColor(12); // Red
            cout << "Error: Account was not saved because it's empty.\n";
            _SetColor(7);
            break;
        }

        cout << "\n======================================\n";
    }
};
