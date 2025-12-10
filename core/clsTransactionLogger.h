/*clsTransactionLogger Overview
================================================================================
                        clsTransactionLogger.h
================================================================================
Overview:
---------
Unified transaction logging system for ALL financial operations in the bank.
Replaces separate transaction files with one comprehensive log.

Transaction Types:
------------------
- DEPOSIT:        Client deposited money
- WITHDRAW:       Client withdrew money
- TRANSFER_OUT:   Client sent a transfer
- TRANSFER_IN:    Client received a transfer
- ADMIN_DEPOSIT:  Admin deposited to client
- ADMIN_WITHDRAW: Admin withdrew from client
- ADM_TRANS_OUT:  Admin transfer (sender record)
- ADM_TRANS_IN:   Admin transfer (receiver record)

File Format:
------------
Date#//#Time#//#Username/Account#//#OperationType#//#Amount#//#FromAccount#//#ToAccount#//#BalanceAfter

Fields:
-------
1. Date: Transaction date
2. Time: Transaction time
3. Username/Account: Who performed the operation (Admin username or Client account)
4. OperationType: Type of operation (see above)
5. Amount: Transaction amount
6. FromAccount: Source account (or "-" if N/A)
7. ToAccount: Destination account (or "-" if N/A)
8. BalanceAfter: Account balance after transaction

Usage Example:
--------------
// Client deposit
clsTransactionLogger::LogDeposit(CurrentClient, 500);

// Client withdraw
clsTransactionLogger::LogWithdraw(CurrentClient, 200);

// Client transfer
clsTransactionLogger::LogTransfer(CurrentClient, ToClient, 300);

// Admin deposit/withdraw
clsTransactionLogger::LogAdminDeposit(CurrentAdmin, Client, 1000);
clsTransactionLogger::LogAdminWithdraw(CurrentAdmin, Client, 500);

// Admin transfer (records separate for sender and receiver)
clsTransactionLogger::LogAdminTransfer(CurrentAdmin, FromClient, ToClient, 500);
================================================================================
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../utils/clsDate.h"
#include "../utils/clsString.h"

using namespace std;

class clsTransactionLogger
{
public:
    enum enOperationType
    {
        DEPOSIT,
        WITHDRAW,
        TRANSFER_OUT,
        TRANSFER_IN,
        ADMIN_DEPOSIT,
        ADMIN_WITHDRAW,
        ADM_TRANS_OUT,
        ADM_TRANS_IN  
    };

    struct stTransactionRecord
    {
        string Date;
        string Time;
        string Username;
        string OperationType;
        double Amount;
        string FromAccount;
        string ToAccount;
        double BalanceAfter;
    };

private:
    static string _OperationTypeToString(enOperationType Type)
    {
        switch (Type)
        {
        case DEPOSIT: return "DEPOSIT";
        case WITHDRAW: return "WITHDRAW";
        case TRANSFER_OUT: return "TRANSFER_OUT";
        case TRANSFER_IN: return "TRANSFER_IN";
        case ADMIN_DEPOSIT: return "ADMIN_DEPOSIT";
        case ADMIN_WITHDRAW: return "ADMIN_WITHDRAW";
        case ADM_TRANS_OUT: return "ADM_TRANS_OUT";
        case ADM_TRANS_IN: return "ADM_TRANS_IN";
        default: return "UNKNOWN";
        }
    }

    static void _WriteTransactionToFile(string Username, enOperationType Type,
                                        double Amount, string FromAccount,
                                        string ToAccount, double BalanceAfter)
    {
        fstream MyFile("../data/AllTransactions.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            string Date = clsDate::DateToString(clsDate::GetSystemDate());
            string Time = clsDate::GetAccurateTime();

            MyFile << Date << "#//#"
                   << Time << "#//#"
                   << Username << "#//#"
                   << _OperationTypeToString(Type) << "#//#"
                   << Amount << "#//#"
                   << FromAccount << "#//#"
                   << ToAccount << "#//#"
                   << BalanceAfter
                   << endl;

            MyFile.close();
        }
    }

public:
    // Client Operations
    template <typename T>
    static void LogDeposit(const T &Client, double Amount)
    {
        string Account = Client.GetAccountNumber();
        _WriteTransactionToFile(Account, DEPOSIT, Amount, "-", Account,
                                Client.GetAccountBalance());
    }

    template <typename T>
    static void LogWithdraw(const T &Client, double Amount)
    {
        string Account = Client.GetAccountNumber();
        _WriteTransactionToFile(Account, WITHDRAW, Amount, Account, "-",
                                Client.GetAccountBalance());
    }

    template <typename T1, typename T2>
    static void LogTransfer(const T1 &FromClient, const T2 &ToClient, double Amount)
    {
        // Log for sender (TRANSFER_OUT)
        _WriteTransactionToFile(FromClient.GetAccountNumber(), TRANSFER_OUT, Amount,
                                FromClient.GetAccountNumber(),
                                ToClient.GetAccountNumber(),
                                FromClient.GetAccountBalance());

        // Log for receiver (TRANSFER_IN)
        _WriteTransactionToFile(ToClient.GetAccountNumber(), TRANSFER_IN, Amount,
                                FromClient.GetAccountNumber(),
                                ToClient.GetAccountNumber(),
                                ToClient.GetAccountBalance());
    }

    // Admin Operations
    template <typename TAdmin, typename TClient>
    static void LogAdminDeposit(const TAdmin &Admin, const TClient &Client, double Amount)
    {
        _WriteTransactionToFile(Admin.GetAdminUsername(), ADMIN_DEPOSIT, Amount,
                                "-", Client.GetAccountNumber(),
                                Client.GetAccountBalance());
    }

    template <typename TAdmin, typename TClient>
    static void LogAdminWithdraw(const TAdmin &Admin, const TClient &Client, double Amount)
    {
        _WriteTransactionToFile(Admin.GetAdminUsername(), ADMIN_WITHDRAW, Amount,
                                Client.GetAccountNumber(), "-",
                                Client.GetAccountBalance());
    }

    template <typename TAdmin, typename TClient1, typename TClient2>
    static void LogAdminTransfer(const TAdmin &Admin, const TClient1 &FromClient,
                                 const TClient2 &ToClient, double Amount)
    {
        _WriteTransactionToFile(Admin.GetAdminUsername(), ADM_TRANS_OUT, Amount,
                                FromClient.GetAccountNumber(),
                                ToClient.GetAccountNumber(),
                                FromClient.GetAccountBalance());

        _WriteTransactionToFile(Admin.GetAdminUsername(), ADM_TRANS_IN, Amount,
                                FromClient.GetAccountNumber(),
                                ToClient.GetAccountNumber(),
                                ToClient.GetAccountBalance());
    }

    static vector<stTransactionRecord> GetAllTransactions()
    {
        vector<stTransactionRecord> vTransactions;
        fstream MyFile("../data/AllTransactions.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vector<string> vData = clsString::Split(Line, "#//#");

                if (vData.size() >= 8)
                {
                    stTransactionRecord Record;
                    Record.Date = vData[0];
                    Record.Time = vData[1];
                    Record.Username = vData[2];
                    Record.OperationType = vData[3];
                    Record.Amount = stod(vData[4]);
                    Record.FromAccount = vData[5];
                    Record.ToAccount = vData[6];
                    Record.BalanceAfter = stod(vData[7]);

                    vTransactions.push_back(Record);
                }
            }
            MyFile.close();
        }

        return vTransactions;
    }

    static vector<stTransactionRecord> GetAccountTransactions(string AccountNumber)
    {
        vector<stTransactionRecord> vTransactions;
        vector<stTransactionRecord> vAllTransactions = GetAllTransactions();

        for (const stTransactionRecord &Record : vAllTransactions)
        {
            if (Record.Username == AccountNumber ||
                (Record.OperationType == "TRANSFER_OUT" && Record.FromAccount == AccountNumber) ||
                (Record.OperationType == "TRANSFER_IN" && Record.ToAccount == AccountNumber) ||
                (Record.OperationType == "ADMIN_DEPOSIT" && Record.ToAccount == AccountNumber) ||
                (Record.OperationType == "ADMIN_WITHDRAW" && Record.FromAccount == AccountNumber) ||
                (Record.OperationType == "ADM_TRANS_OUT" && Record.FromAccount == AccountNumber) ||
                (Record.OperationType == "ADM_TRANS_IN" && Record.ToAccount == AccountNumber)
                )
            {
                vTransactions.push_back(Record);
            }
        }

        return vTransactions;
    }

    static vector<stTransactionRecord> GetTransactionsByType(string Type)
    {
        vector<stTransactionRecord> vTransactions;
        vector<stTransactionRecord> vAllTransactions = GetAllTransactions();

        for (const stTransactionRecord &Record : vAllTransactions)
        {
            if (Record.OperationType == Type)
            {
                vTransactions.push_back(Record);
            }
        }

        return vTransactions;
    }
    static vector<stTransactionRecord> GetAllAdminTransactions()
    {
        vector<stTransactionRecord> vAdminTransactions;
        vector<stTransactionRecord> vAllTransactions = GetAllTransactions();
    
        for (const stTransactionRecord &Record : vAllTransactions)
        {
            // Include only admin operations
            if (Record.OperationType == "ADMIN_DEPOSIT" ||
                Record.OperationType == "ADMIN_WITHDRAW" ||
                Record.OperationType == "ADM_TRANS_OUT" ||
                Record.OperationType == "ADM_TRANS_IN")
            {
                vAdminTransactions.push_back(Record);
            }
        }
    
        return vAdminTransactions;
    }

};
