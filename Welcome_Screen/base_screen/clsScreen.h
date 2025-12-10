#pragma once

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <windows.h>

#include "../../core/clsAdmin.h"
#include "Global.h"
#include "../../core/clsBankClient.h"
#include "../../utils/clsInputValidate.h"

using namespace std;

class clsScreen
{
protected:
    // Change the text color in the console screen
    static void _SetColor(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
    static void _printCentered(const string& text, int consoleWidth = 80) {
        int len = text.length();
        int spaces = (consoleWidth - len) / 2;
        for(int i = 0; i < spaces; i++) cout << " ";
            cout << text << endl;
    }
    // Draw Header and current Admin and Date
    static void _DrawScreenHeader(const string &Title, const string &SubTitle = "", bool ClearScreen = true)
    {
        if (ClearScreen)
        {
            system("cls");
        }
        _SetColor(14); // Gold for borders
        cout << "\n\n\t\t\t\t\t======================================";
        _SetColor(10); // Light green for title
        cout << "\n\t\t\t\t\t" << Title;

        if (!SubTitle.empty())
            cout << "\n\t\t\t\t\t" << SubTitle;
        _SetColor(14);
        cout << "\n\t\t\t\t\t======================================\n\n";
        _SetColor(7); // Reset color
        if (!CurrentAdmin.IsEmpty())
        {
            _SetColor(11); // Light Cyan
            cout << "\t\t\t\t\tCurrent Admin: ";

            _SetColor(10); // Light Green (fullname)
            cout << CurrentAdmin.FullName() << endl;
        }
        if (!CurrentClient.IsEmpty())
        {
            _SetColor(11); // Light Cyan
            cout << "\t\t\t\t\tCurrent Client: ";

            _SetColor(10); // Light Green (fullname)
            cout << CurrentClient.FullName() << endl;
        }
        _SetColor(11); // Light Cyan
        cout << "\t\t\t\t\tDate: ";

        _SetColor(10); // Light Green (date)
        cout << clsDate::DateToString(clsDate::GetSystemDate()) << endl;
        cout << endl;
        _SetColor(7); // Reset color
    }

    static void _DrawEndScreen(const string &Title = "\t\tEnd Screen")
    {
        _SetColor(14);
        cout << "\n\t\t\t\t\t======================================";
        _SetColor(12); // Red for end message
        cout << "\n\t\t\t\t\t" << Title;
        _SetColor(14);
        cout << "\n\t\t\t\t\t======================================\n\n";
        _SetColor(11); // Cyan for thank you
        cout << "\t\t\t\t\tThank you for using the program!";
        _SetColor(10); // Light Green (FullName)
        cout << CurrentAdmin.FullName() << endl;
        _SetColor(11);
        // simple Animation
        cout <<"\t\t\t\t\t";
        for (int i = 0; i < 15; i++)
        {
            cout << ".";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(250));
        }
        cout << "\n\t\t\t\t\tPress any key to exit...";
        _SetColor(7);
        cin.ignore();
    }

};
