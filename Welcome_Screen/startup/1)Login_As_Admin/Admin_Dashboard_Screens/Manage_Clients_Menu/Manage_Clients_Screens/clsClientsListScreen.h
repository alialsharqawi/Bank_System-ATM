/*clsClientsListScreen Overview
================================================================================
                         clsClientsListScreen.h
================================================================================
Overview:
----------
This file defines the clsClientsListScreen class, which is responsible for
displaying the list of clients in the system in a neatly formatted console table.

Main Features:
--------------
1. Displays a table header with columns:
   - Account Number
   - Client Name
   - Phone
   - Email
   - Pin Code
   - Balance

2. Prints each client's data in a well-aligned row.

3. Handles the case when no clients exist (shows a proper message).

4. Uses column formatting (setw, left) to ensure the table looks organized.

Key Functions:
--------------
- _PrintClientRecordLine(const clsBankClient& Client):
   Private function to print a single client's data in one table row.

- ShowClientsList():
   Main public function to display the client list, including:
   - Drawing the table header
   - Printing client records
   - Handling empty client list
   - Drawing table separator lines

Notes:
------
- The class inherits protectedly from clsScreen to use screen helper functions.
- Relies on clsBankClient to fetch client data.
- Uses clsInputValidate and clsUtil for helper functionalities (e.g., color handling).

Usage Example:
--------------
clsClientsListScreen::ShowClientsList();
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

using namespace std;
class clsClientsListScreen : protected clsScreen
{

private:
    static void _PrintClientRecordLine(const clsBankClient &Client)
    {
        cout << setw(8) << "" << "\t| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.GetPhone();
        cout << "| " << setw(25) << left << Client.GetEmail();
        cout << "| " << setw(10) << left << Client.GetPinCode();
        cout << "| " << setw(12) << left << Client.GetAccountBalance() << "|";
    }

public:
    static void ShowClientsList()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Client List Screen";

        string SubTitle;
        if (vClients.size() == 0)
        {
            SubTitle = "\t    (0) No Clients.";
        }
        else
        {
            SubTitle = "\t    (" + to_string(vClients.size()) + ") Client" + (vClients.size() > 1 ? "s." : ".");
        }

        _DrawScreenHeader(Title, SubTitle);

        // Draw table header
        cout << setw(8) << "" << "\t" << string(107, '_') << "\n\n";
        cout << setw(8) << "" << "\t| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "|" << endl
             << setw(8) << "" << "\t" << string(107, '_') << "\n\n";

        if (vClients.size() == 0)
        {
            _SetColor(12);
            cout << "\t\t\t\tNo Clients Available In the System!\n";
            _SetColor(7);
        }
        else
        {
            for (const clsBankClient &Client : vClients)
            {
                _PrintClientRecordLine(Client);
                cout << endl;
            }
        }
        cout << setw(8) << "" << "\t" << string(107, '_') << "\n";
    }
};
