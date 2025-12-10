/*Overview clsFindAdminScreen
================================================================================
                            clsFindAdminScreen.h
================================================================================
Overview:
---------
This file defines the Find Admin Screen — a UI screen responsible for searching
and displaying a single Admin's details in the system.
It interacts with `clsAdmin` to validate and retrieve Admin information and shows
the result in a formatted display.

The screen is interactive but read-only — it does NOT modify any Admin data.

================================================================================
Class Responsibilities:
-----------------------

1. Prompt the Admin to Enter a AdminUsername to search.
2. Validate input:
       - Ensure AdminUsername exists using clsAdmin::IsAdminExist().
       - Allow cancellation by Entering "0".
3. Retrieve Admin details using:
       clsAdmin::Find(AdminUsername)
4. Display Admin information if found:
       - Shows Admin data using clsAdmin::Print()
       - Uses colored messages for success (green) or failure (red)
5. Allow repeated searches until the Admin chooses to stop.

================================================================================
Private Helper Methods:
-----------------------

Currently, no private helper methods are explicitly defined in this screen.

================================================================================
Public Method:
--------------

ShowFindAdminScreen()
-------------------
Main entry point of the screen.

Steps:
1. Draws screen header using clsScreen tools.
2. Prompts Admin for a AdminUsername.
3. Handles cancellation if Admin Enters "0".
4. Checks if the AdminUsername exists in the system.
5. Finds the Admin and displays Admin information.
6. Uses colored messages:
       - Green for successful search
       - Red for not found
       - Yellow for cancellation
7. Repeats the search based on Admin input (y/n).

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation is handled by clsInputValidate for robust Admin interaction.
- Designed to be Admin-friendly:
      → Provides clear prompts, success/failure messages, and cancellation option.
- Screen is read-only: No modification of Admin data occurs.
- Supports multiple consecutive searches.

================================================================================
Usage Example:
--------------

    clsFindAdminScreen::ShowFindAdminScreen();

Typically called from:
    - Manage Admins Menu (clsManageAdminsScreen)
    - Admin or Debug interfaces
    - Any feature requiring Admin search

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

class clsFindAdminScreen : protected clsScreen
{

private:
    static string _ReadAdminUsername()
    {
        string AdminUsername = "";
        cout << "Please Enter Admin Name ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AdminUsername = clsInputValidate::ReadString();
        return AdminUsername;
    }

public:
    static void ShowFindAdminScreen()
    {
        bool FindAgain = true;

        _DrawScreenHeader("\t    Find Admin Screen");
        char again = 'y';
        while (FindAgain)
        {
            string AdminUsername = _ReadAdminUsername();

            if (AdminUsername == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }

            while (!clsAdmin::IsAdminExist(AdminUsername))
            {
                cout << "\nAdminUsername [ " << AdminUsername << " ]is Not Found, Enter another one.\n";
                AdminUsername = _ReadAdminUsername();
                if (AdminUsername == "0")
                {
                    _SetColor(14); // Yellow warning
                    cout << "\n⚠ Operation Cancelled.\n\a";
                    _SetColor(7);
                    return;
                }
            }
            clsAdmin Admin1 = clsAdmin::Find(AdminUsername);

            if (!Admin1.IsEmpty())
            {
                _SetColor(10); // green
                cout << "\nAdmin Found :-)\n";
                _SetColor(7);
            }
            else
            {
                _SetColor(12); // red
                cout << "\nAdmin Was not Found :-(\n";
                _SetColor(7);
            }
            Admin1.Print();
            cout << "Do you want to find another account? [1] Yes [0] No: ";
            FindAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};
