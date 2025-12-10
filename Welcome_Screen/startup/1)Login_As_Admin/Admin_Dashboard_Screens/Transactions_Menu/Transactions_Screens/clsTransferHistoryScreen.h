#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../base_screen/Global.h"
#include "../../../../../../core/clsTransactionLogger.h"

using namespace std;

class clsAdminAllTransactionsScreen : protected clsScreen
{
private:
    static void _PrintTransactionLine(const clsTransactionLogger::stTransactionRecord &Record)
    {
        // Color code based on operation type
        if (Record.OperationType == "DEPOSIT" || Record.OperationType == "ADMIN_DEPOSIT")
            _SetColor(10); // Green
        else if (Record.OperationType == "WITHDRAW" || Record.OperationType == "ADMIN_WITHDRAW")
            _SetColor(12); // Red
        else if (Record.OperationType == "TRANSFER_OUT" || Record.OperationType == "ADM_TRANS_OUT")
            _SetColor(14); // Yellow
        else if (Record.OperationType == "TRANSFER_IN" || Record.OperationType == "ADM_TRANS_IN")
            _SetColor(11); // Cyan
        else
            _SetColor(7); // Default

        cout << setw(8) << left << "" << "| " << setw(12) << left << Record.Date;
        cout << "| " << setw(12) << left << Record.Time;
        cout << "| " << setw(15) << left << Record.Username;
        cout << "| " << setw(14) << left << Record.OperationType;
        cout << "| " << setw(10) << left << Record.Amount;
        cout << "| " << setw(12) << left << Record.FromAccount;
        cout << "| " << setw(12) << left << Record.ToAccount;
        cout << "| " << setw(10) << left << Record.BalanceAfter;
        cout << "|";

        _SetColor(7); // Reset color
    }

public:
    static void ShowAllTransactionsScreen()
    {
        vector<clsTransactionLogger::stTransactionRecord> vTransactions =
            clsTransactionLogger::GetAllAdminTransactions();

        string Title = "\tAll Transactions (Admin View)";
        string SubTitle = "\tTotal: " + to_string(vTransactions.size()) + " transaction(s)";

        _DrawScreenHeader(Title, SubTitle);

        // Legend
        cout << "\n";
        _SetColor(10); cout << ". DEPOSIT / ADMIN_DEPOSIT      Green\n";
        _SetColor(12); cout << ". WITHDRAW / ADMIN_WITHDRAW    Red\n";
        _SetColor(14); cout << ". TRANSFER_OUT / ADM_TRANS_OUT Yellow\n";
        _SetColor(11); cout << ". TRANSFER_IN / ADM_TRANS_IN   Cyan\n";
        _SetColor(7);
        cout << setw(8) << left << "" << "\n\t" << string(125, '_') << "\n\n";

        // Table header
        cout << setw(8) << left << "" << "| " << left << setw(12) << "Date";
        cout << "| " << left << setw(12) << "Time";
        cout << "| " << left << setw(15) << "Username";
        cout << "| " << left << setw(14) << "Type";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(12) << "From";
        cout << "| " << left << setw(12) << "To";
        cout << "| " << left << setw(10) << "Balance";
        cout << "|\n\t" << string(125, '_') << "\n\n";

        if (vTransactions.empty())
        {
            _SetColor(14);
            cout << "\t\t\t\tNo Transactions Available!\n";
            _SetColor(7);
        }
        else
        {
            for (const auto &Record : vTransactions)
            {
                _PrintTransactionLine(Record);
                cout << endl;
            }
        }

        cout << "\t" << string(125, '_') << endl;
    }
};
