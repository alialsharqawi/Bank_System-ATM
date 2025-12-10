/*Overview clsManageClientsScreen
================================================================================
                        clsManageClientsScreen.h
================================================================================
Overview:
---------
This file defines the Manage Clients Menu Screen — a controller screen responsible
for navigating all Client-management operations in the system.
It displays a menu, reads the user's choice, and directs the workflow to the
correct sub-screen (List, Add, Find, Update, Delete, Login History).

It does NOT modify data directly; it only calls other screens that contain the
real logic.

================================================================================
Class Responsibilities:
-----------------------

1. Display the "Manage Clients" menu.
2. Read and validate user input (1 to 7).
3. Redirect the user to the appropriate screen:
      - List Clients
      - Add New Client
      - Find Client
      - Update Client
      - Delete Client
      - Client Login Register History
4. Offer a "Go Back" mechanism that returns to the menu after each operation.
5. Keep UI consistency using clsScreen (headers, colors, formatting).

================================================================================
Menu Options:
-------------

    1 → List Clients
    2 → Add New Client
    3 → Find Client
    4 → Update Client
    5 → Delete Admin
    6 → Client Login Register History
    7 → Return to Main Menu

The options are represented internally using the enum:

    enum enManageClientsMenuOptions { eListClients, eAddNewClient, ... }

================================================================================
Input Handling:
---------------

The method:

    _ReadManageClientsMenuOption()

uses clsInputValidate to ensure the user Enters a number between 1 and 7.
Invalid input never crashes the system.

================================================================================
Navigation Logic:
-----------------

The method:

    _PerformManageClientsMenuOption()

contains a switch() statement that:
    - Clears the screen
    - Calls the correct sub-screen
    - Returns to the menu afterward

Each helper like `_ShowListClientsScreen()` simply calls the corresponding class:

    clsListClientsScreen::ShowClientsList();
    clsAddNewClientScreen::ShowAddNewClientScreen();
    clsFindClientScreen::ShowFindClientScreen();
    clsUpdateClientScreen::ShowUpdateClientScreen();
    clsDeleteClientScreen::ShowDeleteAdminScreen();
    clsClientsSessionLogScreen::ShowClientsSessionLogScreen();

This preserves clean separation between menu logic and actual features.

================================================================================
Main Public Function:
---------------------

    ShowManageClientsMenu()

This is the entry point of the screen.
It:

1. Clears the console,
2. Draws the header,
3. Prints menu options,
4. Reads user choice,
5. Calls `_PerformManageClientsMenuOption()`.

================================================================================
Design Notes:
-------------

- This class is UI-only; no business logic or file handling.
- The screen re-displays itself after every completed operation.
- Uses consistent formatting with setw() for alignment.
- Protected inheritance from clsScreen → allows reuse of UI tools
  without exposing them publicly.

================================================================================
Usage Example (from Main Menu):
--------------------------------

    clsManageClientsScreen::ShowManageClientsMenu();

================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../utils/clsInputValidate.h"
#include "../../../../base_screen/clsScreen.h"

#include "Manage_Clients_Screens/clsClientsListScreen.h"
#include "Manage_Clients_Screens/clsAddNewClientScreen.h"
#include "Manage_Clients_Screens/clsFindClientScreen.h"
#include "Manage_Clients_Screens/clsUpdateClientScreen.h"
#include "Manage_Clients_Screens/clsDeleteClientScreen.h"
#include "Manage_Clients_Screens/clsClientsSessionLogScreen.h"
#include "Manage_Clients_Screens/clsTotalBalancesScreen.h"

using namespace std;

class clsManageClientsScreen : protected clsScreen
{
private:
    enum enManageClientsMenuOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eFindClient = 3,
        eUpdateClient = 4,
        eDeleteClient = 5,
        eClientsSessions = 6,
        eMainMenu
    };

    static short _ReadManageClientsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }

    static void _GoBackToManageClientsMenu()
    {
        cout << "\n\nPress any key to go back to Manage Clients Menu...";
        system("pause>0");
        ShowManageClientsMenu();
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
    
    // main menu functions
    static void _ShowAllClientsScreen()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pListClients))
        {
            return; // this will exit the function and it will not continue
        }
        clsClientsListScreen::ShowClientsList();
    }

    static void _AddNewClientScreen()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pAddNewClient))
        {
            return; // this will exit the function and it will not continue
        }
        clsAddNewClientScreen::AddNewClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pFindClient))
        {
            return; // this will exit the function and it will not continue
        }
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pUpdateClients))
        {
            return; // this will exit the function and it will not continue
        }

        clsUpdateClientScreen::UpdateClient();
    }
    static void _ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pDeleteClient))
        {
            return; // this will exit the function and it will not continue
        }
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }
    static void _ShowTotalBalances()
    {
        if (!CheckAccessRights(clsAdmin::enPermissions::pTotalBalances))
        {
            return; // this will exit the function and it will not continue
        }
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _ShowClientSessionsHistory(){
        clsClientsSessionLogScreen::ShowClientsSessionLogScreen();
    }

    static void _PerformManageClientsMenuOption(enManageClientsMenuOptions ManageClientsMenuOption)
    {
        switch (ManageClientsMenuOption)
        {
        case enManageClientsMenuOptions::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToManageClientsMenu();
            break;

        case enManageClientsMenuOptions::eAddNewClient:
            system("cls");
            _AddNewClientScreen();
            _GoBackToManageClientsMenu();
            break;

        case enManageClientsMenuOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToManageClientsMenu();
            break;

        case enManageClientsMenuOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToManageClientsMenu();
            break;

        case enManageClientsMenuOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToManageClientsMenu();
            break;
        case enManageClientsMenuOptions::eClientsSessions:
            system("cls");
            _ShowClientSessionsHistory();
            _GoBackToManageClientsMenu();
            break;
        case enManageClientsMenuOptions::eMainMenu:
            // do nothing, main screen will handle it :-)
            break;
        }
    }

public:
    static void ShowManageClientsMenu()
    {
        system("cls");
        _DrawScreenHeader("\tManage Clients Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Clients Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Clients.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Find Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client.\n";
        cout << setw(37) << left << "" << "\t[5] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[6] Clients Sessions History.\n";
        cout << setw(37) << left << "" << "\t[7] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformManageClientsMenuOption((enManageClientsMenuOptions)_ReadManageClientsMenuOption());
    }
};
