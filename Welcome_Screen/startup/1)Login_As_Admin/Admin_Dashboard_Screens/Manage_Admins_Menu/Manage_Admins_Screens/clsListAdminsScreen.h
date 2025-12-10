/*Overview clsListAdminsScreen
================================================================================
                            clsListAdminsScreen.h
================================================================================
Overview:
---------
This file defines the Admins List Screen — a UI screen responsible for displaying
all system Admins in a formatted table.
It loads the Admin list from `clsAdmin`, prints a well-aligned table with columns,
and handles the case when the system has no Admins.

The screen is read-only and does NOT modify any data.

================================================================================
Class Responsibilities:
-----------------------

1. Retrieve all Admins using:
       clsAdmin::GetAdminsList()

2. Display a well-formatted table containing:
       - AdminUsername
       - Full Name
       - Phone
       - Email
       - Password
       - Permissions

3. Print professional table borders for readability.
4. Show a custom message when no Adminusers exist.

================================================================================
Private Helper Methods:
-----------------------

1. _PrintAdminRecordLine(const clsAdmin& Admin)
   -----------------------------------------
   - Prints one row in the Admin table.
   - Uses setw() formatting for clean alignment.
   - Email column is widened to 30 chars for better visibility.
   - Final layout example:

        | AdminUsername | Full Name | Phone | Email | Password | Permissions |

2. _PrintLine()
   -------------
   - Prints a horizontal line (___________) to visually separate sections.
   - Width = 112 chars → chosen specifically to match table width.

================================================================================
Public Method:
--------------

ShowAdminsList()
---------------
Main entry point of the screen.

Steps:
1. Loads all Admins.
2. Draws screen header using clsScreen tools.
3. Prints table header (column titles).
4. Prints all Admins if available.
5. Otherwise shows a yellow "No Admins Available" message.
6. Prints closing line for clean UI.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- The design maintains consistency with all other screens in the system.
- No input from the Admin is required on this screen.
- Table formatting is carefully aligned for professional output.

================================================================================
Usage Example:
--------------

    clsListAdminsScreen::ShowAdminsList();

Typically called from:
    - Manage Admins Menu (clsManageAdminsScreen)
    - Admin interfaces
    - Debug screens

================================================================================
End of Documentation
================================================================================
*/

#pragma once

#include <iostream>
#include <iomanip>

#include "../../../../../base_screen/clsScreen.h"
#include "../../../../../../core/clsAdmin.h"
#include "../../../../../../utils/clsInputValidate.h"

class clsListAdminsScreen : protected clsScreen
{

private:
    static void _PrintAdminRecordLine(const clsAdmin &Admin)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << Admin.GetAdminUsername();
        cout << "| " << setw(25) << left << Admin.FullName();
        cout << "| " << setw(12) << left << Admin.GetPhone();
        cout << "| " << setw(30) << left << Admin.GetEmail(); // Email column widened
        cout << "| " << setw(10) << left << Admin.GetPassword();
        cout << "| " << setw(12) << left << Admin.GetPermissions() << "|";
    }


public:
    static void ShowAdminsList()
    {
        vector<clsAdmin> vAdmins = clsAdmin::GetAdminsList();

        string Title = "\t  Admin List Screen";
        string SubTitle = (vAdmins.empty() ? "\t    (0) No Admins." : "\t    (" + to_string(vAdmins.size()) + ") Admin" + (vAdmins.size() > 1 ? "s." : "."));

        _DrawScreenHeader(Title, SubTitle);

        //print line
        cout << setw(8) << left << "" << "\n\t" << string(114, '_') << "\n"
             << endl;

        cout << setw(8) << left << "" << "|" << left << setw(12) << "AdminUserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(30) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions" << "|";

        //print line
        cout << setw(8) << left << "" << "\n\t" << string(114, '_') << "\n"
             << endl;

        if (vAdmins.empty())
        {
            _SetColor(14); // yellow
            cout << "\t\t\t\tNo Admins Available In the System!\n";
            _SetColor(7);
        }
        else
        {
            for (const clsAdmin &Admin : vAdmins)
            {
                _PrintAdminRecordLine(Admin);
                cout << endl;
            }
        }

        //print line
        cout  << "\t" << string(114, '_') << "\n" << endl;
    }
};
