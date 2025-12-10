/*clsCurrentAdminSessionScreen Overview
================================================================================
                    clsCurrentAdminSessionScreen.h
================================================================================
Overview:
---------
This screen displays session logs for the CURRENT logged-in admin only.
Shows personal session history (LOGIN and LOGOUT records).

Main Features:
--------------
1. Displays sessions for CurrentAdmin only
2. Shows: Date, Time, Action, Duration
3. Simplified view (no username/permissions - already known)
4. Personal activity tracking

Usage Example:
--------------
clsCurrentAdminSessionScreen::ShowCurrentAdminSessionScreen();
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../base_screen/Global.h"
#include "../../../../../../core/clsAdmin.h"
#include "../../../../../../utils/clsString.h"

using namespace std;

class clsCurrentAdminSessionScreen : protected clsScreen
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

    static vector<stAdminSessionRecord> _GetCurrentAdminSessions()
    {
        vector<stAdminSessionRecord> vSessions;
        vector<string> vLines = clsAdmin::GetAdminSessionLog(CurrentAdmin.GetAdminUsername());

        for (string &Line : vLines)
        {
            stAdminSessionRecord Record = _ConvertLineToRecord(Line);
            vSessions.push_back(Record);
        }

        return vSessions;
    }

    static void _PrintRecordLine(stAdminSessionRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Record.Date;
        cout << "| " << setw(18) << left << Record.Time;
        cout << "| " << setw(10) << left << Record.Action;
        cout << "| " << setw(18) << left << Record.Duration;
        cout << "|";
    }

public:
    static void ShowCurrentAdminSessionScreen()
    {
        vector<stAdminSessionRecord> vSessions = _GetCurrentAdminSessions();

        string Title = "\tMy Session History";
        string SubTitle = "         Username: " + CurrentAdmin.GetAdminUsername();

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t" << string(70, '_') << "\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Date";
        cout << "| " << left << setw(18) << "Time";
        cout << "| " << left << setw(10) << "Action";
        cout << "| " << left << setw(18) << "Duration";
        cout << "|\n"<< "\t" << string(70, '_') << "\n\n";

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

        cout << "\t" << string(70, '_') << endl;
    }
};