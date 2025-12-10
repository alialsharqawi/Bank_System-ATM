#pragma once
#include <iostream>
#include <iomanip>

#include "../utils/clsInputValidate.h"

#include "base_screen/clsScreen.h"
#include "startup/1)Login_As_Admin/clsAdminLoginScreen.h"
#include "startup/2)ATM/clsClientLoginScreen.h"
#include "startup/3)Creat_Admin_Account/clsCreatAdminAccout.h"
#include "startup/4)Creat_Client_Account/clsCreatClientAccount.h"


using namespace std;

class clsStartUpBankSystem : protected clsScreen
{

private:
    enum enStartUpMenuOptions
    {
        eLoginToAdminPanel = 1,
        eOpenATMInterface,
        eRegisterNewClient,
        eRegisterNewAdmin,
        eExitSystem
    };

    static short _ReadStartUpMenuOption()
    {
        cout << setw(37) << left << "" << "\t   Choose an option [1 to 5]: ";
        return clsInputValidate::ReadIntNumberBetween(1, 5, "\nPlease Enter a number between 1 and 5: ");
    }

    static void _GoBackToStartMenu()
    {
        cout << "Press any Key to Back Start Menu.";
        system("pause>0");
        ShowStartUpMenu();
    }

    /// ================================
    /// PRIVATE HANDLERS FOR EACH TASK
    /// ================================

    static void _HandleLoginToAdminPanel()
    {
        system("cls");
        clsAdminLoginScreen::ShowLoginScreen();
        _GoBackToStartMenu();
    }

    static void _HandleOpenATMInterface()
    {
        system("cls");
        
        clsClientLoginScreen::ShowLoginScreen();
        _GoBackToStartMenu();
    }

    static void _HandleRegisterNewClient()
    {
        system("cls");
        clsCreatClientAccount::CreateNewClient();
        _GoBackToStartMenu();
    }

    static void _HandleRegisterNewAdmin()
    {
        system("cls");
        clsCreatAdminAccount::CreateNewAdmin();
        _GoBackToStartMenu();
    }

    static void _PerformMenuOption(enStartUpMenuOptions Option)
    {
        switch (Option)
        {
        case eLoginToAdminPanel:
            _HandleLoginToAdminPanel();
            break;

        case eOpenATMInterface:
            _HandleOpenATMInterface();
            break;

        case eRegisterNewClient:
            _HandleRegisterNewClient();
            break;

        case eRegisterNewAdmin:
            _HandleRegisterNewAdmin();
            break;

        case eExitSystem:
            system("cls");
            _SetColor(10);
            cout << "\n"
                 << setw(37) << left << "" << "Exiting system...\n";
            _SetColor(7);
            _DrawEndScreen();
            exit(0);
            break;
        }
    }

public:

    static void ShowStartUpMenu()
    {
        system("cls");

        // Title Box
        _SetColor(14); // Gold border
        cout << "\n\n\t\t\t\t\t==================================================";

        _SetColor(10); // Green title
        cout << "\n\t\t\t\t\t\t   Smart Bank System - Welcome";

        _SetColor(14); 
        cout << "\n\t\t\t\t\t==================================================";

        // Subtitle centered
        _SetColor(11); // Cyan-ish
        cout << "\n\t\t\t\t     Fast . Secure . Effortless Transactions . AI POWERDED :)\n\n";

        _SetColor(7); // Reset

        // Menu Title
        cout << setw(37) << left << "" << "\t   -------------------------------------------\n";
        cout << setw(37) << left << "" << "\t\t\tAvailable Services\n";
        cout << setw(37) << left << "" << "\t   -------------------------------------------\n";

        cout << setw(37) << left << "" << "\t\t   [1] Login to Admin Dashboard.\n";
        cout << setw(37) << left << "" << "\t\t   [2] Open ATM Interface.\n";
        cout << setw(37) << left << "" << "\t\t   [3] Register New Client Account.\n";
        cout << setw(37) << left << "" << "\t\t   [4] Register New Admin Account.\n";
        cout << setw(37) << left << "" << "\t\t   [5] Exit.\n";

        cout << setw(37) << left << "" << "\t   -------------------------------------------\n\n";

        _PerformMenuOption((enStartUpMenuOptions)_ReadStartUpMenuOption());
    }

};
