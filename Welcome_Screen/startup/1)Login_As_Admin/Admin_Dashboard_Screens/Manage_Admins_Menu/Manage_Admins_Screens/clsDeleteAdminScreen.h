/*clsDeleteAdminScreen Overview
================================================================================
                            clsDeleteAdminScreen.h
================================================================================
Overview:
---------
This file defines the Delete Admin Screen — a UI screen responsible for deleting
existing Admins from the system.
It interacts with `clsAdmin` to retrieve, validate, and delete Admin accounts.

The screen is interactive and ensures Admin confirmation before deletion.

================================================================================
Class Responsibilities:
-----------------------

1. Prompt the Admin to Enter a AdminUsername to delete.
2. Validate input:
       - Ensure AdminUsername exists using clsAdmin::IsAdminExist().
       - Allow cancellation by Entering "0".
3. Retrieve Admin details using:
       clsAdmin::Find(AdminUsername)
4. Display Admin details using Admin1.Print().
5. Confirm deletion with the Admin.
6. Delete the Admin using clsAdmin::Delete().
7. Show success or error messages after deletion.
8. Allow repeated deletion until the Admin chooses to stop.

================================================================================
Private Helper Methods:
-----------------------

1. _ReadAdminUsername()
   ----------------
   - Prompts Admin to Enter a AdminUsername.
   - Displays "(0 to cancel)" option.
   - Returns the Entered string.

================================================================================
Public Method:
--------------

ShowDeleteAdminScreen()
---------------------
Main entry point of the screen.

Steps:
1. Clears console and draws screen header.
2. Prompts Admin for a AdminUsername.
3. Validates AdminUsername existence.
4. Shows Admin details.
5. Asks for confirmation before deletion.
6. Calls Admin1.Delete() to remove Admin.
7. Displays success (green) or error (red) messages.
8. Prompts for deleting another Admin.
9. Repeats process until Admin exits.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation is handled by clsInputValidate for robust data entry.
- Uses colored feedback messages:
      - Green for successful deletion
      - Red for errors
      - Yellow for warnings/cancellations
- Designed for admin interfaces where multiple Admin deletions may be required.
- Prevents accidental deletion by requiring Admin confirmation.

================================================================================
Usage Example:
--------------

    clsDeleteAdminScreen::ShowDeleteAdminScreen();

Typically called from:
    - Manage Admins Menu (clsManageAdminsScreen)
    - Admin or Debug interfaces
    - Any feature requiring Admin removal

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


class clsDeleteAdminScreen : protected clsScreen
{

private:
    static string _ReadAdminUsername()
    {
        string AdminUsername = "";
        cout << "Please Enter User Name ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AdminUsername = clsInputValidate::ReadString();
        return AdminUsername;
    }

public:
    static void ShowDeleteAdminScreen()
    {
        bool DeleteAgain = true;
        while (DeleteAgain)
        {
            system("cls");
            _DrawScreenHeader("\t   Delete Admin Screen");

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

            Admin1.Print();

            cout << "\nAre you sure you want to delete this Admin y/n? ";

            char Answer = clsInputValidate::ReadYesOrNo();

            if (Answer == 'y' || Answer == 'Y')
            {

                if (Admin1.Delete())
                {
                    _SetColor(10); // green
                    cout << "\nAdmin Deleted Successfully :-)\n";
                    _SetColor(7); // defualt
                    Admin1.Print();
                }
                else
                {
                    _SetColor(12); // Red
                    cout << "\nError Admin Was not Deleted\n";
                    _SetColor(7); // defualt
                }
            }

            cout << "Do You want Delete another account? [1] Yes [0] No: ";
            DeleteAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};
