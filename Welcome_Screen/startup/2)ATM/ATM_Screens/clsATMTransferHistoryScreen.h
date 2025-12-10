/*clsATMTransferHistoryScreen Overview
================================================================================
                    clsATMTransferHistoryScreen.h
================================================================================
Overview:
---------
This screen displays ALL transaction history for the current logged-in client.
Shows deposits, withdrawals, and transfers (sent/received).

Main Features:
--------------
1. Reads from AllTransactions.txt
2. Filters transactions involving CurrentClient
3. Shows: Date, Time, Type, Amount, From/To, Balance After
4. Color-coded by operation type

Usage Example:
--------------
clsATMTransferHistoryScreen::ShowTransactionHistoryScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsTransactionLogger.h"

using namespace std;

class clsATMTransferHistoryScreen : protected clsScreen
{

private:
    static void _PrintRecordLine(clsTransactionLogger::stTransactionRecord Record)
    {
        // Color based on operation type
        if (Record.OperationType == "DEPOSIT")
            _SetColor(10); // Green
        else if (Record.OperationType == "WITHDRAW")
            _SetColor(12); // Red
        else if (Record.OperationType == "TRANSFER_OUT")
            _SetColor(14); // Yellow
        else if (Record.OperationType == "TRANSFER_IN")
            _SetColor(11); // Cyan

        cout << setw(8) << left << "" << "| " << setw(12) << left << Record.Date;
        cout << "| " << setw(12) << left << Record.Time;
        cout << "| " << setw(14) << left << Record.OperationType;
        cout << "| " << setw(10) << left << Record.Amount;
        cout << "| " << setw(12) << left << Record.FromAccount;
        cout << "| " << setw(12) << left << Record.ToAccount;
        cout << "| " << setw(10) << left << Record.BalanceAfter;
        cout << "|";

        _SetColor(7); // Reset
    }

public:
    static void ShowTransactionHistoryScreen()
    {
        vector<clsTransactionLogger::stTransactionRecord> vTransactions = 
            clsTransactionLogger::GetAccountTransactions(CurrentClient.GetAccountNumber());

        string Title = "\tTransaction History";
        string SubTitle = "    Account: " + CurrentClient.GetAccountNumber() + 
                         " | (" + to_string(vTransactions.size()) + ") Transaction(s).";

        _DrawScreenHeader(Title, SubTitle);

        // Legend
        cout << "\n";
        _SetColor(10);
        cout << ". DEPOSIT         Client deposited money\n";
        _SetColor(12);
        cout << ". WITHDRAW        Client withdrew money\n";
        _SetColor(14);
        cout << ". TRANSFER_OUT    Client sent a transfer\n";
        _SetColor(11);
        cout << ". TRANSFER_IN     Client received a transfer\n";
        _SetColor(7);
        cout << ". ADMIN_DEPOSIT:  Admin deposited to client\n";
        cout << ". ADMIN_WITHDRAW: Admin withdrew from client\n";
        cout << ". ADM_TRANS_OUT:  Admin transfer (sender record)\n";
        cout << ". ADM_TRANS_IN:   Admin transfer (receiver record)\n";
        //- DEPOSIT:        Client deposited money
        //- WITHDRAW:       Client withdrew money
        //- TRANSFER_OUT:   Client sent a transfer
        //- TRANSFER_IN:    Client received a transfer
        //- ADMIN_DEPOSIT:  Admin deposited to client
        //- ADMIN_WITHDRAW: Admin withdrew from client
        //- ADM_TRANS_OUT:  Admin transfer (sender record)
        //- ADM_TRANS_IN:   Admin transfer (receiver record)
        cout << setw(8) << left << "" << "\n\t" << string(107, '_') << "\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "Date";
        cout << "| " << left << setw(12) << "Time";
        cout << "| " << left << setw(14) << "Type";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(12) << "From";
        cout << "| " << left << setw(12) << "To";
        cout << "| " << left << setw(10) << "Balance";
        cout << "|\n\t" << string(107, '_') << "\n\n";

        if (vTransactions.size() == 0)
        {
            _SetColor(14);
            cout << "\t\t\t\tNo Transactions Available!\n";
            _SetColor(7);
        }
        else
        {
            for (const auto &Record : vTransactions)
            {
                _PrintRecordLine(Record);
                cout << endl;
            }
        }

        cout << "\t" << string(107, '_') << endl;


    }
};