/*clsTransferScreen Overview
================================================================================
                        clsTransferScreen.h
================================================================================
Overview:
----------
This file defines the clsTransferScreen class, responsible for handling the
"Transfer Money" screen in the banking system. It allows transferring money
between two existing bank accounts with full validation and transaction logging.

Main Features:
--------------
1. Reads source and destination account numbers with validation.
2. Ensures both accounts exist and prevents transferring to the same account.
3. Displays short client information cards for both accounts.
4. Validates that the transfer amount does not exceed the source balance.
5. Processes the transfer (withdraw + deposit).
6. Logs the transfer transaction using clsAdmin::AddTransactionToFile().
7. Supports cancellation at any point by Entering "0".

Private Functions:
------------------
- _ReadAccountNumber():
    Prompts the user for an account number.
    Accepts "0" to cancel the transaction.

Public Functions:
-----------------
- ShowTransferScreen():
    Displays the transfer screen and handles the full transfer process:

    a) Ask for source account number.
    b) Validate existence.
    c) Show account details.

    d) Ask for destination account number.
    e) Validate existence and ensure it's different from the source.
    f) Show account details.

    g) Ask for transfer amount.
    h) Validate sufficient balance.

    i) Confirm operation.
    j) Perform withdrawal from source and deposit into destination.
    k) Show updated balances.
    l) Save transaction to file.

Safety & Validation:
--------------------
- Cancels operation gracefully on “0”.
- Prevents self-transfer.
- Ensures clients exist before proceeding.
- Blocks transfer if funds are insufficient.

Transaction Logging:
--------------------
Calls:
clsAdmin::AddTransactionToFile(CurrentAdmin.GetUsername(),
                              Amount,
                              FromAccountNumber,
                              FromClient.GetAccountBalance(),
                              ToAccountNumber,
                              ToClient.GetAccountBalance());

This ensures every transfer is stored for reports and auditing.

Notes:
------
- Uses clsInputValidate for clean input handling.
- Uses clsBankClient for account operations (Find, Withdraw, Deposit).
- Uses clsScreen for consistent UI styling & header drawing.
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include "../../../../../../utils/clsInputValidate.h"
#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../base_screen/Global.h"
#include "../../../../../../core/clsBankClient.h"
#include "../../../../../../core/clsAdmin.h"



using namespace std;
class clsTransferScreen : protected clsScreen
{
private:
    static string _ReadSourceAccount()
    {
        string AccountNumber = "";
        cout << "Please Enter Account Number to Transfer From ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }
    static string _ReadDestinationAccount()
    {
        string AccountNumber = "";
        cout << "Please Enter Account Number to Transfer To ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }
public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTransfer Money Screen");
        string FromAccountNumber = _ReadSourceAccount();
        if (FromAccountNumber == "0")
        {
            _SetColor(14); // Yellow warning
            cout << "\n⚠ Operation Cancelled.\n\a";
            _SetColor(7);
            return;
        }
        while (!clsBankClient::IsClientExist(FromAccountNumber))
        {
            cout << "\nClient with [" << FromAccountNumber << "] does not exist.\n";
            FromAccountNumber = _ReadSourceAccount();
            if (FromAccountNumber == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
        }

        clsBankClient FromClient = clsBankClient::Find(FromAccountNumber);
        FromClient.PrintShortClientCard();

        string ToAccountNumber;
        while (true)
        {
            ToAccountNumber = _ReadDestinationAccount();
            if (ToAccountNumber == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
            while (!clsBankClient::IsClientExist(ToAccountNumber))
            {
                cout << "\nClient with [" << ToAccountNumber << "] does not exist.\n";
                ToAccountNumber = _ReadDestinationAccount();
                if (ToAccountNumber == "0")
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }
            if (ToAccountNumber == FromAccountNumber)
            {
                cout << "\n⚠ You cannot transfer to the same account. Please Enter a different account number.\n";
            }
            else
            {
                break; // Exit the loop if the account numbers are different
            }
        }

        clsBankClient ToClient = clsBankClient::Find(ToAccountNumber);
        ToClient.PrintShortClientCard();
        while(true){
            double Amount = 0;
            cout << "\nPlease Enter transfer amount? ";
            Amount = clsInputValidate::ReadPositiveDouble();
            if (Amount > FromClient.GetAccountBalance())
            {
                _SetColor(12); // Red for error
                cout << "\n⚠ \aInsufficient balance in the source account.\n";
                _SetColor(14);
                cout << "\nPress any key to Enter Valid amount.";
                system("pause>0");
                _SetColor(7);
                cout << endl;
                continue;
            }
            cout << "\nAre you sure you want to perform this transaction (Y/N)? ";
            char Answer = clsInputValidate::ReadYesOrNo();
            if (Answer == 'Y' || Answer == 'y')
            {
                FromClient.Withdraw(Amount);
                ToClient.Deposit(Amount);
                clsTransactionLogger::LogAdminTransfer(CurrentAdmin,FromClient,ToClient,Amount);
                _SetColor(10); // green
                cout << "\nAmount Transferred Successfully.\n";
                _SetColor(7);
                cout << "\nNew Balance of Source Account Is: " << FromClient.GetAccountBalance();
                cout << "\nNew Balance of Destination Account Is: " << ToClient.GetAccountBalance();

                // save transaction to file
                clsAdmin::AddTransactionToFile(CurrentAdmin.GetAdminUsername(), Amount, FromAccountNumber, FromClient.GetAccountBalance(),
                                              ToAccountNumber, ToClient.GetAccountBalance());
                break;
            }
            else
            {
                _SetColor(12);
                cout << "\nOperation was cancelled.\n";
                _SetColor(7);
                break;
            }
        }
    }
};