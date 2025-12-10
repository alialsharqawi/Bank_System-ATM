/*clsBankClient Overview
================================================================================
                               clsBankClient.h
================================================================================
Overview:
---------
This file defines the clsBankClient class, which represents a complete bank
client entity in the project. It inherits all personal information from
clsPerson (FirstName, LastName, Email, Phone) and adds banking-related data
and operations such as:

- Account Number
- PIN Code
- Account Balance
- Save, Update, Add, and Delete Operations
- Withdraw and Deposit
- Loading and Storing all clients in the database file

The class handles all file persistence internally using a clean separation
between public behaviour and private helper functions.

================================================================================
Class Purpose:
--------------
clsBankClient serves as the main data model for bank clients in the Banking
Management System. It is designed to:

● Represent a single client
● Read/write client data to the file
● Allow searching, adding, updating, deleting
● Perform financial operations
● Provide formatted printing for UI screens

It also uses inheritance to avoid duplicating personal fields.

================================================================================
Key Concepts Implemented:
-------------------------

1. **Inheritance (clsPerson → clsBankClient)**
   - Reuses personal data: name, email, phone
   - Reduces code duplication
   - Enables polymorphic behaviour if needed later

2. **Encapsulation**
   - Client properties are private
   - Access via getters/setters
   - File operations are hidden inside private static functions

3. **Data Persistence (File I/O)**
   - Clients stored in "Clients.txt"
   - Loading and saving done via serialization/deserialization:
        - _ConvertLinetoClientObject()
        - _ConverClientObjectToLine()

4. **Object Modes (enMode)**
   - EmptyMode   → object has no data
   - UpdateMode  → modify existing record
   - AddNewMode  → adding a new client

   Mode allows Save() to decide the correct behaviour.

5. **Validation & Utility Functions**
   - Find() to search clients
   - IsClientExist() to check duplication
   - IsEmpty() to detect empty objects
   - GetClientsList() to list all clients
   - GetTotalBalances() to calculate total money in bank

6. **Financial Operations**
   - Deposit()
   - Withdraw()
   - Auto-saving after each transaction

================================================================================
File Storage Format:
--------------------
Each client is stored in a single line using the separator `" || "`:

    FirstName || LastName || Email || Phone || AccountNumber || EncryptedPin || Balance

Internal functions handle converting between text lines and clsBankClient objects.

================================================================================
Main Responsibilities:
----------------------

● Provide full CRUD (Create / Read / Update / Delete) for clients
● Guarantee file data consistency
● Handle input validation such as duplicated account numbers
● Perform secure operations (PIN encryption/decryption)
● Provide reusable utilities for the rest of the system

================================================================================
Important Internal Methods:
---------------------------

- _ConvertLinetoClientObject()
    Converts a file line into a client object.

- _ConverClientObjectToLine()
    Serializes a client object into a text line.

- _LoadClientsDataFromFile() / _SaveCleintsDataToFile()
    Load and save the entire client database.

- _AddNew(), _Update()
    Handle object persistence depending on mode.

- _AddDataLineToFile()
    Appends new clients to the file.

================================================================================
Public Interface Summary:
-------------------------

● **Find()** – search by account number (with/without PIN)
● **Save()** – add or update a client
● **Delete()** – remove a client from storage
● **GetClientsList()** – return all clients
● **GetTotalBalances()** – sum all balances
● **Deposit() / Withdraw()** – financial transactions
● **Print() / PrintShortClientCard()** – formatted output

================================================================================
Usage Example:
--------------

    clsBankClient Client = clsBankClient::Find("A1022");

    if (!Client.IsEmpty()) {
        Client.Withdraw(500);
        Client.Deposit(200);
        Client.Save();
        Client.Print();
    }

================================================================================
Design Notes:
-------------

- The class hides all low-level file logic to keep UI code clean.
- Object mode ensures correct behaviour when saving.
- Sensitive data (PIN) is encrypted using clsUtil.
- All file operations rewrite the full file to maintain consistency.
- Methods are carefully divided into static and non-static
  depending on whether they belong to the object or the database.

================================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"          // core/clsPerson.h
#include "../utils/clsString.h" // utils/clsString.h
#include "../utils/clsUtil.h"   // utils/clsUtil.h

using namespace std;

class clsBankClient : public clsPerson

// clsBankClient inherits everything from clsPerson:
// - Private properties: FirstName, LastName, Email, Phone
// - Public methods: getters, setters
// - Constructor initializes the inherited properties
// Additional methods in clsBankClient:
// - GetFullName(): returns the full name
// - PrintClientData(): prints all client details

{
private:
    // Why we use this mode enum:
    // - To identify the type of operation to perform on the object.
    // - This helps when saving data to a file, to know what action to take.
    //   - UpdateMode: update existing data in the file.
    //   - EmptyMode: the object is empty, no data.
    //   - AddNewMode: add new data to the file.

    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = " || ")
    {
        // Converts a line from the file into a clsBankClient object and returns it.
        // - Static: can be called without creating a clsBankClient object.
        // - Private: not accessible directly from outside the class.
        // How it works:
        // 1. Reserve a vector of strings to store the split data from the line.
        // 2. Use clsString::Split to divide the line by the given separator.
        // 3. Store the resulting vector of strings in vClientData.
        // 4. Return a clsBankClient object initialized with:
        //    - UpdateMode (because this line comes from an existing file, not new input)
        //    - The split data from the line
        //    - Decrypted password

        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                             vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stod(vClientData[6]));
    }

    static string _ConverClientObjectToLine(const clsBankClient &Client, string Seperator = " || ")
    {
        // Converts a clsBankClient object into a single line string for file storage.
        // - Static: can be called without creating a clsBankClient object.
        // - Private: not accessible from outside the class.
        // How it works:
        // 1. Prepare an empty string to store client data as a line.
        // 2. Append the object's data to the string using getters.
        //    - Getters for first name, last name, email, phone are inherited from clsPerson.
        // 3. Insert the specified separator between each data field.
        // 4. Encrypt sensitive data like the account number before adding it.
        // 5. Convert numeric values (like account balance) to string.
        // 6. Return the final string that represents the client record for the file.

        string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.GetAccountNumber() + Seperator;
        stClientRecord += clsUtil::EncryptText(Client.GetPinCode()) + Seperator;
        stClientRecord += to_string(Client.GetAccountBalance());

        return stClientRecord;
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        // Loads all bank clients from the file into a vector.
        // - Static: can be called without creating a clsBankClient object.
        // - Private: not accessible from outside the class.
        // How it works:
        // 1. Prepare an empty vector of clsBankClient to store the client objects.
        // 2. Open "Clients.txt" in read mode.
        // 3. If the file opens successfully:
        //    a. Read each line of the file using getline.
        //    b. Convert each line into a clsBankClient object using _ConvertLinetoClientObject().
        //    c. Append the client object to the vector.
        // 4. Close the file after reading all lines.
        // 5. Return the vector containing all client objects loaded from the file.
        vector<clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    static void _SaveCleintsDataToFile(const vector<clsBankClient> &vClients)
    {
        // Saves all client records to the data file.
        // This function rewrites the entire file with the updated list of clients.
        // - Accepts a vector of clsBankClient objects (by const reference for efficiency).
        // - Skips any client marked for deletion.
        // - Converts each client object into a formatted line before writing.
        // The method is static and private because it serves as an internal
        // helper for data persistence and is not intended to be accessed externally.
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::out); // overwrite Mode

        string DataLine;

        if (MyFile.is_open())
        {
            for (const clsBankClient &C : vClients)
            {
                if (C._MarkedForDelete == false) // if true skip mean you have been delete this line
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        // Updates the current client's record in the data file.
        // This is a non-static, private method because it modifies the object
        // that invoked it and should not be accessed externally.
        //
        // Workflow:
        // - Load all clients from the file into a vector.
        // - Search for the client whose AccountNumber matches the current object.
        // - Replace that record with the current object's data.
        // - Save the updated list back to the file.
        //
        // Used only when the object is operating in UpdateMode.
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : _vClients)
        {
            if (C.GetAccountNumber() == this->GetAccountNumber())
            {
                C = *this; // overwrite the matching record
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);
    }

    void _AddNew()
    {
        // Add New client process from the Add New client screen:
        // 1. In the Add New client screen, create a new client object containing the data Entered by the user.
        // 2. Call the _AddNew() method using this new client object.
        // 3. Inside _AddNew(), the current object (*this) represents the client to be added.
        // 4. _ConverClientObjectToLine(*this) converts this client object into a single line of text
        //    suitable for storage in the data file.
        // 5. _AddDataLineToFile(...) takes that text line and appends it to the end of the client file,
        //    effectively saving the new client's data persistently.
        // 6. After this method finishes execution, the new client is stored in the file
        //    and can later be loaded back into memory when needed.
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        // Adds a new client record to the file.
        // - Non-static: operates on the object that called it.
        // - Private: not accessible from outside the class.
        // How it works:
        // 1. Receives a string representing the client record to be added.
        // 2. Opens "Clients.txt" in append mode to add the record at the end of the file.
        // 3. Checks if the file is open.
        // 4. Writes the string to the file.
        // 5. Closes the file after writing.
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static clsBankClient _GetEmptyClientObject()
    {
        // Returns an empty clsBankClient object with mode set to EmptyMode.
        // - Static: can be called without creating a clsBankClient instance.
        // - Private: not accessible from outside the class.
        // How it works:
        // 1. Creates a clsBankClient object with default/empty values for all fields.
        // 2. Sets its mode to EmptyMode to indicate it has no valid data.
        // 3. Returns this empty object.
        // Usage:
        // - Used when no client exists in the file with the provided account number.
        // - Typically called by the Find function when the search yields no result.
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    clsBankClient() {} // defualt Constructor
    /**
     * @brief Constructor for clsBankClient class.
     *
     * - Initializes a clsBankClient object with provided data.
     * - Calls the base class (clsPerson) constructor to initialize inherited attributes:
     *   FirstName, LastName, Email, and Phone.
     * - Sets the client's specific attributes: AccountNumber, PinCode, AccountBalance, and Mode.
     * Usage:
     * - Use the parameterized constructor to create a fully initialized client object.
     * - Use the default constructor to create an empty object for later initialization.
     */
    clsBankClient(enMode Mode, string FirstName, string LastName,
                  string Email, string Phone, string AccountNumber, string PinCode,
                  float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    //---------------------------------------------
    // Getters and Setters
    //---------------------------------------------
    string GetAccountNumber() const { return _AccountNumber; }
    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode() const { return _PinCode; }
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance() const { return _AccountBalance; }

    //---------------------------------------------
    // Print Client Info
    //---------------------------------------------
    void Print()
    {
        // Print Info
        // - Non-static: operates on the object that calls it
        // named after "Print" to hidden print in base class(person)
        // - Public: accessible from outside the class
        // - Used to print all client information
        // - Extends the Print method from the base class (clsPerson)
        //   by including client-specific data: AccountNumber, PinCode, AccountBalance
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << GetFirstName();  // inherited getter from clsPerson
        cout << "\nLastName    : " << GetLastName();   // inherited getter from clsPerson
        cout << "\nFull Name   : " << FullName();      // inherited method from clsPerson
        cout << "\nEmail       : " << GetEmail();      // inherited getter from clsPerson
        cout << "\nPhone       : " << GetPhone();      // inherited getter from clsPerson
        cout << "\nAcc. Number : " << _AccountNumber;  // private attribute in clsBankClient
        cout << "\nPassword    : " << _PinCode;        // private attribute in clsBankClient
        cout << "\nBalance     : " << _AccountBalance; // private attribute in clsBankClient
        cout << "\n___________________\n";
    }
    void PrintShortClientCard()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nAccount Number: " << GetAccountNumber();
        cout << "\nFull Name     : " << FullName();
        cout << "\nBalance       : " << GetAccountBalance();
        cout << "\n___________________\n";
    }
    //---------------------------------------------
    // Find Clients
    //---------------------------------------------
    static clsBankClient Find(string AccountNumber)
    {
        // Find Client by Account Number
        // - Static: can be called without creating a clsBankClient object
        // - Public: accessible from outside the class
        // - Purpose: searches for a client in the file by the given account number
        // - Returns:
        //     * clsBankClient object with data if a matching account is found
        //     * Empty clsBankClient object if no match is found
        // How it works:
        // 1. Open the "Clients.txt" file in read mode.
        // 2. If the file is successfully opened:
        //    a. Prepare an empty string to read each line.
        //    b. Use a while loop with getline to read each line from the file.
        //    c. Convert the line into a clsBankClient object using _ConvertLinetoClientObject.
        //    d. Compare the object's account number with the given account number.
        //    e. If a match is found, close the file and return the client object.
        // 3. If the file cannot be opened or no client is found, return an empty client
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.GetAccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        // Overloaded Find method:
        // - Static method, accessible without creating a clsBankClient object.
        // - Public: can be called from outside the class.
        // - Used for client login authentication.
        // - Searches for a client record in the file by account number and PIN code.
        // - Returns the corresponding clsBankClient object if found,
        //   otherwise returns an empty client object.
        fstream MyFile;
        MyFile.open("../data/Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    //---------------------------------------------
    // Save Client
    //---------------------------------------------
    enum enSaveResults
    {
        // Enumeration to represent the results of saving a client record.
        // - Public: accessible from outside the class.
        // - Static-like usage: can be used without instantiating the class (as it's an enum).
        // Values:
        //   svFaildEmptyObject         : Save operation failed because the client object is empty.
        //   svSucceeded                : Save operation succeeded successfully.
        //   svFaildAccountNumberExists : Save operation failed because the account number already exists.
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExists = 2
    };

    enSaveResults Save()
    {
        // Save process steps:
        // 1. Determine the current object mode (_Mode) to identify the required operation.
        // 2. If the mode is EmptyMode:
        //      - Check if the object contains valid data.
        //      - If the object is empty, return a failed save result.
        // 3. If the mode is UpdateMode:
        //      - Call _Update() to overwrite the existing record in the storage.
        //      - Return a successful save result.
        // 4. If the mode is AddNewMode:
        //      - Check whether a client with the same AccountNumber already exists.
        //      - If it exists, return a failure indicating duplicated account number.
        //      - Otherwise, call _AddNew() to write a new record.
        //      - After adding, set the mode to UpdateMode for future modifications.
        //      - Return a successful save result.
        // 5. If none of the above modes match:
        //      - Treat it as an invalid state and return a failed save result.
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;
            }
        }
        case enMode::UpdateMode:
        {

            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                // We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        default:
        {
            return enSaveResults::svFaildEmptyObject;
        }
        }
    }
    //---------------------------------------------
    // Utilities
    //---------------------------------------------
    static bool IsClientExist(string AccountNumber)
    {
        // IsClientExist process steps:
        // 1. This function is declared static so it can be used without creating an object of the class.
        // 2. It is public so it can be accessed from outside the class.
        // 3. The function receives an AccountNumber (string) to search for.
        // 4. Call the Find() function to retrieve a client with the given AccountNumber.
        // 5. Store the returned object in a temporary clsBankClient variable.
        // 6. If Find() returns an empty object:
        //      - This means no client exists with the given AccountNumber.
        //      - Return false.
        // 7. If Find() returns a non-empty object:
        //      - This means the client exists.
        //      - Return true.
        // 8. This is where the IsEmpty() function plays its role in identifying empty objects.
        //----------------------------------------------------------------------------------
        // Allocate a temporary client object to store the result of Find().
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }

    bool IsEmpty()
    {
        // IsEmpty process steps:
        // 1. This function checks whether the current object is considered empty.
        // 2. It is used by the Find() function when no client matches the requested AccountNumber.
        // 3. It is also used in the Save() function when the mode is EmptyMode to prevent saving invalid objects.
        // 4. The function is public so it can be accessed from outside the class.
        // 5. It is not static because it operates on the specific object instance.
        // 6. The function returns true if the object's mode is set to EmptyMode; otherwise, it returns false.
        return (_Mode == enMode::EmptyMode);
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        // GetAddNewClientObject process steps:
        // 1. This function creates and returns a new clsBankClient object prepared for adding a new client.
        // 2. It is declared static so it can be called without creating an instance of the class.
        // 3. The function takes an AccountNumber, which will be assigned to the new client.
        // 4. The constructor is called with AddNewMode to indicate that this object represents a new client record.
        // 5. The rest of the fields are initialized with empty values until filled later by the user.
        // 6. The returned object can be used directly in screens that handle adding new clients.

        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
    //---------------------------------------------
    // Delete Client
    //---------------------------------------------
    bool Delete()
    {
        // Delete process steps:
        // 1. This function is non-static, meaning it must be called through an existing object instance.
        // 2. Create a vector of clsBankClient to hold all client records.
        // 3. Call _LoadClientsDataFromFile() to load all clients from the storage into the vector.
        // 4. Iterate through the vector using a ranged-for loop (by reference).
        // 5. For each client in the vector:
        //      - Check if its AccountNumber matches the AccountNumber of the current object (*this).
        //      - If a match is found, set the client's _MarkedForDelete flag to true.
        //      - Break the loop since the target client has been located.
        // 6. Call _SaveClientsDataToFile() to write the updated list back to the file.
        //      - Only clients NOT marked for deletion will be saved.
        // 7. Replace the current object (*this) with an empty client object by calling _GetEmptyClientObject().
        // 8. Return true to indicate that the deletion process completed successfully.

        vector<clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : _vClients)
        {
            if (C.GetAccountNumber() == this->_AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }
    //---------------------------------------------
    // List and Balance
    //---------------------------------------------
    static vector<clsBankClient> GetClientsList()
    {
        // GetClientsList process steps:
        // 1. This function is declared static, so it can be called without creating an object of the class.
        // 2. The function retrieves all clients stored in the file.
        // 3. It calls _LoadClientsDataFromFile(), which reads the file and returns a vector of clsBankClient.
        // 4. The function returns that vector as the complete list of clients.

        return _LoadClientsDataFromFile();
    }
    //---------------------------------------------
    // Financial Operations
    //---------------------------------------------
    static double GetTotalBalances()
    {
        // GetTotalBalances process steps:
        // 1. Declare a vector to hold all clients.
        // 2. Call GetClientsList() to retrieve all client records.
        // 3. Create a variable to accumulate the total balances.
        // 4. Loop through each client in the vector (by value).
        // 5. For each client, retrieve its balance using GetAccountBalance().
        // 6. Add the balance to the total accumulator.
        // 7. After completing the loop, return the total balance of all clients.
        // 8. This function is static because the calculation does not depend on any specific object.

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;
        for (clsBankClient &Client : vClients)
        {
            TotalBalances += Client.GetAccountBalance();
        }
        return TotalBalances;
    }

    void Deposit(double Amount)
    {
        // Deposit process steps:
        // 1. Increase the account balance by the deposit amount.
        // 2. Call Save() to update the client's record in the storage.
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        // Withdraw process steps:
        // 1. Check if the current balance is sufficient for the withdrawal.
        // 2. If the balance is less than the requested amount:
        //      - Return false to indicate the withdrawal failed.
        // 3. Otherwise:
        //      - Deduct the withdrawal amount from the balance.
        //      - Call Save() to persist the updated balance.
        //      - Return true to indicate a successful withdrawal.
        if (_AccountBalance < Amount)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }
    
    //////////////////////////////////////////////
    // Helper: Get last LOGIN time for a client
    //////////////////////////////////////////////
    
    static string _GetLastLoginTime(string AccountNumber)
    {
        vector<string> vSessions;
        fstream MyFile("../data/ClientsSessionLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vector<string> vData = clsString::Split(Line, "#//#");
                if (vData.size() >= 4 && vData[3] == AccountNumber && vData[2] == "LOGIN")
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
    
    //////////////////////////////////////////////
    // Register Client Session (LOGIN or LOGOUT)
    //////////////////////////////////////////////
    
    static void RegisterClientSession(const clsBankClient &Client, string SessionType)
    {
        fstream MyFile("../data/ClientsSessionLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            string Date = clsDate::DateToString(clsDate::GetSystemDate());
            string Time = clsDate::GetAccurateTime();

            string Duration = "-";

            if (SessionType == "LOGOUT")
            {
                string LastLoginTime = _GetLastLoginTime(Client.GetAccountNumber());
                if (LastLoginTime != "")
                {
                    Duration = _CalculateDuration(LastLoginTime, Date + " " + Time);
                }
            }

            MyFile << Date << "#//#"
                   << Time << "#//#"
                   << SessionType << "#//#"
                   << Client.GetAccountNumber() << "#//#"
                   << Client.FullName() << "#//#"
                   << Duration
                   << endl;

            MyFile.close();
        }
    }
    
    //////////////////////////////////////////////
    // Get all client sessions
    //////////////////////////////////////////////
    
    static vector<string> GetClientSessionLog()
    {
        vector<string> vSessions;
        fstream MyFile("../data/ClientsSessionLog.txt", ios::in);

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
    
    //////////////////////////////////////////////
    // Get sessions for specific client
    //////////////////////////////////////////////
    
    static vector<string> GetClientSessionLog(string AccountNumber)
    {
        vector<string> vSessions;
        fstream MyFile("../data/ClientsSessionLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vector<string> vData = clsString::Split(Line, "#//#");

                if (vData.size() >= 4 && vData[3] == AccountNumber)
                {
                    vSessions.push_back(Line);
                }
            }
            MyFile.close();
        }

        return vSessions;
    }
    
    //////////////////////////////////////////////
    // Helper: Calculate duration between login and logout
    //////////////////////////////////////////////
    
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