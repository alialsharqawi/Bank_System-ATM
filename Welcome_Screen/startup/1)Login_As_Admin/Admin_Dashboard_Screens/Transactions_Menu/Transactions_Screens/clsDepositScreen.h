/*clsDepositScreen Overview
================================================================================
                        clsDepositScreen.h
================================================================================
Overview:
----------
This file defines the clsDepositScreen class, which handles depositing money
into a client's bank account via the console interface.

Main Features:
--------------
1. Prompts the user to Enter a client account number.
2. Validates if the account exists and handles cancellation (input "0").
3. Displays the client's current details before the deposit.
4. Prompts the user to Enter the deposit amount.
5. Asks for confirmation before performing the deposit.
6. Updates the client's balance and displays success or cancellation messages.

Key Functions:
--------------
- ShowDepositScreen(): Public function that manages the deposit workflow,
  including validation, input, confirmation, and balance update.

Notes:
------
- The class inherits protectedly from clsScreen to use screen drawing utilities.
- Uses clsBankClient for account retrieval and balance update.
- Uses clsInputValidate for input validation and _SetColor for colored console messages.

Usage Example:
--------------
clsDepositScreen::ShowDepositScreen();
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
#include "../../../../../../core/clsTransactionLogger.h"


class clsDepositScreen : protected clsScreen
{

private:
    static double _ReadDepositAmount()
    {
        double Amount = 0;
        cout << "\nEnter the amount you want to deposit: ";
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

public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t    Deposit Screen");

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

        double Amount = 0;
        Amount = _ReadDepositAmount();

        cout << "\nAre you sure you want to perform this transaction (Y/N)? ";
        char Answer = clsInputValidate ::ReadYesOrNo();

        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.Deposit(Amount);
            clsTransactionLogger::LogAdminDeposit(CurrentAdmin,Client1,Amount);
            _SetColor(10); // green
            cout << "\n________________________________";
            cout << "\nAmount Deposited Successfully.";
            cout << "\n________________________________\n";
            _SetColor(7);
            cout << "\nNew Balance Is: " << Client1.GetAccountBalance();
        }
        else
        {
            _SetColor(12);
            cout << "\nOperation was cancelled.\n";
            _SetColor(7);
        }
    }
};
