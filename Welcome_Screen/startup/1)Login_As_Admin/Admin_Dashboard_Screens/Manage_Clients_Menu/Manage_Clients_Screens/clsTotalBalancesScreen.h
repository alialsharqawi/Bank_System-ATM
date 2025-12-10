/*clsTotalBalancesScreen Overview
================================================================================
                        clsTotalBalancesScreen.h
================================================================================
Overview:
----------
This file defines the clsTotalBalancesScreen class, which is responsible for
displaying all clients' account balances in a formatted table along with the
total balances in the banking system.

Main Features:
--------------
1. Displays a table with columns:
   - Account Number
   - Client Name
   - Balance
2. Prints each client's balance in a neatly aligned row.
3. Calculates and displays the total balances of all clients.
4. Converts the total balance into text for better readability.
5. Handles the case when there are no clients in the system.

Key Functions:
--------------
- _PrintClientRecordBalanceLine(clsBankClient Client):
   Private function to print a single client's balance row.

- _PrintTotalBalance(double TotalBalances):
   Private function to display the total balance in numeric and text form.

- ShowTotalBalancesScreen():
   Public function that orchestrates displaying all balances and the total,
   including header, table, client data, and total balance summary.

Notes:
------
- The class inherits protectedly from clsScreen to use screen helper functions.
- Relies on clsBankClient to fetch client list and calculate total balances.
- Uses clsUtil::NumberToText to convert numeric total balance into text.
- Uses _SetColor for colored output to enhance readability.

Usage Example:
--------------
clsTotalBalancesScreen::ShowTotalBalancesScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "../../../../../../utils/clsInputValidate.h"
#include "../../../../../../utils/clsUtil.h"
#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../../core/clsBankClient.h"


class clsTotalBalancesScreen : protected clsScreen
{

private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout << setw(8) << "" << "\t"<<"| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.GetAccountBalance()<<"|";
    }
    static void _PrintTotalBalance(double TotalBalances)
    {
        _SetColor(11); // Light Aqua
        cout << "\t\t\t\t\t   Total Balances = ";
        _SetColor(12);
        cout << TotalBalances << endl;
        _SetColor(13); // Light Purple
        cout << "\t\t\t\t\t   ( ";
        _SetColor(10); // Light Green
        cout << clsUtil::NumberToText(TotalBalances);
        _SetColor(13);
        cout << " )" << endl;
        _SetColor(7);
    }

public:
    static void ShowTotalBalancesScreen()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        
        string subtitle = "\tBalances List ";
        if (vClients.size() == 0)
            subtitle += "(0) No Clients.";
        else
            subtitle += "(" + to_string(vClients.size()) + ") Client" + (vClients.size() > 1 ? "s." : ".");
            
        _DrawScreenHeader("\t Total Balances Screen",subtitle);
        // Draw Table Header
        cout << setw(8) << "" << "\t"<< endl
             << setw(8) << "" << "\t"<< string(74, '_') << "\n\n";
        cout << setw(8) << "" << "\t"<< "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance"<< "|";
        cout << setw(8) << "" << "\t"<<endl << setw(8) << "" << "\t"<< string(74, '_') << endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
        {
            _SetColor(14);
            cout << "\t\t\t\tNo Clients Available In the System!";
            _SetColor(7);
        }

        else
        {
            for (const clsBankClient &Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        }
        cout << setw(8) << "" << "\t"<< string(74, '_') << endl;
        _PrintTotalBalance(TotalBalances);
    }
};
