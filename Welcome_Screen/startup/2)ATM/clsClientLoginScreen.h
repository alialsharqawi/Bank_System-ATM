/*clsClientLoginScreen Overview
================================================================================
                        clsClientLoginScreen.h
================================================================================
Overview:
----------
This file defines the clsClientLoginScreen class, which handles Client authentication
for the banking system console application.

Main Features:
--------------
1. Prompts the Client to Enter a ClientUsername and PIN.
2. Validates credentials against existing Clients (clsClient).
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
- Integrates with clsClient and clsMainScreen for authentication and workflow control.

Usage Example:
--------------
clsClientLoginScreen::ShowLoginScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../base_screen/Global.h"
#include "../../base_screen/clsScreen.h"
#include "../../../core/clsBankClient.h"

#include"clsClientDashboard_Menu.h"

class clsClientLoginScreen : protected clsScreen
{
private:
    static void _Login()
    {
        bool LoginFaild = false;

        string ClientUsername, PIN;

        short trials = 3;
        do
        {

            if (LoginFaild)
            {
                _SetColor(12);
                cout << "\nInvlaid ClientUsername/PIN!\nyou have " << trials << " trials left.\n\n";
                cout << CurrentClient.FullName();
                _SetColor(7);
            }
            cout << "Enter Client Username ";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << "? ";
            cin >> ClientUsername;
            if(ClientUsername == "0"){
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                cin.ignore();
                return;
            }
            cout << "Enter PIN? ";
            cin >> PIN;

            CurrentClient = clsBankClient::Find(ClientUsername, PIN);
            LoginFaild = CurrentClient.IsEmpty();

            trials--;

            if (trials == 0 && LoginFaild)
            {
                
                _DrawEndScreen("    Too many failed login attempts");
                
                return;
            }

        } while (LoginFaild);
        cin.ignore();
        clsBankClient::RegisterClientSession(CurrentClient, "LOGIN");
        clsATMMainMenu::ShowATMMainMenu();
    }

public:
    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t Login Screen As Client");
        _Login();
    }
};
