/*clsATMCheckBalanceScreen Overview
================================================================================
                    clsATMCheckBalanceScreen.h
================================================================================
Overview:
----------
This file defines the clsATMCheckBalanceScreen class, which displays the
current balance and account information for the logged-in ATM user.

Main Features:
--------------
1. Displays complete account information card.
2. Shows current balance in a clear, formatted way.
3. Simple and quick balance inquiry.
4. User-friendly interface with colored output.
5. No modifications to account - read-only operation.

Key Functions:
--------------
- ShowCheckBalanceScreen(): Public function that displays balance information.
- _PrintClientCard(): Displays detailed account information.

Notes:
------
- Uses CurrentClient (logged-in user) for instant access.
- Read-only operation - safest ATM function.
- No validation or confirmation needed.
- Uses _SetColor for attractive colored display.

Usage Example:
--------------
clsATMCheckBalanceScreen::ShowCheckBalanceScreen();
================================================================================
*/
#pragma once

#include <iostream>
#include <iomanip>

#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsBankClient.h"

using namespace std;

class clsATMCheckBalanceScreen : protected clsScreen
{

private:
    static void _PrintClientCard()
    {
        cout << "\n========================================\n";
        cout << "|         Account Information          |\n";
        cout << "========================================\n";
        cout << "| Account Number : " << CurrentClient.GetAccountNumber() << "\n";
        cout << "| Account Holder : " << CurrentClient.FullName() << "\n";
        cout << "| Phone Number   : " << CurrentClient.GetPhone() << "\n";
        cout << "| Email          : " << CurrentClient.GetEmail() << "\n";
        cout << "========================================\n";
    }

    static void _PrintBalanceInfo()
    {
        _SetColor(11); // Cyan
        cout << "\n****************************************\n";
        cout << "*                                      *\n";
        cout << "*          CURRENT BALANCE             *\n";
        cout << "*                                      *\n";
        cout << "****************************************\n";
        _SetColor(10); // Green
        cout << "*                                      *\n";
        cout << "*           " << setw(15) << left << CurrentClient.GetAccountBalance() 
             << "            *\n";
        cout << "*                                      *\n";
        _SetColor(11);
        cout << "****************************************\n";
        _SetColor(7); // Reset to white
    }

public:
    static void ShowCheckBalanceScreen()
    {
        _DrawScreenHeader("\t   Check Balance");

        _PrintClientCard();

        _PrintBalanceInfo();

    }
};