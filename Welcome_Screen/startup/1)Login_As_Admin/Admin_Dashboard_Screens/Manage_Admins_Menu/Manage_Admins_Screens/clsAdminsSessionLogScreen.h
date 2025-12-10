/*clsAdminsSessionLogScreen Overview
================================================================================
                        clsAdminsSessionLogScreen.h
================================================================================
Overview:
---------
This screen displays all admin session logs (LOGIN and LOGOUT records).
Shows complete session history for all admins in the system.

Main Features:
--------------
1. Displays all admin sessions from AdminsSessionLog.txt
2. Shows: Date, Time, Action, Username, Full Name, Permissions, Duration
3. Formatted table display with proper alignment
4. Handles empty log files gracefully

Usage Example:
--------------
clsAdminsSessionLogScreen::ShowAdminsSessionLogScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../../core/clsAdmin.h"
#include "../../../../../../utils/clsString.h"

using namespace std;

class clsAdminsSessionLogScreen : protected clsScreen
{

private:
    struct stAdminSessionRecord
    {
        string Date;
        string Time;
        string Action;
        string Username;
        string FullName;
        short Permissions;
        string Duration;
    };

    static stAdminSessionRecord _ConvertLineToRecord(string Line)
    {
        stAdminSessionRecord Record;
        vector<string> vData = clsString::Split(Line, "#//#");

        if (vData.size() >= 7)
        {
            Record.Date = vData[0];
            Record.Time = vData[1];
            Record.Action = vData[2];
            Record.Username = vData[3];
            Record.FullName = vData[4];
            Record.Permissions = stoi(vData[5]);
            Record.Duration = vData[6];
        }

        return Record;
    }

    static vector<stAdminSessionRecord> _GetSessionsList()
    {
        vector<stAdminSessionRecord> vSessions;
        vector<string> vLines = clsAdmin::GetAdminSessionLog();

        for (string &Line : vLines)
        {
            stAdminSessionRecord Record = _ConvertLineToRecord(Line);
            vSessions.push_back(Record);
        }

        return vSessions;
    }

    static void _PrintRecordLine(stAdminSessionRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << Record.Date;
        cout << "| " << setw(15) << left << Record.Time;
        cout << "| " << setw(8) << left << Record.Action;
        cout << "| " << setw(12) << left << Record.Username;
        cout << "| " << setw(22) << left << Record.FullName;
        cout << "| " << setw(8) << left << Record.Permissions;
        cout << "| " << setw(12) << left << Record.Duration;
        cout << "    |";
    }

public:
    static void ShowAdminsSessionLogScreen()
    {
        vector<stAdminSessionRecord> vSessions = _GetSessionsList();

        string Title = "\tAdmins Session Log";
        //string SubTitle = "\t    (" + to_string(vSessions.size()) + ") Session(s).";

        _DrawScreenHeader(Title);

        cout << setw(8) << left << "" << "\n\t" << string(108, '_') << "\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "Date";
        cout << "| " << left << setw(15) << "Time";
        cout << "| " << left << setw(8) << "Action";
        cout << "| " << left << setw(12) << "Username";
        cout << "| " << left << setw(22) << "Full Name";
        cout << "| " << left << setw(8) << "Perms";
        cout << "| " << left << setw(12) << "Duration";
        cout << "    |\n"<< "\t" << string(108, '_') << "\n\n";

        if (vSessions.size() == 0)
        {
            _SetColor(14);
            cout << "\t\t\t\tNo Sessions Available!\n";
            _SetColor(7);
        }
        else
        {
            for (const stAdminSessionRecord &Record : vSessions)
            {
                _PrintRecordLine(Record);
                cout << endl;
            }
        }

        cout << "\t" << string(108, '_') << endl;
    }
};