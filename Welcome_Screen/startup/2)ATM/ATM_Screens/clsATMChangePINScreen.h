/*clsATMChangePINScreen Overview
================================================================================
                        clsATMChangePINScreen.h
================================================================================
Overview:
----------
This file defines the clsATMChangePINScreen class, which allows the logged-in
client to change their PIN code through the ATM interface.

Main Features:
--------------
1. Displays current client account information.
2. Verifies current PIN before allowing change (security check).
3. Prompts for new PIN with confirmation.
4. Validates that new PIN matches confirmation.
5. Ensures new PIN is different from current PIN.
6. Updates PIN and saves to file.
7. Shows success message with security reminder.

Key Functions:
--------------
- ShowChangePINScreen(): Public function that manages the PIN change workflow.
- _ReadCurrentPIN(): Reads and validates the current PIN for security.
- _ReadNewPIN(): Reads the new PIN.
- _ReadConfirmPIN(): Confirms the new PIN by re-entering it.

Security Features:
------------------
- Must enter current PIN correctly (3 attempts allowed).
- New PIN must be confirmed by entering twice.
- New PIN must be different from current PIN.
- Masked input for better security (optional).

Notes:
------
- Uses CurrentClient (logged-in user).
- Critical security function - requires extra validation.
- PIN is stored using SetPinCode() method.
- Changes are saved immediately to file.

Usage Example:
--------------
clsATMChangePINScreen::ShowChangePINScreen();
================================================================================
*/
#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../utils/clsInputValidate.h"
#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsBankClient.h"

using namespace std;

class clsATMChangePINScreen : protected clsScreen
{

private:
    static void _PrintClientCard()
    {
        cout << "\n----------------------------------------\n";
        cout << "|         Your Account Information     |\n";
        cout << "----------------------------------------\n";
        cout << "| Account Number : " << CurrentClient.GetAccountNumber() << "\n";
        cout << "| Name           : " << CurrentClient.FullName() << "\n";
        cout << "----------------------------------------\n";
    }

    // =====================================================
    // 0 TO CANCEL ADDED
    // =====================================================
    static string _ReadCurrentPIN()
    {
        cout << "\nPlease Enter your Current PIN Code ";
        _SetColor(12);
        cout <<"(0 to Cancel)";
        _SetColor(7);
        cout <<": ";
        string PIN = clsInputValidate::ReadString();
        return PIN;
    }

    static string _ReadNewPIN()
    {
        cout << "\nPlease Enter your New PIN Code ";
        _SetColor(12);
        cout <<"(0 to Cancel)";
        _SetColor(7);
        cout <<": ";
        string PIN = clsInputValidate::ReadString();
        return PIN;
    }

    static string _ReadConfirmPIN()
    {
        cout << "Please Confirm your New PIN Code ";
        _SetColor(12);
        cout <<"(0 to Cancel)";
        _SetColor(7);
        cout <<": ";
        string PIN = clsInputValidate::ReadString();
        return PIN;
    }

    static void _PrintCancelled()
    {
        cout <<"\a";
        _SetColor(12);
        cout << "\n============================================\n";
        cout << "             OPERATION CANCELLED\n";
        cout << "============================================\n";
        _SetColor(7);
    }

public:
    static void ShowChangePINScreen()
    {
        _DrawScreenHeader("\t   Change PIN Code");

        _PrintClientCard();

        // Verify current PIN
        int Attempts = 3;
        bool CurrentPINVerified = false;

        while (Attempts > 0 && !CurrentPINVerified)
        {
            string CurrentPIN = _ReadCurrentPIN();

            // Cancel option
            if (CurrentPIN == "0")
            {
                _PrintCancelled();
                return;
            }

            if (CurrentPIN == CurrentClient.GetPinCode())
            {
                CurrentPINVerified = true;
            }
            else
            {
                Attempts--;
                _SetColor(12);
                cout << "\n\a[X] Incorrect PIN! ";
                if (Attempts > 0)
                {
                    cout << "You have " << Attempts << " attempt(s) remaining.\n";
                }
                _SetColor(7);
            }
        }

        if (!CurrentPINVerified)
        {
            _SetColor(12);
            cout << "\a\n========================================\n";
            cout << "|      Access Denied!                  |\n";
            cout << "|      Too many failed attempts        |\n";
            cout << "========================================\n";
            _SetColor(7);
            return;
        }

        _SetColor(10);
        cout << "\n✓ Current PIN verified successfully!\n";
        _SetColor(7);

        string NewPIN = "";
        string ConfirmPIN = "";
        bool PINsMatch = false;

        while (!PINsMatch)
        {
            cout << "\n----------------------------------------\n";
            cout << "|         Enter New PIN Code           |\n";
            cout << "----------------------------------------\n";

            NewPIN = _ReadNewPIN();

            // Cancel option
            if (NewPIN == "0")
            {
                _PrintCancelled();
                return;
            }

            if (NewPIN == CurrentClient.GetPinCode())
            {
                _SetColor(12);
                cout << "\n\a[X] New PIN cannot be the same as current PIN!\n";
                _SetColor(7);
                continue;
            }

            ConfirmPIN = _ReadConfirmPIN();

            // Cancel option
            if (ConfirmPIN == "0")
            {
                _PrintCancelled();
                return;
            }

            if (NewPIN == ConfirmPIN)
            {
                PINsMatch = true;
            }
            else
            {
                _SetColor(12);
                cout << "\n\a[X] PIN codes do not match! Please try again.\n";
                _SetColor(7);
            }
        }

        // Confirmation
        _SetColor(14);
        cout << "\n========================================\n";
        cout << "|             Confirmation              |\n";
        cout << "========================================\n";
        _SetColor(7);

        cout << "\nConfirm PIN Change (Y/N): ";
        char Answer = clsInputValidate::ReadYesOrNo();

        if (Answer == 'Y' || Answer == 'y')
        {
            CurrentClient.SetPinCode(NewPIN);
            CurrentClient.Save();

            _SetColor(10);
            cout << "\n========================================\n";
            cout << "|      PIN Changed Successfully!       |\n";
            cout << "========================================\n";
            cout << "| Your PIN code has been updated.      |\n";
            cout << "| Please remember your new PIN.        |\n";
            cout << "========================================\n";
            _SetColor(7);

            _SetColor(11);
            cout << "\n  Security Reminder:\n";
            cout << "- Keep your PIN confidential\n";
            cout << "- Never share it with anyone\n";
            cout << "- Memorize it - do not write it down\n";
            _SetColor(7);
        }
        else
        {
            _SetColor(12);
            cout << "\n\a========================================\n";
            cout << "|      PIN Change Cancelled            |\n";
            cout << "========================================\n";
            _SetColor(7);
        }
    }
};