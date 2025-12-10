/*clsAdmin Overview
================================================================================
                                   clsAdmin.h
================================================================================
Overview:
---------
This file defines the clsAdmin class, which represents a Admin in the banking
system. Each Admin has personal information (inherited from clsPerson), login
credentials, and system permissions. The class also handles reading, writing,
updating, deleting, and searching Admins in the data\\Admins.text file.

The class also manages:
- Admin authentication (AdminUserName + password)
- Permission checking using bitwise operations
- Logging login activity
- Logging transfer transactions

================================================================================
Data Storage Format:
--------------------
Each Admin is stored in the file "data\\Admins.text" in the following structure:

FirstName || LastName || Email || Phone || AdminUserName || EncryptedPassword || Permissions

Transactions performed by Admins are logged in:
- Transactions.txt
Login activity is logged in:
- LoginRegister.txt

================================================================================
Main Features:
--------------
1. Load and save all Admins from/to file.
2. Encrypt and decrypt passwords automatically.
3. Add new Admins.
4. Update existing Admins.
5. Delete Admins safely.
6. Find Admins by AdminUserName or by credentials.
7. Check Admin access permissions using bitwise flags.
8. Log transactions and login history.

================================================================================
Internal Modes:
---------------
Each clsAdmin object has a "Mode" that determines its purpose:

- EmptyMode:
    The object represents "no Admin found".

- UpdateMode:
    Represents an existing Admin loaded from file and ready for updating.

- AddNewMode:
    Represents a new Admin to be created and added to file.

================================================================================
Permission System:
------------------
Permissions are stored as integers using bitwise flags:

    eAll            = -1   (full permissions)
    pListClients    = 1
    pAddNewClient   = 2
    pFindClient     = 4
    pUpdateClients  = 8
    pTotalBalances  = 16
    pTranactions    = 32
    pDeleteClient   = 64
    pManageAdmins   = 128

Permission checks use:
    (AdminPermission & RequiredPermission) == RequiredPermission

================================================================================
Important Methods:
------------------
● Print()
    void fun. print Admin information

● Find(AdminUserName)
    Returns an Admin object if the AdminUserName exists.

● Find(AdminUserName, password)
    Used for login authentication.

● Save()
    Adds or updates an Admin depending on the object's Mode.

● Delete()
    Marks the Admin as deleted and re-saves the file.

● CheckAccessPermission(permission)
    Returns true only if the Admin has the specific permission.

● AddTransactionToFile(...)
    Logs a transfer operation.

● AddAdminLoginEntryToFile(...)
    Logs a Admin login.

================================================================================
File Handling:
--------------
The class uses text-based storage. When updating:
- Load all Admins into a vector.
- Modify or delete an Admin inside the vector.
- Write the vector back to the file.

New Admins are appended to the file without loading all Admins.

================================================================================
Security Notes:
---------------
- Passwords are stored encrypted using clsUtil::EncryptText().
- Decrypting happens only when loading data into memory.
- Passwords are NEVER written to logs.

================================================================================
Usage Summary:
--------------
- Admin panels use clsAdmin to add, list, edit, delete Admins.
- The login screen uses Find(AdminUserName, password).
- Transfer screens use AddTransactionToFile() to log operations.
- Every login writes to LoginRegister.txt automatically.

================================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"         
#include "../utils/clsString.h"
#include "../utils/clsDate.h"  
#include "../utils/clsUtil.h"  

using namespace std;

class clsAdmin : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;
    string _AdminUserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    static clsAdmin _ConvertLinetoAdminObject(string Line, string Seperator = " || ")
    {
        vector<string> vAdminData = clsString::Split(Line, Seperator);

        return clsAdmin(enMode::UpdateMode,
                        vAdminData[0], vAdminData[1], vAdminData[2],
                        vAdminData[3], vAdminData[4], clsUtil::DecryptText(vAdminData[5]), // to DecryptPassword from text File
                        stoi(vAdminData[6]));
    }

    static string _ConverAdminObjectToLine(const clsAdmin &Admin, string Seperator = " || ")
    {
        string AdminRecord = "";

        AdminRecord += Admin.GetFirstName() + Seperator;
        AdminRecord += Admin.GetLastName() + Seperator;
        AdminRecord += Admin.GetEmail() + Seperator;
        AdminRecord += Admin.GetPhone() + Seperator;
        AdminRecord += Admin.GetAdminUsername() + Seperator;
        AdminRecord += clsUtil::EncryptText(Admin.GetPassword()) + Seperator; // to Eecrypt Password to text File
        AdminRecord += to_string(Admin.GetPermissions());

        return AdminRecord;
    }

    static vector<clsAdmin> _LoadAdminsDataFromFile()
    {
        vector<clsAdmin> vAdmins;
        fstream MyFile("../data/Admins.text", ios::in); // Read mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) // Read line by line from text file
            {
                clsAdmin Admin = _ConvertLinetoAdminObject(Line); // convert Each line in text file to Admin Object
                vAdmins.push_back(Admin);                         // append Admin Object to vector from data type clsAdmin
            }
            MyFile.close();
        }

        return vAdmins;
    }

    static void _SaveAdminDataToFile(const vector<clsAdmin> &vAdmins)
    {
        fstream MyFile("../data/Admins.text", ios::out); // write mode

        if (MyFile.is_open())
        {
            for (const clsAdmin &A : vAdmins)
            {
                if (!A.IsMarkedForDelete())
                {
                    string DataLine = _ConverAdminObjectToLine(A);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile("../data/Admins.text", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl; // append Admin Record to Text File
            MyFile.close();
        }
    }

    void _Update()
    {
        // Update process steps:
        // 1. In the update Admin screen, create a new Admin object containing the updated data.
        // 2. Call this function and pass the new Admin object.
        // 3. The function loads all Admins from the storage into vAdmins.
        // 4. Iterate through each Admin in vAdmins.
        // 5. When a Admin in the vector has the same AdminUserName (or ID) as the new Admin:
        //   A = *this;
        //    Here: A is a reference to the existing Admin in the vector,
        //    and *this is the new Admin from the update Admin screen.
        //    This line replaces the old Admin's data with the new data in the vector.
        // then save data to file
        vector<clsAdmin> vAdmins = _LoadAdminsDataFromFile();
        for (clsAdmin &A : vAdmins)
        {
            if (A.GetAdminUsername() == this->_AdminUserName)
            {
                A = *this;
                break;
            }
        }
        _SaveAdminDataToFile(vAdmins);
    }

    void _AddNew()
    {
        // Add New Admin process from the Add New Admin screen:
        // 1. In the Add New Admin screen, create a new Admin object containing the data Entered by the Admin.
        // 2. Call the _AddNew() method using this new Admin object.
        // 3. Inside _AddNew(), the current object (*this) represents the new Admin to be added.
        // 4. _ConverAdminObjectToLine(*this) converts this Admin object into a single line of text
        //    suitable for storage in the data file.
        // 5. _AddDataLineToFile(...) takes that text line and appends it to the end of the file,
        //    effectively saving the new Admin's data persistently.
        // 6. After this method finishes execution, the new Admin is stored in the file
        //    and can later be loaded back into memory when needed.
        _AddDataLineToFile(_ConverAdminObjectToLine(*this));
    }

    static clsAdmin _GetEmptyAdminObject()
    {
        return clsAdmin(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    // Inherited Constructor
    clsAdmin(enMode Mode, string FirstName, string LastName,
             string Email, string Phone, string AdminUserName,
             string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AdminUserName = AdminUserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    enum enPermissions
    {
        eAll = -1,           // All Permissions
        pListClients = 1,    // [1] Show Client List
        pAddNewClient = 2,   // [2] Add New Client
        pFindClient = 4,     // [3] Find Client
        pUpdateClients = 8,  // [4] Update Client Info
        pTotalBalances = 16, // [5] Show All Balances
        pTranactions = 32,   // [6] Transactions
        pDeleteClient = 64,  // [7] Delete Client
        pManageAdmins = 128  // [8] Manage Admins
    };
    //--------------------------------------
    // Getter and Setter
    //--------------------------------------
    string GetAdminUsername() const { return _AdminUserName; } // Avoid using the name GetAdminUsername because it conflicts with a Windows API macro.
    void SetAdminUsername(string AdminUserName) { _AdminUserName = AdminUserName; }

    string GetPassword() const { return _Password; }
    void SetPassword(string Password) { _Password = Password; }

    int GetPermissions() const { return _Permissions; }
    void SetPermissions(int Permissions) { _Permissions = Permissions; }
    //--------------------------------------
    // Print Admin info
    //--------------------------------------
    void Print()
    {
        // named after "Print" to hidden print in base class(person)
        cout << "\nAdmin Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << GetFirstName();
        cout << "\nLastName    : " << GetLastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << GetEmail();
        cout << "\nPhone       : " << GetPhone();
        cout << "\nUser Name   : " << GetAdminUsername();
        cout << "\nPassword    : " << GetPassword();
        cout << "\nPermissions : " << GetPermissions();
        cout << "\n___________________\n";
    }
    //--------------------------------------
    // Find Admin
    //--------------------------------------
    static clsAdmin Find(string AdminUserName) // Find BY User Name *used in find Admin screen
    {
        fstream MyFile("../data/Admins.text", ios::in); // Read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsAdmin Admin = _ConvertLinetoAdminObject(Line);
                if (Admin.GetAdminUsername() == AdminUserName)
                {
                    MyFile.close();
                    return Admin;
                }
            }
            MyFile.close();
        }
        return _GetEmptyAdminObject();
    }

    static clsAdmin Find(string AdminUserName, string Password) // Find BY User Name&Password *used in login screen
    {
        fstream MyFile("../data/Admins.text", ios::in); // Read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsAdmin Admin = _ConvertLinetoAdminObject(Line);
                if (Admin.GetAdminUsername() == AdminUserName && Admin.GetPassword() == Password)
                {
                    MyFile.close();
                    return Admin;
                }
            }
            MyFile.close();
        }
        return _GetEmptyAdminObject();
    }
    //--------------------------------------
    // Save Results
    //--------------------------------------
    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAdminExists = 2
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFaildEmptyObject;

        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;

        case enMode::AddNewMode:
            if (clsAdmin::IsAdminExist(_AdminUserName))
                return enSaveResults::svFaildAdminExists;
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        default:
            return enSaveResults::svFaildEmptyObject;
        }
    }

    //---------------------------------------------
    // Utilities
    //---------------------------------------------

    bool IsEmpty() const { return (_Mode == enMode::EmptyMode); }
    bool IsMarkedForDelete() const { return _MarkedForDelete; }

    static bool IsAdminExist(string AdminUserName)
    {
        clsAdmin Admin = clsAdmin::Find(AdminUserName);
        return !Admin.IsEmpty();
    }

    static clsAdmin GetAddNewAdminObject(string AdminUserName)
    {
        return clsAdmin(enMode::AddNewMode, "", "", "", "", AdminUserName, "", 0);
    }

    static vector<clsAdmin> GetAdminsList()
    {
        return _LoadAdminsDataFromFile();
    }
    //---------------------------------------------
    // Delete Admin
    //---------------------------------------------
    bool Delete()
    {
        // Delete Admin process:
        // 1. Load all Admins from the data file into a local vector vAdmins.
        // 2. Iterate through each Admin in the vector:
        //    - Check if the AdminUserName of the current Admin (A.GetAdminUsername())
        //      matches the AdminUserName of this object (_AdminUserName).
        //    - If a match is found, mark this Admin for deletion by setting
        //      A._MarkedForDelete = true.
        //    - Break the loop once the matching Admin is found and marked.
        // 3. Save the updated vector back to the data file using _SaveAdminDataToFile(vAdmins),
        //    so the deletion is persisted.
        // 4. Replace the current object (*this) with an empty Admin object
        //    by calling _GetEmptyAdminObject(), effectively resetting it.
        // 5. Return true to indicate that the delete operation was completed successfully.
        vector<clsAdmin> vAdmins = _LoadAdminsDataFromFile();
        for (clsAdmin &A : vAdmins)
        {
            if (A.GetAdminUsername() == _AdminUserName)
            {
                A._MarkedForDelete = true;
                break;
            }
        }
        _SaveAdminDataToFile(vAdmins);
        *this = _GetEmptyAdminObject();
        return true;
    }

    //---------------------------------------------
    // Check Admin Access Permission
    //---------------------------------------------

    bool CheckAccessPermission(enPermissions Permission)
    {
        // Check Access Permission process:
        // 1. This function is called using a Admin object NAMED(the current object or an admin object).
        // 2. It receives a permission value (or enum) representing the specific permission
        //    that the Admin wants to check and get.
        // 3. First, it checks if the Admin's permissions equal enPermissions::eAll (-1),
        //    which means the Admin has full access. If so, it returns true.
        // 4. If not, it performs a bitwise AND between the Admin's permissions
        //    (this->GetPermissions()) and the requested permission.
        //    - If the result equals the requested permission, it means the Admin has
        //      that specific permission, so it returns true.
        // 5. If neither condition is met, the function returns false,
        //    indicating the Admin does not have the requested permission.

        if (this->GetPermissions() == enPermissions::eAll)
            return true;

        if ((Permission & this->GetPermissions()) == Permission)
            return true;
        else
            return false;
    }

    //---------------------------------------------
    // Add process To File
    //---------------------------------------------
    static void AddTransactionToFile(string AdminUserName, double amount, string fromAccount, double fromBalance, string toAccount, double toBalance)
    {
        fstream MyFile("../data/Transactions.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            // date & time
            string Date = clsDate::DateToString(clsDate::GetSystemDate());
            // get accurate time
            string TimeBuffer = clsDate::GetAccurateTime();
            string sperator = " || ";
            // Write transaction entry
            MyFile << Date << " || "
                   << TimeBuffer << " || "
                   << AdminUserName << " || "
                   << amount << " || "
                   << fromAccount << " || "
                   << fromBalance << " || "
                   << toAccount << " || "
                   << toBalance
                   << endl;

            MyFile.close();
        }
        else
        {
            cerr << "Error: Cannot open Transactions.txt to write transaction entry.\n";
        }
    }

    // Helper: Get last LOGIN time for a user
    static string _GetLastLoginTime(string Username)
    {
        vector<string> vSessions;
        fstream MyFile("../data/AdminsSessionLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vector<string> vData = clsString::Split(Line, "#//#");
                if (vData.size() >= 4 && vData[3] == Username && vData[2] == "LOGIN")
                {
                    vSessions.push_back(vData[0] + " " + vData[1]); // Date + Time
                }
            }
            MyFile.close();
        }

        if (vSessions.size() > 0)
            return vSessions[vSessions.size() - 1];

        return "";
    }
    // Register Admin Session (LOGIN or LOGOUT)
    static void RegisterAdminSession(const clsAdmin &Admin, string SessionType)
    {
        fstream MyFile("../data/AdminsSessionLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            string Date = clsDate::DateToString(clsDate::GetSystemDate());
            string Time = clsDate::GetAccurateTime();

            string Duration = "-";

            if (SessionType == "LOGOUT")
            {
                string LastLoginTime = _GetLastLoginTime(Admin.GetAdminUsername());
                if (LastLoginTime != "")
                {
                    Duration = _CalculateDuration(LastLoginTime, Date + " " + Time);
                }
            }

            MyFile << Date << "#//#"
                   << Time << "#//#"
                   << SessionType << "#//#"
                   << Admin.GetAdminUsername() << "#//#"
                   << Admin.GetFirstName() + " " + Admin.GetLastName() << "#//#"
                   << Admin.GetPermissions() << "#//#"
                   << Duration
                   << endl;

            MyFile.close();
        }
    }

    // Get all admin sessions
    static vector<string> GetAdminSessionLog()
    {
        vector<string> vSessions;
        fstream MyFile("../data/AdminsSessionLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vSessions.push_back(Line);
            }
            MyFile.close();
        }

        return vSessions;
    }

    // Get sessions for specific admin
    static vector<string> GetAdminSessionLog(string Username)
    {
        vector<string> vSessions;
        fstream MyFile("../data/AdminsSessionLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vector<string> vData = clsString::Split(Line, "#//#");

                if (vData.size() >= 4 && vData[3] == Username)
                {
                    vSessions.push_back(Line);
                }
            }
            MyFile.close();
        }

        return vSessions;
    }
    // Helper: Calculate duration between login and logout
    static string _CalculateDuration(string LoginDateTime, string LogoutDateTime)
    {
        // Parse DateTime format: "25/11/2025 01:30:45 PM"
        vector<string> vLoginParts = clsString::Split(LoginDateTime, " ");
        vector<string> vLogoutParts = clsString::Split(LogoutDateTime, " ");

        if (vLoginParts.size() < 2 || vLogoutParts.size() < 2)
            return "Unknown";

        // Parse dates
        clsDate LoginDate(vLoginParts[0]);
        clsDate LogoutDate(vLogoutParts[0]);

        // Parse times (format: "01:30:45")
        vector<string> vLoginTime = clsString::Split(vLoginParts[1], ":");
        vector<string> vLogoutTime = clsString::Split(vLogoutParts[1], ":");

        if (vLoginTime.size() < 3 || vLogoutTime.size() < 3)
            return "Unknown";

        // Convert to 24-hour format if PM
        int LoginHour = stoi(vLoginTime[0]);
        int LogoutHour = stoi(vLogoutTime[0]);

        if (vLoginParts.size() > 2 && vLoginParts[2] == "PM" && LoginHour != 12)
            LoginHour += 12;
        if (vLoginParts.size() > 2 && vLoginParts[2] == "AM" && LoginHour == 12)
            LoginHour = 0;

        if (vLogoutParts.size() > 2 && vLogoutParts[2] == "PM" && LogoutHour != 12)
            LogoutHour += 12;
        if (vLogoutParts.size() > 2 && vLogoutParts[2] == "AM" && LogoutHour == 12)
            LogoutHour = 0;

        int LoginMinute = stoi(vLoginTime[1]);
        int LogoutMinute = stoi(vLogoutTime[1]);

        // Calculate total minutes
        int DaysDiff = clsDate::GetDifferenceInDays(LoginDate, LogoutDate, false);
        int TotalMinutes = DaysDiff * 24 * 60;

        TotalMinutes += (LogoutHour - LoginHour) * 60;
        TotalMinutes += (LogoutMinute - LoginMinute);

        // Format output
        if (TotalMinutes < 0)
            return "Invalid";

        if (TotalMinutes < 60)
            return to_string(TotalMinutes) + " mins";

        int Hours = TotalMinutes / 60;
        int Minutes = TotalMinutes % 60;

        if (Hours < 24)
        {
            if (Minutes == 0)
                return to_string(Hours) + " hrs";
            else
                return to_string(Hours) + " hrs " + to_string(Minutes) + " mins";
        }

        int Days = Hours / 24;
        Hours = Hours % 24;

        if (Hours == 0 && Minutes == 0)
            return to_string(Days) + " days";
        else if (Hours == 0)
            return to_string(Days) + " days " + to_string(Minutes) + " mins";
        else if (Minutes == 0)
            return to_string(Days) + " days " + to_string(Hours) + " hrs";
        else
            return to_string(Days) + " days " + to_string(Hours) + " hrs " + to_string(Minutes) + " mins";
    }
};