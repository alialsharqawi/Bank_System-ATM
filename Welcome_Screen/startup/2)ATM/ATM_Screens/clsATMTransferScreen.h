/*clsATMTransferScreen Overview
================================================================================
                        clsATMTransferScreen.h
================================================================================
Overview:
----------
This file defines the clsATMTransferScreen class, which handles money transfers
from the logged-in client's account to another account through the ATM interface.

Main Features:
--------------
1. Automatically uses CurrentClient as the source account (no need to enter it).
2. Prompts for destination account number with validation.
3. Prevents transferring to the same account.
4. Displays source account information (destination balance hidden for privacy).
5. Validates transfer amount against available balance.
6. Shows transaction summary before confirmation.
7. Logs transaction to file for auditing.
8. Clean UI with minimal colors and simple ASCII borders.

Key Functions:
--------------
- ShowTransferScreen(): Public function that manages the transfer workflow.
- _ReadDestinationAccount(): Reads and validates destination account number.
- _ReadTransferAmount(): Reads and validates the transfer amount.
- _PrintSourceAccountCard(): Displays source account information.
- _PrintDestinationInfo(): Shows only name and account number (privacy protected).
- _PrintTransactionSummary(): Shows transfer details before confirmation.

UI Design:
----------
- Simple borders using only - and |
- Minimal color usage (only for success/error messages)
- Destination balance hidden for privacy
- Clean and straightforward layout

Privacy Notes:
--------------
- Destination account balance is NOT displayed
- Only shows destination account number and name for verification
- Protects other users' financial information

Usage Example:
--------------
clsATMTransferScreen::ShowTransferScreen();
================================================================================
*/
#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../utils/clsInputValidate.h"
#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsBankClient.h"
#include "../../../../core/clsAdmin.h"
#include "../../../../core/clsTransactionLogger.h"
using namespace std;

class clsATMTransferScreen : protected clsScreen
{

private:
    static void _PrintStepHeader(string StepNumber, string StepTitle)
    {
        _SetColor(11);
        cout << "\n--------------------------------------------\n";
        cout << "  STEP " << StepNumber << ": " << StepTitle << "\n";
        cout << "--------------------------------------------\n";
        _SetColor(7);
    }

    static void _PrintSourceAccountCard()
    {
        cout << "\n--------------------------------------------\n";
        cout << "|  Your Account (Source)                   |\n";
        cout << "--------------------------------------------\n";
        cout << "| Account Number : " << CurrentClient.GetAccountNumber() << "\n";
        cout << "| Account Holder : " << CurrentClient.FullName() << "\n";
        cout << "| Current Balance: " << CurrentClient.GetAccountBalance() << " $\n";
        cout << "--------------------------------------------\n";
    }

    static void _PrintDestinationInfo(clsBankClient& ToClient)
    {
        cout << "\n--------------------------------------------\n";
        cout << "|  Destination Account                     |\n";
        cout << "--------------------------------------------\n";
        cout << "| Account Number : " << ToClient.GetAccountNumber() << "\n";
        cout << "| Account Holder : " << ToClient.FullName() << "\n";
        cout << "--------------------------------------------\n";
    }

    // ============================================
    // 0 TO CANCEL Added Here
    // ============================================
    static string _ReadDestinationAccount()
    {
        cout << "\nEnter Destination Account Number ";
        _SetColor(12);
        cout <<"(0 to Cancel)";
        _SetColor(7);
        cout <<": ";
        string AccountNumber = clsInputValidate::ReadString();

        if (AccountNumber == "0")
        {
            return "0"; // cancel
        }

        return AccountNumber;
    }

    // ============================================
    // 0 TO CANCEL Added Here
    // ============================================
    static double _ReadTransferAmount()
    {
        cout << "\nEnter Amount to Transfer ";
        _SetColor(12);
        cout <<"(0 to Cancel)";
        _SetColor(7);
        cout <<": ";
        double Amount = clsInputValidate::ReadDblNumber();

        if (Amount == 0)
        {
            return 0; // cancel
        }

        while (Amount < 0)
        {
            cout << "\nInvalid amount! Must be greater than 0.\n";
            cout << "\nEnter Amount to Transfer  ";
            _SetColor(12);
            cout <<"(0 to Cancel)";
            _SetColor(7);
            cout <<": ";
            Amount = clsInputValidate::ReadDblNumber();

            if (Amount == 0)
                return 0;
        }

        while (Amount > CurrentClient.GetAccountBalance())
        {
            cout <<"\a";
            _SetColor(12);
            cout << "\nInsufficient balance! Available: "
                 << CurrentClient.GetAccountBalance() << " $\n";
            _SetColor(7);
            cout << "\nEnter Amount to Transfer  ";
            _SetColor(12);
            cout <<"(0 to Cancel)";
            _SetColor(7);
            cout <<": ";
            Amount = clsInputValidate::ReadDblNumber();

            if (Amount == 0)
                return 0;
        }

        return Amount;
    }

    static void _PrintTransactionSummary(clsBankClient& ToClient, double Amount)
    {
        _SetColor(14);
        cout << "\n============================================\n";
        cout << "         TRANSACTION SUMMARY\n";
        cout << "============================================\n";

        cout << "\n  Transfer Details:\n";
        cout << "  ------------------------------------------\n";
        
        cout << "  FROM: " << CurrentClient.FullName() << "\n";
        cout << "        Account: " << CurrentClient.GetAccountNumber() << "\n";
        cout << "        Current Balance: " << CurrentClient.GetAccountBalance() << " $\n";

        cout << "\n  TO:   " << ToClient.FullName() << "\n";
        cout << "        Account: " << ToClient.GetAccountNumber() << "\n";

        cout << "\n  ------------------------------------------\n";
        cout << "  Transfer Amount:  " << Amount << " $\n";
        cout << "  Your New Balance: " << (CurrentClient.GetAccountBalance() - Amount) << " $\n";
        cout << "  ------------------------------------------\n";
        _SetColor(7);
    }

    static void _PrintCancelled()
    {
        cout <<"\a";
        _SetColor(12);
        cout << "\n============================================\n";
        cout << "             OPERATION CANCELLED\n";
        cout << "============================================\n";
        _SetColor(7);
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t   Transfer Money");

        // Step 1: Show Source Account
        _PrintStepHeader("1", "SOURCE ACCOUNT");
        _PrintSourceAccountCard();

        // Step 2: Get Destination Account
        _PrintStepHeader("2", "DESTINATION ACCOUNT");
        string ToAccountNumber = _ReadDestinationAccount();

        // Cancel from Step 2
        if (ToAccountNumber == "0")
        {
            _PrintCancelled();
            return;
        }

        while (!clsBankClient::IsClientExist(ToAccountNumber))
        {

            cout << "\nAccount [" << ToAccountNumber << "] does not exist!\n";
            ToAccountNumber = _ReadDestinationAccount();

            if (ToAccountNumber == "0")
            {
                _PrintCancelled();
                return;
            }
        }

        while (ToAccountNumber == CurrentClient.GetAccountNumber())
        {
            cout << "\nCannot transfer to your own account!\n";
            ToAccountNumber = _ReadDestinationAccount();

            if (ToAccountNumber == "0")
            {
                _PrintCancelled();
                return;
            }

            while (!clsBankClient::IsClientExist(ToAccountNumber))
            {
                cout << "\nAccount [" << ToAccountNumber << "] does not exist!\n";
                ToAccountNumber = _ReadDestinationAccount();

                if (ToAccountNumber == "0")
                {
                    _PrintCancelled();
                    return;
                }
            }
        }

        clsBankClient ToClient = clsBankClient::Find(ToAccountNumber);
        _SetColor(10);
        cout << "\nAccount found!\n";
        _SetColor(7);

        _PrintDestinationInfo(ToClient);

        // Step 3: Amount
        _PrintStepHeader("3", "TRANSFER AMOUNT");
        double Amount = _ReadTransferAmount();

        if (Amount == 0)
        {
            _PrintCancelled();
            return;
        }
        _SetColor(10);
        cout << "\nAmount validated!\n";
        _SetColor(7);

        // Step 4: Confirm
        _PrintStepHeader("4", "CONFIRMATION");
        _PrintTransactionSummary(ToClient, Amount);

        cout << "\nAre you sure you want to proceed? (Y/N): ";
        char Answer = clsInputValidate::ReadYesOrNo();

        if (Answer == 'Y' || Answer == 'y')
        {
            if (CurrentClient.Withdraw(Amount))
            {
                ToClient.Deposit(Amount);
                clsTransactionLogger::LogTransfer(CurrentClient, ToClient, Amount);
                
                _SetColor(10);
                cout << "\n============================================\n";
                cout << "         TRANSFER SUCCESSFUL!\n";
                cout << "============================================\n";
                _SetColor(15);

                cout << "\n  Transaction Completed:\n";
                cout << "  ------------------------------------------\n";
                cout << "  Amount Transferred: " << Amount << " $\n";
                cout << "  Your New Balance:   " << CurrentClient.GetAccountBalance() << " $\n";
                cout << "  ------------------------------------------\n";
                _SetColor(7);
                clsAdmin::AddTransactionToFile(
                    CurrentClient.GetAccountNumber(),
                    Amount,
                    CurrentClient.GetAccountNumber(),
                    CurrentClient.GetAccountBalance(),
                    ToClient.GetAccountNumber(),
                    ToClient.GetAccountBalance()
                );
            }
            else
            {
                _SetColor(12);
                cout <<"\a";
                cout << "\n============================================\n";
                cout << "         TRANSFER FAILED!\n";
                cout << "         Insufficient Balance\n";
                cout << "============================================\n";
                _SetColor(7);
            }
        }
        else
        {
            _PrintCancelled();
        }
    }
};
