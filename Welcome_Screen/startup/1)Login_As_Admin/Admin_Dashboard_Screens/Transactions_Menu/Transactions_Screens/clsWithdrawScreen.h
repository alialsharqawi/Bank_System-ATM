/*clsWithdrawScreen Overview
================================================================================
                        clsWithdrawScreen.h
================================================================================
Overview:
----------
This file defines the clsWithdrawScreen class, which handles withdrawing money
from a client's bank account via the console interface.

Main Features:
--------------
1. Prompts the user to Enter a client account number.
2. Validates if the account exists and allows cancellation (input "0").
3. Displays the client's current details before the withdrawal.
4. Prompts the user to Enter the withdrawal amount.
5. Asks for confirmation before performing the withdrawal.
6. Updates the client's balance if sufficient funds exist.
7. Displays success, insufficient funds, or cancellation messages.

Key Functions:
--------------
- ShowWithdrawScreen(): Public function that manages the withdrawal workflow,
  including account validation, input, confirmation, and balance update.

Notes:
------
- Inherits protectedly from clsScreen to use screen drawing utilities.
- Uses clsBankClient for account retrieval and balance manipulation.
- Uses clsInputValidate for input validation and _SetColor for console message colors.

Usage Example:
--------------
clsWithdrawScreen::ShowWithdrawScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include "../../../../../../utils/clsInputValidate.h"
#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../base_screen/Global.h"
#include "../../../../../../core/clsBankClient.h"
#include "../../../../../../core/clsAdmin.h"


class clsWithdrawScreen : protected clsScreen
{
private:
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "Please Enter Account Number ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }
    static double _ReadWithdrawAmount()
    {
        double Amount = 0;
        cout << "\nEnter the amount you want to Withdraw: ";
        Amount = clsInputValidate::ReadPositiveDouble();

        while (Amount <= 0)
        {
            _SetColor(12);
            cout << "\n[X] Invalid amount! Amount must be greater than 0.\n";
            _SetColor(7);
            cout << "\nEnter the amount you want to deposit: ";
            Amount = clsInputValidate::ReadPositiveDouble();
        }

        return Amount;
    }
public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();
        if (AccountNumber == "0")
        {
            _SetColor(14); // Yellow warning
            cout << "\n⚠ Operation Cancelled.\n\a";

            _SetColor(7);
            return;
        }

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
            if (AccountNumber == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        Client1.PrintShortClientCard();

        
        while(true){
            double Amount = 0;
            
            Amount = _ReadWithdrawAmount();

            cout << "\nAre you sure you want to perform this transaction (Y/N)? ";
            char Answer = clsInputValidate ::ReadYesOrNo();

            if (Answer == 'Y' || Answer == 'y')
            {
                if (Client1.Withdraw(Amount))
                {
                    clsTransactionLogger::LogAdminWithdraw(CurrentAdmin,Client1,Amount);
                    _SetColor(10);
                    cout << "\nAmount Withdrew Successfully.\n";
                    _SetColor(7);
                    cout << "\nNew Balance Is: " << Client1.GetAccountBalance();
                    break;
                }
                else
                {
                   
                    cout << "\nAmout to withdraw is: " << Amount;
                    cout << "\nYour Balance is: " << Client1.GetAccountBalance();
                    _SetColor(12); // red
                    cout << "\n\nCannot withdraw, Insuffecient Balance!\n\n";
                    _SetColor(14);
                    cout << "\nPress any key to Enter Valid amount.";
                    _SetColor(7);
                    system("pause>0");
                    cout << endl;
                }
            }
            else
            {
                _SetColor(12); // red
                cout << "\nOperation was cancelled.\n";
                _SetColor(7);
                break;
            }
        }

    }
};
