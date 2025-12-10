/*clsATMQuickWithdrawScreen Overview
================================================================================
                    clsATMQuickWithdrawScreen.h
================================================================================
Overview:
----------
This file defines the clsATMQuickWithdrawScreen class, which provides quick
withdrawal options with predefined amounts for fast ATM transactions.

Main Features:
--------------
1. Displays menu with 9 predefined withdrawal amounts (20, 50, 100, 200, 400,
   600, 800, 1000) plus Exit option.
2. Shows current balance before withdrawal.
3. Validates if selected amount exceeds available balance.
4. Performs quick withdrawal without additional confirmation.
5. Updates balance and displays success message.
6. Allows multiple quick withdrawals in one session.

Key Functions:
--------------
- ShowQuickWithdrawScreen(): Public function that manages the quick withdraw menu.
- _GetQuickWithdrawOption(): Reads user's menu choice.
- _PerformQuickWithdrawOption(): Executes the withdrawal based on selection.

Notes:
------
- No confirmation step for faster transactions.
- Predefined amounts for common withdrawal needs.
- Automatically checks balance before allowing withdrawal.
- Uses CurrentClient for the logged-in user.

Usage Example:
--------------
clsATMQuickWithdrawScreen::ShowQuickWithdrawScreen();
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

class clsATMQuickWithdrawScreen : protected clsScreen
{

private:
    enum enQuickWithdrawOptions
    {
        eWithdraw20 = 1,
        eWithdraw50 = 2,
        eWithdraw100 = 3,
        eWithdraw200 = 4,
        eWithdraw400 = 5,
        eWithdraw600 = 6,
        eWithdraw800 = 7,
        eWithdraw1000 = 8,
        eExit = 9
    };

    static short _GetQuickWithdrawOption()
    {
        short Choice = 0;
        cout << "\nChoose what to do [1 to 9]: ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 9);
        return Choice;
    }

    static short _GetQuickWithdrawAmount(short Option)
    {
        switch (Option)
        {
        case eWithdraw20:
            return 20;
        case eWithdraw50:
            return 50;
        case eWithdraw100:
            return 100;
        case eWithdraw200:
            return 200;
        case eWithdraw400:
            return 400;
        case eWithdraw600:
            return 600;
        case eWithdraw800:
            return 800;
        case eWithdraw1000:
            return 1000;
        default:
            return 0;
        }
    }

    static void _PrintClientCard()
    {
        cout << "\n========================================\n";
        cout << "|         Your Account Balance         |\n";
        cout << "========================================\n";
        cout << "| Current Balance: " << setw(15) << left 
             << CurrentClient.GetAccountBalance() << " $ |\n";
        cout << "========================================\n";
    }

    static void _ShowQuickWithdrawMenu()
    {
        cout << "\n========================================\n";
        cout << "|        Quick Withdraw Menu           |\n";
        cout << "========================================\n";
        cout << "| [1] Withdraw 20  $                   |\n";
        cout << "| [2] Withdraw 50  $                   |\n";
        cout << "| [3] Withdraw 100 $                   |\n";
        cout << "| [4] Withdraw 200 $                   |\n";
        cout << "| [5] Withdraw 400 $                   |\n";
        cout << "| [6] Withdraw 600 $                   |\n";
        cout << "| [7] Withdraw 800 $                   |\n";
        cout << "| [8] Withdraw 1000$                   |\n";
        cout << "| [9] Exit                             |\n";
        cout << "========================================\n";
    }

    static void _PerformQuickWithdrawOption(enQuickWithdrawOptions Option)
    {
        if (Option == enQuickWithdrawOptions::eExit)
        {
            cout <<"\a";
            return;
        }

        short Amount = _GetQuickWithdrawAmount(Option);

        // Check if amount exceeds balance
        if (Amount > CurrentClient.GetAccountBalance())
        {
            _SetColor(12); // Red
            cout <<"\a";
            cout << "\n========================================\n";
            cout << "|      Insufficient Balance!           |\n";
            cout << "========================================\n";
            cout << "| Requested Amount: " << setw(15) << left << Amount << " $ |\n";
            cout << "| Your Balance    : " << setw(15) << left 
                 << CurrentClient.GetAccountBalance() << " $ |\n";
            cout << "========================================\n";
            _SetColor(7);
            return;
        }

        // Perform withdrawal
        if (CurrentClient.Withdraw(Amount))
        {
            clsTransactionLogger::LogWithdraw(CurrentClient, Amount);
            _SetColor(10); // Green
            cout << "\n========================================\n";
            cout << "|     Withdrawal Successful!           |\n";
            cout << "========================================\n";
            cout << "| Amount Withdrawn: " << setw(15) << left << Amount << " $ |\n";
            cout << "| New Balance     : " << setw(15) << left 
                 << CurrentClient.GetAccountBalance() << " $ |\n";
            cout << "========================================\n";
            _SetColor(7);
        }
        else
        {
            _SetColor(12); // Red
            cout <<"\a";
            cout << "\n========================================\n";
            cout << "|      Withdrawal Failed!              |\n";
            cout << "========================================\n";
            _SetColor(7);
        }
    }

public:
    static void ShowQuickWithdrawScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Quick Withdraw");

        _PrintClientCard();

        _ShowQuickWithdrawMenu();

        short Choice = _GetQuickWithdrawOption();

        _PerformQuickWithdrawOption((enQuickWithdrawOptions)Choice);
    }
};