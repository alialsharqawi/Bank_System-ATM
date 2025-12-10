/*clsCurrentClientSessionScreen Overview
================================================================================
                    clsCurrentClientSessionScreen.h
================================================================================
Overview:
---------
This screen displays session logs for the CURRENT logged-in client only.
Shows personal ATM session history (LOGIN and LOGOUT records).

Main Features:
--------------
1. Displays sessions for CurrentClient only
2. Shows: Date, Time, Action, Duration
3. Simplified view (no account number - already known)
4. Personal ATM activity tracking

Usage Example:
--------------
clsCurrentClientSessionScreen::ShowCurrentClientSessionScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../base_screen/clsScreen.h"
#include "../../../base_screen/Global.h"
#include "../../../../core/clsBankClient.h"
#include "../../../../utils/clsString.h"

using namespace std;

class clsCurrentClientSessionScreen : protected clsScreen
{

private:
    struct stClientSessionRecord
    {
        string Date;
        string Time;
        string Action;
        string AccountNumber;
        string FullName;
        string Duration;
    };

    static stClientSessionRecord _ConvertLineToRecord(string Line)
    {
        stClientSessionRecord Record;
        vector<string> vData = clsString::Split(Line, "#//#");

        if (vData.size() >= 6)
        {
            Record.Date = vData[0];
            Record.Time = vData[1];
            Record.Action = vData[2];
            Record.AccountNumber = vData[3];
            Record.FullName = vData[4];
            Record.Duration = vData[5];
        }

        return Record;
    }

    static vector<stClientSessionRecord> _GetCurrentClientSessions()
    {
        vector<stClientSessionRecord> vSessions;
        vector<string> vLines = clsBankClient::GetClientSessionLog(CurrentClient.GetAccountNumber());

        for (string &Line : vLines)
        {
            stClientSessionRecord Record = _ConvertLineToRecord(Line);
            vSessions.push_back(Record);
        }

        return vSessions;
    }

    static void _PrintRecordLine(stClientSessionRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Record.Date;
        cout << "| " << setw(18) << left << Record.Time;
        cout << "| " << setw(10) << left << Record.Action;
        cout << "| " << setw(18) << left << Record.Duration;
        cout << "|";
    }

public:
    static void ShowCurrentClientSessionScreen()
    {
        vector<stClientSessionRecord> vSessions = _GetCurrentClientSessions();

        string Title = "\tMy Session History";
        string SubTitle = "\t    Account: " + CurrentClient.GetAccountNumber();

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t" << string(75, '_') << "\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Date";
        cout << "| " << left << setw(18) << "Time";
        cout << "| " << left << setw(10) << "Action";
        cout << "| " << left << setw(18) << "Duration";
        cout << "|\n" << "\t" << string(75, '_') << "\n\n";

        if (vSessions.size() == 0)
        {
            _SetColor(14);
            cout << "\t\t\t\tNo Sessions Available!\n";
            _SetColor(7);
        }
        else
        {
            for (const stClientSessionRecord &Record : vSessions)
            {
                _PrintRecordLine(Record);
                cout << endl;
            }
        }

        cout << "\t" << string(75, '_') << endl;
    }
};