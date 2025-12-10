#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../utils/clsInputValidate.h"
#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsBankClient.h"
#include "../../../../core/clsTransactionLogger.h"
using namespace std;

class clsATMDepositScreen : protected clsScreen
{

private:
    static double _ReadDepositAmount()
    {
        double Amount = 0;

        while (true)
        {
            cout << "\nEnter the amount you want to deposit ";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";

            Amount = clsInputValidate::ReadDblNumber();

            // Cancel
            if (Amount == 0)
            {
                _SetColor(14);
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return 0;
            }

            // Invalid
            if (Amount < 0)
            {
                _SetColor(12);
                cout << "\n\a[X] Invalid amount! Amount must be greater than 0.\n";
                _SetColor(7);
                continue;
            }

            return Amount;
        }
    }

    static void _PrintClientCard()
    {
        cout << "\n----------------------------------------\n";
        cout << "|         Your Account Information     |\n";
        cout << "----------------------------------------\n";
        cout << "| Account Number : " << CurrentClient.GetAccountNumber() << "\n";
        cout << "| Name           : " << CurrentClient.FullName() << "\n";
        cout << "| Current Balance: " << CurrentClient.GetAccountBalance() << "  \n";
        cout << "----------------------------------------\n";
    }

public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t    Deposit Money");

        _PrintClientCard();

        double Amount = _ReadDepositAmount();

        if (Amount == 0)
            return;

        _SetColor(14);
        cout << "\n----------------------------------------\n";
        cout << "|         Transaction Summary          |\n";
        cout << "----------------------------------------\n";
        cout << "| Deposit Amount  : " << Amount << "  \n";
        cout << "| Current Balance : " << CurrentClient.GetAccountBalance() << "  \n";
        cout << "| New Balance     : " << (CurrentClient.GetAccountBalance() + Amount) << "  \n";
        cout << "----------------------------------------\n";
        _SetColor(7);

        cout << "\nAre you sure you want to deposit " << Amount << " ? (Y/N): ";
        char Answer = clsInputValidate::ReadYesOrNo();

        if (Answer == 'Y' || Answer == 'y')
        {
            CurrentClient.Deposit(Amount);
            clsTransactionLogger::LogDeposit(CurrentClient, Amount);

            _SetColor(10);
            cout << "\n----------------------------------------\n";
            cout << "|      Deposit Successful!             |\n";
            cout << "----------------------------------------\n";
            cout << "| Amount Deposited: " << Amount << "  \n";
            cout << "| New Balance     : " << CurrentClient.GetAccountBalance() << "  \n";
            cout << "----------------------------------------\n";
            _SetColor(7);
        }
        else
        {
            _SetColor(12);
            cout <<"\a";
            cout << "\n----------------------------------------\n";
            cout << "|      Transaction Cancelled           |\n";
            cout << "----------------------------------------\n";
            _SetColor(7);
        }
    }
};