/*clsPerson Overview
================================================================================
                                   clsPerson.h
================================================================================
Overview:
---------
This file defines the clsPerson class, which serves as a basic data model for
representing a person's information. It is primarily used as a parent class
(base class) for other classes such as clsUser and clsBankClient.

The class stores essential personal information:
- First name
- Last name
- Email address
- Phone number

It also provides basic utilities such as:
- Reading and updating person details
- Printing full formatted information
- Obtaining the full name

================================================================================
Purpose of the Class:
---------------------
clsPerson is designed to be a simple, reusable, and extendable foundation for
any object that needs personal details. It allows derived classes to inherit
these attributes without rewriting the same code.

Examples of derived classes:
- clsUser  (inherits login details + permissions)
- clsBankClient  (inherits account details + balance)

================================================================================
Main Features:
--------------

● Constructor Overloading
   - A parameterized constructor initializes all fields.
   - A default constructor allows creating an empty person object.

● Setters
   Methods that safely update private attributes:
   - SetFirstName()
   - SetLastName()
   - SetEmail()
   - SetPhone()

● Getters
   All getters are marked `const` to ensure they do not modify object state:
   - GetFirstName()
   - GetLastName()
   - GetEmail()
   - GetPhone()

● FullName()
   Concatenates first and last names into a single string.

● Print()
   Outputs a formatted summary of all personal information.

================================================================================
Design Notes:
-------------
- All attributes are private to ensure proper encapsulation.
- Derived classes depend on clsPerson for common human attributes.
- The FullName() method simplifies display logic across the system.
- Print() is meant for debugging and display screens, not file storage.

================================================================================
Usage Summary:
--------------
Typical usage in derived classes:

    class clsUser : public clsPerson
    {
        // inherits first name, last name, email, phone
        // adds username, password, permissions
    };

    class clsBankClient : public clsPerson
    {
        // inherits basic personal info
        // adds account number, balance, transactions
    };

================================================================================
*/

#pragma once

#include <iostream>

#include <string>
using namespace std;

class clsPerson
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
    // Constructor set private attributes
    clsPerson(string FirstName, string LastName, string Email, string Phone)
        : _FirstName(FirstName), _LastName(LastName), _Email(Email), _Phone(Phone) {}

    clsPerson() {}

    // Setters
    void SetFirstName(string FirstName) { _FirstName = FirstName; }
    void SetLastName(string LastName) { _LastName = LastName; }
    void SetEmail(string Email) { _Email = Email; }
    void SetPhone(string Phone) { _Phone = Phone; }

    // Getters (const because they don't modify the object)
    string GetFirstName() const { return _FirstName; }
    string GetLastName() const { return _LastName; }
    string GetEmail() const { return _Email; }
    string GetPhone() const { return _Phone; }

    // Full Name
    string FullName() const { return _FirstName + " " + _LastName; }

    // Print Info
    void Print() const
    {
        cout << "\nPERSON Info:";
        cout << "\n___________________";
        cout << "\nFirstName: " << _FirstName;
        cout << "\nLastName : " << _LastName;
        cout << "\nFull Name: " << FullName();
        cout << "\nEmail    : " << _Email;
        cout << "\nPhone    : " << _Phone;
        cout << "\n___________________\n";
    }
};
