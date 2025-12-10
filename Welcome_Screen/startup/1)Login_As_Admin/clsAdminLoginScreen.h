/*clsAdminLoginScreen Overview
================================================================================
                        clsAdminLoginScreen.h
================================================================================
Overview:
----------
This file defines the clsAdminLoginScreen class, which handles Admin authentication
for the banking system console application.

Main Features:
--------------
1. Prompts the Admin to Enter a AdminUsername and password.
2. Validates credentials against existing Admins (clsAdmin).
3. Allows up to 3 login attempts and exits the program after exceeding the limit.
4. Records successful login attempts to a file.
5. Upon successful login, transfers control to the main menu (clsMainScreen).

Key Functions:
--------------
- _Login(): Private function that manages the login process, validation, retry attempts, and recording login entries.
- ShowLoginScreen(): Public function that clears the console, displays the login screen header, and initiates the login process.

Notes:
------
- The class inherits protectedly from clsScreen to use screen drawing utilities.
- Uses _SetColor to display colored feedback messages for errors.
- Integrates with clsAdmin and clsMainScreen for authentication and workflow control.

Usage Example:
--------------
clsAdminLoginScreen::ShowLoginScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../base_screen/Global.h"
#include "../../base_screen/clsScreen.h"
#include "../../../core/clsAdmin.h"

#include"clsAdminDashboard_Menu.h"

class clsAdminLoginScreen : protected clsScreen
{
private:
    static void _Login()
    {
        bool LoginFaild = false;

        string AdminUsername, Password;

        short trials = 3;
        do
        {

            if (LoginFaild)
            {
                _SetColor(12);
                cout << "\nInvlaid AdminUsername/Password!\nyou have " << trials << " trials left.\n\n";
                cout << CurrentAdmin.FullName();
                _SetColor(7);
            }
            cout << "Enter Admin Username ";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << "? ";
            cin >> AdminUsername;
            if(AdminUsername == "0"){
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                cin.ignore();
                return;
            }
            cout << "Enter Password? ";
            cin >> Password;

            CurrentAdmin = clsAdmin::Find(AdminUsername, Password);
            LoginFaild = CurrentAdmin.IsEmpty();
            trials--;

            if (trials == 0 && LoginFaild)
            {
                // cout << "\nYou have exceeded the maximum number of login attempts.\n";
                // cout << "Exiting the program...\n";
                // system("pause>0");
                // exit(0);
                
                _DrawEndScreen("    Too many failed login attempts");
                
                return;
            }

        } while (LoginFaild);
        cin.ignore();
        clsAdmin::RegisterAdminSession(CurrentAdmin, "LOGIN");
        clsAdminDashboardMenu::ShowAdminDashboard();
    }

public:
    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t Login Screen As Admin");
        _Login();
    }
};
