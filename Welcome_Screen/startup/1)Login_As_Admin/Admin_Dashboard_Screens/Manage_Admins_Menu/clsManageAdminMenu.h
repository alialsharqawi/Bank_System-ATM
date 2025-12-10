/*Overview clsManageAdminsScreen
================================================================================
                        clsManageAdminsScreen.h
================================================================================
Overview:
---------
This file defines the Manage Admins Menu Screen — a controller screen responsible
for navigating all Admin-management operations in the system.
It displays a menu, reads the user's choice, and directs the workflow to the
correct sub-screen (List, Add, Find, Update, Delete, Login History).

It does NOT modify data directly; it only calls other screens that contain the
real logic.

================================================================================
Class Responsibilities:
-----------------------

1. Display the "Manage Admins" menu.
2. Read and validate user input (1 to 7).
3. Redirect the user to the appropriate screen:
      - List Admins
      - Add New Admin
      - Find Admin
      - Update Admin
      - Delete Admin
      - Login Register History
4. Offer a "Go Back" mechanism that returns to the menu after each operation.
5. Keep UI consistency using clsScreen (headers, colors, formatting).

================================================================================
Menu Options:
-------------

    1 → List Admins
    2 → Add New Admin
    3 → Find Admin
    4 → Update Admin
    5 → Delete Admin
    6 → Login Register History
    7 → Return to Main Menu

The options are represented internally using the enum:

    enum enManageAdminsMenuOptions { eListAdmins, eAddNewAdmin, ... }

================================================================================
Input Handling:
---------------

The method:

    _ReadManageAdminsMenuOption()

uses clsInputValidate to ensure the user Enters a number between 1 and 7.
Invalid input never crashes the system.

================================================================================
Navigation Logic:
-----------------

The method:

    _PerformManageAdminsMenuOption()

contains a switch() statement that:
    - Clears the screen
    - Calls the correct sub-screen
    - Returns to the menu afterward

Each helper like `_ShowListAdminsScreen()` simply calls the corresponding class:

    clsListAdminsScreen::ShowAdminsList();
    clsAddNewAdminScreen::ShowAddNewAdminScreen();
    clsFindAdminScreen::ShowFindAdminScreen();
    clsUpdateAdminScreen::ShowUpdateAdminScreen();
    clsDeleteAdminScreen::ShowDeleteAdminScreen();
    clsLoginRegisterScreen::ShowLoginRegisterScreen();

This preserves clean separation between menu logic and actual features.

================================================================================
Main Public Function:
---------------------

    ShowManageAdminsMenu()

This is the entry point of the screen.
It:

1. Clears the console,
2. Draws the header,
3. Prints menu options,
4. Reads user choice,
5. Calls `_PerformManageAdminsMenuOption()`.

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

    clsManageAdminsScreen::ShowManageAdminsMenu();

================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../utils/clsInputValidate.h"
#include "../../../../base_screen/clsScreen.h"

#include "Manage_Admins_Screens/clsListAdminsScreen.h"
#include "Manage_Admins_Screens/clsAddNewAdminScreen.h"
#include "Manage_Admins_Screens/clsFindAdminScreen.h"
#include "Manage_Admins_Screens/clsUpdateAdminScreen.h"
#include "Manage_Admins_Screens/clsDeleteAdminScreen.h"
#include "Manage_Admins_Screens/clsCurrentAdminSessionScreen.h"
#include "Manage_Admins_Screens/clsAdminsSessionLogScreen.h"
using namespace std;

class clsManageAdminsScreen : protected clsScreen
{
private:
    enum enManageAdminsMenuOptions
    {
        eListAdmins = 1,
        eAddNewAdmin = 2,
        eFindAdmin = 3,
        eUpdateAdmin = 4,
        eDeleteAdmin = 5,
        eMySessionsHistory = 6,
        eAdminsSessions = 7,
        eMainMenu
    };

    static short _ReadManageAdminsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 8, "Enter Number between 1 to 8? ");
        return Choice;
    }

    static void _GoBackToManageAdminsMenu()
    {
        cout << "\n\nPress any key to go back to Manage Admins Menu...";
        system("pause>0");
        ShowManageAdminsMenu();
    }

    static void _ShowListAdminsScreen()
    {
        clsListAdminsScreen::ShowAdminsList();
    }

    static void _ShowAddNewAdminScreen()
    {
        clsAddNewAdminScreen::ShowAddNewAdminScreen();
    }

    static void _ShowFindAdminScreen()
    {
        clsFindAdminScreen::ShowFindAdminScreen();
    }

    static void _ShowUpdateAdminScreen()
    {
        clsUpdateAdminScreen::ShowUpdateAdminScreen();
    }

    static void _ShowDeleteAdminScreen()
    {
        clsDeleteAdminScreen::ShowDeleteAdminScreen();
    }
    static void _ShowAdminSessionsHistory()
    {
        clsAdminsSessionLogScreen::ShowAdminsSessionLogScreen();
    }
    static void _ShowMYSessionsHistory()
    {
        clsCurrentAdminSessionScreen::ShowCurrentAdminSessionScreen();
    }

    static void _PerformManageAdminsMenuOption(enManageAdminsMenuOptions ManageAdminsMenuOption)
    {
        switch (ManageAdminsMenuOption)
        {
        case enManageAdminsMenuOptions::eListAdmins:
            system("cls");
            _ShowListAdminsScreen();
            _GoBackToManageAdminsMenu();
            break;

        case enManageAdminsMenuOptions::eAddNewAdmin:
            system("cls");
            _ShowAddNewAdminScreen();
            _GoBackToManageAdminsMenu();
            break;

        case enManageAdminsMenuOptions::eFindAdmin:
            system("cls");
            _ShowFindAdminScreen();
            _GoBackToManageAdminsMenu();
            break;

        case enManageAdminsMenuOptions::eUpdateAdmin:
            system("cls");
            _ShowUpdateAdminScreen();
            _GoBackToManageAdminsMenu();
            break;

        case enManageAdminsMenuOptions::eDeleteAdmin:
            system("cls");
            _ShowDeleteAdminScreen();
            _GoBackToManageAdminsMenu();
            break;
        case enManageAdminsMenuOptions::eMySessionsHistory:
            system("cls");
            _ShowMYSessionsHistory();
            _GoBackToManageAdminsMenu();
            break;
        case enManageAdminsMenuOptions::eAdminsSessions:
            system("cls");
            _ShowAdminSessionsHistory();
            _GoBackToManageAdminsMenu();
            break;
        case enManageAdminsMenuOptions::eMainMenu:
            // do nothing, main screen will handle it :-)
            break;
        }
    }

public:
    static void ShowManageAdminsMenu()
    {
        system("cls");
        _DrawScreenHeader("\tManage Admins Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Admins Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Admins.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Admin.\n";
        cout << setw(37) << left << "" << "\t[3] Find Admin.\n";
        cout << setw(37) << left << "" << "\t[4] Update Admin.\n";
        cout << setw(37) << left << "" << "\t[5] Delete Admin.\n";
        cout << setw(37) << left << "" << "\t[6] My Sessions History.\n";
        cout << setw(37) << left << "" << "\t[7] Admins Sessions History.\n";
        cout << setw(37) << left << "" << "\t[8] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformManageAdminsMenuOption((enManageAdminsMenuOptions)_ReadManageAdminsMenuOption());
    }
};
