/*clsTransactionsScreen Overview
================================================================================
                        clsTransactionsScreen.h
================================================================================
Overview:
----------
This file defines the clsTransactionsScreen class, which manages all financial
transactions within the banking system through a console interface.

Main Features:
--------------
1. Displays a transactions menu with options:
   - Deposit Money
   - Withdraw Money
   - Transfer Money
   - View Transfer History
   - View Total Balances
   - Return to Main Menu
2. Validates user input for menu selection.
3. Calls the appropriate screen based on user choice.
4. Provides a mechanism to return to the transactions menu after completing an action.

Key Functions:
--------------
- _ReadTransactionsMenuOption(): Reads and validates the user's menu choice.
- _ShowDepositScreen(), _ShowWithdrawScreen(), _ShowTransferScreen(),
  _ShowTransferHistoryScreen(), _ShowTotalBalancesScreen(): Private functions
  that call the respective screens for each transaction.
- _GoBackToTransactionsMenu(): Returns the user to the transactions menu.
- _PerformTransactionsMenuOption(enTransactionsMenuOptions option): Executes
  the selected menu option.
- ShowTransactionsMenu(): Public function that displays the transactions menu
  and initiates the menu workflow.

Notes:
------
- The class inherits protectedly from clsScreen to use screen drawing utilities.
- Integrates with deposit, withdrawal, transfer, transfer history, and balance screens.
- Uses clsInputValidate for input validation and _SetColor for colored console output.

Usage Example:
--------------
clsTransactionsScreen::ShowTransactionsMenu();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../utils/clsInputValidate.h"
#include "../../../../base_screen/clsScreen.h"

#include "Transactions_Screens/clsDepositScreen.h"
#include "Transactions_Screens/clsWithdrawScreen.h"
#include "Transactions_Screens/clsTransferScreen.h"
#include "Transactions_Screens/clsTransferHistoryScreen.h"
#include "../Manage_Clients_Menu/Manage_Clients_Screens/clsTotalBalancesScreen.h"


using namespace std;

class clsTransactionsScreen : protected clsScreen
{

private:
    enum enTransactionsMenuOptions
    {
        eDeposit = 1,
        eWithdraw = 2,
        eTransferMoney = 3,
        eTransferHistory = 4,
        eTotalBalance = 5,
        eMainMenu = 6
    };

    static short _ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferHistoryScreen()
    {
        clsAdminAllTransactionsScreen::ShowAllTransactionsScreen();
    }
    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
    {
        switch (TransactionsMenuOption)
        {
        case enTransactionsMenuOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;
        }

        case enTransactionsMenuOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;
        }

        case enTransactionsMenuOptions::eTransferMoney:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eTransferHistory:
        {
            system("cls");
            _ShowTransferHistoryScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        }

        case enTransactionsMenuOptions::eMainMenu:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void ShowTransactionsMenu()
    {
        system("cls");
        _DrawScreenHeader("\t Transactions Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit Money.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw Money.\n";
        cout << setw(37) << left << "" << "\t[3] Transfer Money.\n";
        cout << setw(37) << left << "" << "\t[4] View Transfer History.\n";
        cout << setw(37) << left << "" << "\t[5] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenuOption((enTransactionsMenuOptions)_ReadTransactionsMenuOption());
    }
};
