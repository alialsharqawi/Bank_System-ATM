/*clsATMMainMenu.h Overview
================================================================================
                            clsATMMainMenu.h
================================================================================
Overview:
----------
This file defines the clsATMMainMenu class, which manages the ATM main menu
for bank clients after successful login.

Main Features:
--------------
1. Displays the ATM menu with options:
   - Quick Withdraw
   - Normal Withdraw
   - Deposit
   - Check Balance
   - Transfer
   - Transfer History
   - Change PIN Code
   - Logout
2. All operations are restricted to the logged-in client's account only.
3. Handles user input and validation for menu selection.
4. Calls the appropriate ATM screen based on the selected option.
5. Supports returning to the ATM menu after completing an action.

Key Functions:
--------------
- _ReadATMMenuOption(): Reads and validates the user's menu choice.
- _GoBackToATMMenu(): Returns to the ATM menu after an action is completed.
- _PerformATMMenuOption(): Executes the selected menu option.
- ShowATMMainMenu(): Displays the ATM menu and initiates the workflow.

Notes:
------
- Simpler interface compared to Admin Dashboard (no permission checks needed)
- Client can only access their own account data
- More user-friendly and straightforward for regular banking operations

Usage Example:
--------------
clsATMMainMenu::ShowATMMainMenu();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../utils/clsInputValidate.h"
#include "../../base_screen/Global.h"
#include "../../base_screen/clsScreen.h"

#include "ATM_Screens/clsATMQuickWithdrawScreen.h"
#include "ATM_Screens/clsATMNormalWithdrawScreen.h"
#include "ATM_Screens/clsATMDepositScreen.h"
#include "ATM_Screens/clsATMCheckBalanceScreen.h"
#include "ATM_Screens/clsATMTransferScreen.h"
#include "ATM_Screens/clsATMTransferHistoryScreen.h"
#include "ATM_Screens/clsATMChangePINScreen.h"
#include "ATM_Screens/clsCurrentClientSessionScreen.h"
using namespace std;

class clsATMMainMenu : protected clsScreen
{

private:
    enum enATMMenuOptions
    {
        eQuickWithdraw = 1,
        eNormalWithdraw,
        eDeposit,
        eCheckBalance,
        eTransfer,
        eTransferHistory,
        eChangePIN,
        eMySessionHistory,
        eLogout
    };

    static short _ReadATMMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 9, "Enter Number between 1 to 9? ");
        return Choice;
    }

    static void _GoBackToATMMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to ATM Menu...\n";
        system("pause>0");
        ShowATMMainMenu();
    }

    // ATM Menu Functions
    static void _ShowQuickWithdrawScreen()
    {
        clsATMQuickWithdrawScreen::ShowQuickWithdrawScreen();
    }

    static void _ShowNormalWithdrawScreen()
    {
        clsATMWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowDepositScreen()
    {
        clsATMDepositScreen::ShowDepositScreen();
    }

    static void _ShowCheckBalanceScreen()
    {
        clsATMCheckBalanceScreen::ShowCheckBalanceScreen();
    }

    static void _ShowTransferScreen()
    {
        clsATMTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferHistoryScreen()
    {
        clsATMTransferHistoryScreen::ShowTransactionHistoryScreen();
    }

    static void _ShowChangePINScreen()
    {
        clsATMChangePINScreen::ShowChangePINScreen();
    }
    static void _ShowMySessionHistoryScreen()
    {
        clsCurrentClientSessionScreen::ShowCurrentClientSessionScreen();
    }

    static void _Logout()
    {
        clsBankClient::RegisterClientSession(CurrentClient, "LOGOUT");
        CurrentClient = clsBankClient::Find("", "");
        // Logs out the current client by clearing CurrentClient
    }

    static void _PerformATMMenuOption(enATMMenuOptions ATMMenuOption)
    {
        switch (ATMMenuOption)
        {
        case enATMMenuOptions::eQuickWithdraw:
            system("cls");
            _ShowQuickWithdrawScreen();
            _GoBackToATMMenu();
            break;
            
        case enATMMenuOptions::eNormalWithdraw:
            system("cls");
            _ShowNormalWithdrawScreen();
            _GoBackToATMMenu();
            break;
            
        case enATMMenuOptions::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToATMMenu();
            break;
            
        case enATMMenuOptions::eCheckBalance:
            system("cls");
            _ShowCheckBalanceScreen();
            _GoBackToATMMenu();
            break;
            
        case enATMMenuOptions::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToATMMenu();
            break;
            
        case enATMMenuOptions::eTransferHistory:
            system("cls");
            _ShowTransferHistoryScreen();
            _GoBackToATMMenu();
            break;
            
        case enATMMenuOptions::eChangePIN:
            system("cls");
            _ShowChangePINScreen();
            _GoBackToATMMenu();
            break;

        case enATMMenuOptions::eMySessionHistory:
            system("cls");
            _ShowMySessionHistoryScreen();
            _GoBackToATMMenu();
            break;

        case enATMMenuOptions::eLogout:
            system("cls");
            _Logout();
            _SetColor(10);
            cout << setw(37) << left << "" << "\n\tLogged out successfully. Thank you!\n";
            _SetColor(7);
            _DrawEndScreen();
            break;
        }
    }

public:
    static void ShowATMMainMenu()
    {
        system("cls");

        _DrawScreenHeader("\tATM Main Menu");
        
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t      ATM Services\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Quick Withdraw Money.\n";
        cout << setw(37) << left << "" << "\t[2] Normal Withdraw Money.\n";
        cout << setw(37) << left << "" << "\t[3] Deposit Money.\n";
        cout << setw(37) << left << "" << "\t[4] Check Balance.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Money.\n";
        cout << setw(37) << left << "" << "\t[6] Transfer History.\n";
        cout << setw(37) << left << "" << "\t[7] Change PIN Code.\n";
        cout << setw(37) << left << "" << "\t[8] My Session History.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformATMMenuOption((enATMMenuOptions)_ReadATMMenuOption());
    }
};