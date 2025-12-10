/*clsATMWithdrawScreen Overview
================================================================================
                        clsATMWithdrawScreen.h
================================================================================
Overview:
----------
This file defines the clsATMWithdrawScreen class, which handles withdrawing money
from the logged-in client's account through the ATM interface.

Main Features:
--------------
1. Displays the current client's account information.
2. Shows current balance before withdrawal.
3. Prompts the client to enter the withdrawal amount.
4. Validates the amount (must be positive and not exceed balance).
5. Asks for confirmation before performing the withdrawal.
6. Updates the client's balance and displays success message.
7. Prevents overdraft by checking available balance.

Key Functions:
--------------
- ShowWithdrawScreen(): Public function that manages the withdrawal workflow.
- _ReadWithdrawAmount(): Reads and validates the withdrawal amount.

Notes:
------
- Uses CurrentClient (logged-in user) instead of searching by account number.
- Checks if withdrawal amount exceeds available balance.
- Uses clsInputValidate for input validation and _SetColor for colored output.

Usage Example:
--------------
clsATMWithdrawScreen::ShowWithdrawScreen();
================================================================================
*/
#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../utils/clsInputValidate.h"
#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsBankClient.h"
#include "../../../../core/clsTransactionLogger.h"

using namespace std;

class clsATMWithdrawScreen : protected clsScreen
{

private:

    static double _ReadWithdrawAmount()
    {
        double Amount = 0;

        while (true)
        {
            cout << "\nEnter the amount you want to withdraw ";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";

            Amount = clsInputValidate::ReadDblNumber();

            // Cancel operation
            if (Amount == 0)
            {
                _SetColor(14);
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return 0;
            }

            // Negative amount
            if (Amount < 0)
            {
                _SetColor(12);
                cout << "\a\n[X] Invalid amount! Amount must be greater than 0.\n";
                _SetColor(7);
                continue;
            }

            // Insufficient balance
            if (Amount > CurrentClient.GetAccountBalance())
            {
                _SetColor(12);
                cout << "\n\a[X] Insufficient balance! Your current balance is "
                     << CurrentClient.GetAccountBalance() << " $\n";
                _SetColor(7);
                continue;
            }

            return Amount;
        }
    }

    static void _PrintClientCard()
    {
        cout << "\n----------------------------------------\n";
        cout << "|         Your Account Information     |\n";
        cout << "----------------------------------------\n";
        cout << "| Account Number : " << CurrentClient.GetAccountNumber() << "\n";
        cout << "| Name           : " << CurrentClient.FullName() << "\n";
        cout << "| Current Balance: " << CurrentClient.GetAccountBalance() << " $\n";
        cout << "----------------------------------------\n";
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Money");

        _PrintClientCard();

        double Amount = _ReadWithdrawAmount();
        if (Amount == 0)
        {
            return;
        }

        _SetColor(14);
        cout << "\n----------------------------------------\n";
        cout << "|         Transaction Summary          |\n";
        cout << "----------------------------------------\n";
        cout << "| Withdraw Amount : " << Amount << " $\n";
        cout << "| Current Balance : " << CurrentClient.GetAccountBalance() << " $\n";
        cout << "| New Balance     : " << (CurrentClient.GetAccountBalance() - Amount) << " $\n";
        cout << "----------------------------------------\n";
        _SetColor(7);

        cout << "\nAre you sure you want to withdraw " << Amount << "$? (Y/N): ";
        char Answer = clsInputValidate::ReadYesOrNo();

        if (Answer == 'Y' || Answer == 'y')
        {
            if (CurrentClient.Withdraw(Amount))
            {
                clsTransactionLogger::LogWithdraw(CurrentClient, Amount);
                _SetColor(10);
                cout << "\n----------------------------------------\n";
                cout << "|     Withdrawal Successful!           |\n";
                cout << "----------------------------------------\n";
                cout << "| Amount Withdrawn: " << Amount << " $\n";
                cout << "| New Balance     : " << CurrentClient.GetAccountBalance() << " $\n";
                cout << "----------------------------------------\n";
                _SetColor(7);
            }
            else
            {
                _SetColor(12);
                cout <<"\a";
                cout << "\n----------------------------------------\n";
                cout << "|      Withdrawal Failed!              |\n";
                cout << "|      Insufficient Balance            |\n";
                cout << "----------------------------------------\n";
                _SetColor(7);
            }
        }
        else
        {
            _SetColor(12);
            cout <<"\a";
            cout << "\n----------------------------------------\n";
            cout << "|      Transaction Cancelled           |\n";
            cout << "----------------------------------------\n";
            _SetColor(7);
        }
    }
};
