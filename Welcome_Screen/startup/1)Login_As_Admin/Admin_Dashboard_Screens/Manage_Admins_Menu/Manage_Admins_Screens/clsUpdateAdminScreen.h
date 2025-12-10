/*clsUpdateAdminScreen Overview
================================================================================
                            clsUpdateAdminScreen.h
================================================================================
Overview:
---------
This file defines the Update Admin Screen — a UI screen responsible for updating
existing Admin details in the system.
It interacts with `clsAdmin` to retrieve, validate, and update Admin information.

The screen is interactive and allows selective or full updates of Admin data.

================================================================================
Class Responsibilities:
-----------------------

1. Prompt the Admin to Enter a AdminUsername to update.
2. Validate input:
       - Ensure AdminUsername exists using clsAdmin::IsAdminExist().
       - Allow cancellation by Entering "0".
3. Retrieve Admin details using:
       clsAdmin::Find(AdminUsername)
4. Allow updating:
       - Specific fields (First Name, Last Name, Email, Phone, Password, Permissions)
       - All fields at once
5. Set permissions with `_ReadPermissionsToSet()`
6. Save updated Admin using clsAdmin::Save() and show feedback messages.
7. Allow repeated updates until the Admin chooses to stop.

================================================================================
Private Helper Methods:
-----------------------

1. _ReadAdminUsername()
   ----------------
   - Prompts Admin to Enter a AdminUsername.
   - Displays "(0 to cancel)" option.
   - Returns the Entered string.

2. _ReadAdminInfo(clsAdmin &Admin)
   -----------------------------
   - Reads all Admin fields from input (first name, last name, email, phone, password, permissions)
   - Uses clsInputValidate for input validation.

3. _ReadUpdatedAdminInfo(clsAdmin &Admin)
   ------------------------------------
   - Provides interactive menu to update selected fields or all fields.
   - Shows updated values after each change.
   - Allows repeated updates until Admin exits.

4. _ReadPermissionsToSet()
   ------------------------
   - Interactively sets Admin permissions.
   - Allows full access or selective access to:
        - List clients
        - Add new clients
        - Delete clients
        - Update clients
        - Find clients
        - Transactions
        - Manage Admins
   - Returns integer bitmask representing permissions.
   - Returns -1 if full access granted.

================================================================================
Public Method:
--------------

ShowUpdateAdminScreen()
---------------------
Main entry point of the screen.

Steps:
1. Clears console and draws screen header.
2. Prompts Admin for a AdminAdminname.
3. Validates AdminUsername existence.
4. Shows Admin details.
5. Asks for confirmation before update.
6. Calls `_ReadUpdatedAdminInfo()` to update selected fields.
7. Saves changes and displays success/failure messages.
8. Prompts for updating another Admin.
9. Repeats process until Admin exits.

================================================================================
Design Notes:
-------------

- The class inherits from clsScreen in protected mode:
      → Can use header/color functions without exposing them publicly.
- Input validation handled by clsInputValidate ensures robust data entry.
- Allows both granular updates (specific fields) and full updates (all fields).
- Uses colored feedback messages:
      - Green for success
      - Red for errors
      - Yellow for warnings/cancellations
- Permission management is flexible, supporting full or selective access.
- Designed for admin interfaces where multiple Admin updates are common.

================================================================================
Usage Example:
--------------

    clsUpdateAdminScreen::ShowUpdateAdminScreen();

Typically called from:
    - Manage Admins Menu (clsManageAdminsScreen)
    - Admin or Debug interfaces
    - Any feature requiring Admin updates

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

class clsUpdateAdminScreen : protected clsScreen

{
private:
    static string _ReadAdminUsername()
    {
        string AdminUsername = "";
        cout << "Please Enter Admin User Name ";
        _SetColor(12);
        cout << "(0 to cancel)";
        _SetColor(7);
        cout << ": ";
        AdminUsername = clsInputValidate::ReadString();
        return AdminUsername;
    }
    static void _ReadAdminInfo(clsAdmin &Admin)
    {
        cout << "\nEnter FirstName: ";
        Admin.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        Admin.SetLastName(clsInputValidate::ReadString());
        cout << "\nEnter Email: ";
        Admin.SetEmail(clsInputValidate::ReadEmail());

        cout << "\nEnter Phone: ";
        Admin.SetPhone(clsInputValidate::ReadPhone());
        cout << "\nEnter Password: ";
        Admin.SetPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permission: ";
        Admin.SetPermissions(_ReadPermissionsToSet());
    }

    static void _ReadUpdatedAdminInfo(clsAdmin &Admin)
    {
        enum enChoice
        {
            eSaveAndExit = 0,
            eFirstName = 1,
            eLastName = 2,
            eEmail = 3,
            ePhone = 4,
            ePassword = 5,
            ePermissions = 6,
            eAll = 7
        };
        enChoice Choice;
        char Continue = 'y';
        do
        {
            _DrawScreenHeader("\tUpdate Admin Information", "", 0);

            cout << "\nSelect field to update:\n";
            cout << "[1] First Name\n";
            cout << "[2] Last Name\n";
            cout << "[3] Email\n";
            cout << "[4] Phone\n";
            cout << "[5] Password\n";
            cout << "[6] Permissions\n";
            cout << "[7] All (Update All Fields)\n";
            cout << "[0] Save and Exit\n";
            cout << "Your choice: ";

            Choice = enChoice(clsInputValidate::ReadIntNumberBetween(0, 7, "Please Enter a valid option (0-7): "));

            switch (Choice)
            {
            case enChoice::eFirstName:
                cout << "\nEnter New First Name: ";
                Admin.SetFirstName(clsInputValidate::ReadString());
                break;

            case enChoice::eLastName:
                cout << "\nEnter New Last Name: ";
                Admin.SetLastName(clsInputValidate::ReadString());
                break;

            case enChoice::eEmail:
                cout << "\nEnter New Email: ";
                Admin.SetEmail(clsInputValidate::ReadEmail());
                break;

            case enChoice::ePhone:
                cout << "\nEnter New Phone: ";
                Admin.SetPhone(clsInputValidate::ReadPhone());
                break;

            case enChoice::ePassword:
                cout << "\nEnter New Password: ";
                Admin.SetPassword(clsInputValidate::ReadString());
                break;

            case enChoice::ePermissions:
                cout << "\nEnter New Permissions: ";
                Admin.SetPermissions(_ReadPermissionsToSet());
                break;

            case enChoice::eAll:
                cout << "\nUpdating All Fields...\n";
                _ReadAdminInfo(Admin);
                break;

            case enChoice::eSaveAndExit:
                cout << "\nSaving changes and exiting...\n";
                break;

            default:
                _SetColor(12);
                cout << "\nInvalid choice, Please try again.\n";
                _SetColor(7);
            }

            if (Choice != enChoice(0))
            {
                _SetColor(10); // green
                cout << "\nField(s) updated successfully!";
                cout << "\n------------------------------------\n";
                _SetColor(7);
                cout << "\nDo you want to continue updating? (y/n): ";
                Continue = clsInputValidate::ReadYesOrNo();
                if (tolower(Continue) != 'y')
                    Choice = enChoice(0);
            }
        } while (Choice != 0);
    }

    static short _ReadPermissionsToSet()
    {
        int Permissions = 0;
        bool GiveAccess = true;

        cout << "\nDo you want to give full access? [1] Yes [0] No: ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");

        if (GiveAccess)
        {
            return -1;
        }
        cout << "====================================\n";
        cout << "Do you want to give access To?\n ";
        cout << "====================================\n";

        cout << "\nShow Client List? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pTranactions;
        }

        cout << "\nManage Admins? y/n? ";
        GiveAccess = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        if (GiveAccess)
        {
            Permissions += clsAdmin::enPermissions::pManageAdmins;
        }
        if (Permissions == 127)
        {
            return -1; // to check if all Permissions
        }
        return Permissions;
    }

public:
    static void ShowUpdateAdminScreen()
    {
        bool UpdateAgain = true;
        while (UpdateAgain)
        {
            system("cls");
            _DrawScreenHeader("\t   Update Admin Screen");

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

            cout << "\nAre you sure you want to update this Admin y/n? ";
            char Answer = clsInputValidate::ReadYesOrNo();

            if (Answer == 'y' || Answer == 'Y')
            {
                cout << "\n\nUpdate Admin Info:";
                cout << "\n____________________\n";

                _ReadUpdatedAdminInfo(Admin1);

                clsAdmin::enSaveResults SaveResult;

                SaveResult = Admin1.Save();

                switch (SaveResult)
                {
                case clsAdmin::enSaveResults::svSucceeded:
                {
                    _SetColor(10); // green
                    cout << "\nAdmin Updated Successfully :-)\n";
                    _SetColor(7);
                    Admin1.Print();
                    break;
                }
                case clsAdmin::enSaveResults::svFaildEmptyObject:
                {
                    _SetColor(12);
                    cout << "\nError Admin was not saved because it's Empty";
                    _SetColor(7);
                    break;
                }
                }
            }
            cout << "Do you want update another account? [1] Yes [0] No: ";
            UpdateAgain = clsInputValidate::ReadIntNumberBetween(0, 1, "Enter 0 or 1 only\n");
        }
    }
};
