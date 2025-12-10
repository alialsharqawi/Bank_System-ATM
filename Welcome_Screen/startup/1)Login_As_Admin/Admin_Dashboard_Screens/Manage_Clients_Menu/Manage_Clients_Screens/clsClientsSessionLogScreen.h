/*clsClientsSessionLogScreen Overview
================================================================================
                        clsClientsSessionLogScreen.h
================================================================================
Overview:
---------
This screen displays all client session logs (LOGIN and LOGOUT records).
Shows complete session history for all clients in the system.

Main Features:
--------------
1. Displays all client sessions from ClientsSessionLog.txt
2. Shows: Date, Time, Action, Account Number, Full Name, Duration
3. Formatted table display with proper alignment
4. Handles empty log files gracefully

Usage Example:
--------------
clsClientsSessionLogScreen::ShowClientsSessionLogScreen();
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

class clsClientsSessionLogScreen : protected clsScreen
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

    static vector<stClientSessionRecord> _GetSessionsList()
    {
        vector<stClientSessionRecord> vSessions;
        vector<string> vLines = clsBankClient::GetClientSessionLog();

        for (string &Line : vLines)
        {
            stClientSessionRecord Record = _ConvertLineToRecord(Line);
            vSessions.push_back(Record);
        }

        return vSessions;
    }

    static void _PrintRecordLine(stClientSessionRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << Record.Date;
        cout << "| " << setw(15) << left << Record.Time;
        cout << "| " << setw(8) << left << Record.Action;
        cout << "| " << setw(12) << left << Record.AccountNumber;
        cout << "| " << setw(25) << left << Record.FullName;
        cout << "| " << setw(15) << left << Record.Duration;
        cout << "  |";
    }

public:
    static void ShowClientsSessionLogScreen()
    {
        vector<stClientSessionRecord> vSessions = _GetSessionsList();

        string Title = "\tClients SessionS Log";

        //string SubTitle = "\t    (" + to_string(vSessions.size()) + ") Session(s).";

        _DrawScreenHeader(Title);

        cout << setw(8) << left << "" << "\n\t" << string(102, '_') << "\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "Date";
        cout << "| " << left << setw(15) << "Time";
        cout << "| " << left << setw(8) << "Action";
        cout << "| " << left << setw(12) << "Account";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(15) << "Duration";
        cout << "  |\n"<< "\t" << string(102, '_') << "\n\n";

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

        cout << "\t" << string(102, '_') << endl;
    }
};