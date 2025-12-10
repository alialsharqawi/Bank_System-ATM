/*clsAddNewAdminScreen Overview
================================================================================
                          clsAddNewAdminScreen Class Reference
================================================================================
Purpose:
--------
Handles the console screen and logic for adding a new Admin in the system.

Features:
---------
- Read and validate Admin information:
  - First Name
  - Last Name
  - Email
  - Phone
  - Password
  - Permissions
- Check for duplicate AdminUsernames
- Display Admin details after creation
- Option to cancel operation
- Loop to add multiple Admins
- Uses clsInputValidate for safe input reading
- Uses clsScreen for consistent console UI

Private Methods:
----------------
1. _ReadPermissionsToSet()
   - Reads Admin permissions from console input.
   - Option for full access or individual permissions.
   - Returns an integer representing permission flags.

2. _ReadAdminInfo(clsAdmin &Admin)
   - Reads and sets all Admin information.
   - Calls _ReadPermissionsToSet() for permissions.

3. _PrintAdmin(clsAdmin Admin)
   - Displays all Admin information in a formatted "Admin Card".

4. _ReadAdminAdminname()
   - Reads AdminAdminname from console.
   - Allows cancellation by Entering "0".

Public Methods:
---------------
1. ShowAddNewAdminScreen()
   - Displays the add new Admin screen.
   - Handles Admin input for AdminUsername, information, permissions.
   - Saves Admin using clsAdmin::Save().
   - Displays success/error messages.
   - Allows adding multiple Admins in a loop.

Usage Example:
--------------
clsAddNewAdminScreen::ShowAddNewAdminScreen();

Notes:
------
- Relies on clsScreen for drawing headers.
- Uses clsInputValidate to ensure valid Admin input.
- Provides interactive console UI with color highlighting.
- Permission system uses clsAdmin::enPermissions flags.
- Handles edge cases like duplicate AdminUsernames and cancellation.

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


using namespace std;

class clsAddNewAdminScreen : protected clsScreen
{
private:
    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            return -1;

        cout << "\nSelect permissions to grant:\n";

        cout << "\n[1] Show Client List? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pListClients;

        cout << "\n[2] Add New Client? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pAddNewClient;

        cout << "\n[3] Find Client? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pFindClient;

        cout << "\n[4] Update Client Info? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pUpdateClients;

        cout << "\n[5] Show All Balances? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pTotalBalances;

        cout << "\n[6] Transactions? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pTranactions;

        cout << "\n[7] Delete Client? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pDeleteClient;

        cout << "\n[8] Manage Admins? (y/n)? ";
        Answer = clsInputValidate::ReadYesOrNo();
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsAdmin::enPermissions::pManageAdmins;

        if (Permissions == 255)
            return -1; 

        return Permissions;
    }

    static void _ReadAdminInfo(clsAdmin &Admin)
    {
        cout << "\nEnter First Name: ";
        Admin.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter Last Name: ";
        Admin.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Admin.SetEmail(clsInputValidate::ReadEmail());

        cout << "\nEnter Phone: ";
        Admin.SetPhone(clsInputValidate::ReadPhone());

        cout << "\nEnter Password: ";
        Admin.SetPassword(clsInputValidate::ReadString());

        _SetColor(14); // yellow
        cout << "\nSet Permissions Section.";
        _SetColor(7);
        Admin.SetPermissions(_ReadPermissionsToSet());
    }

    static void _PrintAdmin(clsAdmin Admin)
    {
        cout << "\nAdmin Card:";
        cout << "\n___________________";
        cout << "\nFirst Name  : " << Admin.GetFirstName();
        cout << "\nLast Name   : " << Admin.GetLastName();
        cout << "\nFull Name   : " << Admin.FullName();
        cout << "\nEmail       : " << Admin.GetEmail();
        cout << "\nPhone       : " << Admin.GetPhone();
        cout << "\nAdmin Name   : " << Admin.GetAdminUsername();
        cout << "\nPassword    : " << Admin.GetPassword();
        cout << "\nPermissions : " << Admin.GetPermissions();
        cout << "\n___________________\n";
    }

    static string _ReadAdminUsername()
    {
        string AdminUserName = "";

        while (true)
        {
            cout << "Please Set Admin User Name ";
            _SetColor(12);
            cout << "(0 to cancel)";
            _SetColor(7);
            cout << ": ";
            AdminUserName = clsInputValidate::ReadString();

            if (AdminUserName == "0") 
                return AdminUserName;

            
            if (!AdminUserName.empty() && AdminUserName[0] == 'A')
                return AdminUserName;

            _SetColor(12);
            cout << "\nInvalid Admin Username! Must start with capital 'A'. Try again.\n";
            _SetColor(7);
        }
    }


public:
    static void ShowAddNewAdminScreen(string Header ="\t  Add New Admin Screen")
    {
        _DrawScreenHeader(Header);

        string AdminUsername = _ReadAdminUsername();

        if (AdminUsername == "0")
        {
            _SetColor(14); // Yellow warning
            cout << "\n⚠ Operation Cancelled.\n\a";
            _SetColor(7);
            return;
        }
        while (clsAdmin::IsAdminExist(AdminUsername))
        {
            cout << "\nAdminUsername [ " << AdminUsername << " ] is already used, Enter another one.\n";
            AdminUsername = _ReadAdminUsername();
            if (AdminUsername == "0")
            {
                _SetColor(14); // Yellow warning
                cout << "\n⚠ Operation Cancelled.\n\a";
                _SetColor(7);
                return;
            }
        }

        clsAdmin NewAdmin = clsAdmin::GetAddNewAdminObject(AdminUsername);

        _ReadAdminInfo(NewAdmin);

        clsAdmin::enSaveResults SaveResult = NewAdmin.Save();

        switch (SaveResult)
        {
        case clsAdmin::enSaveResults::svSucceeded:
            _SetColor(10); // green
            cout << "\nAdmin Added Successfully :-)\n";
            _SetColor(7);
            _PrintAdmin(NewAdmin);
            break;

        case clsAdmin::enSaveResults::svFaildEmptyObject:
            _SetColor(14);
            cout << "\nError: Admin was not saved because it's Empty!";
            _SetColor(7);
            break;

        case clsAdmin::enSaveResults::svFaildAdminExists:
            _SetColor(10);
            cout << "\nError: Admin was not saved because AdminUsername is used!\n";
            _SetColor(7);
            break;
        }
    }
};
