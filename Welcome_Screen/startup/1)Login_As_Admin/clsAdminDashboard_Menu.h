/*clsAdminDashboardMenu Overview
================================================================================
                            clsAdminDashboardMenu.h
================================================================================
Overview:
----------
This file defines the clsAdminDashboardMenu class, which manages the main menu of the
banking system console application. It provides access to all core functionalities
based on user permissions.

Main Features:
--------------
1. Displays the main menu with options:
   - Show Client List
   - Add New Client
   - Find Client
   - Update Client Info
   - Delete Client
   - Show All Balances
   - Transactions
   - Manage Admins
   - Currency Exchange
   - Logout
2. Checks Admin access rights before executing each menu option.
3. Handles user input and validation for menu selection.
4. Calls the appropriate screen or functionality based on the selected option.
5. Supports returning to the main menu after completing an action.
6. Handles logout and resets the current user session.

Key Functions:
--------------
- _ReadMainMenuOption(): Reads and validates the user's main menu choice.
- _GoBackToMainMenu(): Returns to the main menu after an action is completed.
- CheckAccessRights(clsAdmin::enPermissions Permission): Verifies if the current Admin has permission.
- _PerformMainMenuOption(enMainMenuOptions MainMenuOption): Executes the selected menu option.
- ShowMainMenu(): Displays the main menu and initiates the menu workflow.

Notes:
------
- The class inherits protectedly from clsScreen to use screen drawing utilities.
- Integrates with multiple screens and features like Admin management & client transactions, balances, and currency exchange.
- Uses clsInputValidate for input validation and _SetColor for colored console output.

Usage Example:
--------------
clsAdminDashboardMenu::ShowMainMenu();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../utils/clsInputValidate.h"

#include "../../base_screen/Global.h"
#include "../../base_screen/clsScreen.h"

#include "Admin_Dashboard_Screens/Manage_Clients_Menu/clsManageClientsScreen.h"
#include "Admin_Dashboard_Screens/Transactions_Menu/clsTransactionsMenu.h"
#include "Admin_Dashboard_Screens/Currency_Menu/clsCurrencyMenu.h"
#include "Admin_Dashboard_Screens/Manage_Admins_Menu/clsManageAdminMenu.h"
using namespace std;

class clsAdminDashboardMenu : protected clsScreen
{

private:
    enum enMainMenuOptions
    {
        eManageClientsMenu = 1,     // [1] Show Client List
        eManageAdminsMenu,          // [8] Transactions
        eTransactionsMenu,          // [9] Manage Admins
        eCurrencyMenu,              // [10] Currency Menu
        eLogout                     // [11] Logout
    };


    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main MenuS...";
        system("pause>0"); // wait for any press
        ShowAdminDashboard();
    }

    // Check Client Access Rights

    static bool CheckAccessRights(clsAdmin::enPermissions Permission)
    {
        if (!CurrentAdmin.CheckAccessPermission(Permission))
        {
                _SetColor(4);
                _printCentered("______________________________________");
                _printCentered("Access Denied! Contact with Super Admin.");
                _printCentered("______________________________________");
                _SetColor(7);
            return false;
        }
        return true;
    }

    static void _ShowManageClintMenu()
    {
        clsManageClientsScreen::ShowManageClientsMenu();
    }
    static void _ShowManageAdminMenu()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pManageAdmins))
        {
            return; // exit if user has no permission
        }
        clsManageAdminsScreen::ShowManageAdminsMenu();
    }
    static void _ShowTransactionsMenu()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pTranactions))
        {
            return; // this will exit the function and it will not continue
        }
        clsTransactionsScreen::ShowTransactionsMenu();
    }
    static void _CurrencyMenu()
    {
        clsCurrencyMenu::ShowCurrencyMenue();
    }
    static void _Logout()
    {
        clsAdmin::RegisterAdminSession(CurrentAdmin, "LOGOUT");
        CurrentAdmin = clsAdmin::Find("", "");
        // Logs out the current user by clearing CurrentAdmin.
        // After this, control returns to the caller function.
    }

    static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case enMainMenuOptions::eManageClientsMenu:
            system("cls");
            _ShowManageClintMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eManageAdminsMenu:
            system("cls");
            _ShowManageAdminMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eTransactionsMenu:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eCurrencyMenu:
            system("cls");
            _CurrencyMenu();
            _GoBackToMainMenu();
            break;
        case enMainMenuOptions::eLogout:
            system("cls");
            _Logout();
            _SetColor(10);
            cout << setw(37) << left << "" << "\n\tYou are logged out successfully.\n";
            _SetColor(7);
            _DrawEndScreen();
            break;
        }
    }

public:
    static void ShowAdminDashboard()
    {
        system("cls");

        _DrawScreenHeader("\tAdmin Dashboard Screen");
        
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t        Main Menus\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Manage Clients Menu.\n";
        cout << setw(37) << left << "" << "\t[2] Manage Admins Menu.\n";
        cout << setw(37) << left << "" << "\t[3] Transactions Menu.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Menu.\n";
        cout << setw(37) << left << "" << "\t[5] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
    }
};
