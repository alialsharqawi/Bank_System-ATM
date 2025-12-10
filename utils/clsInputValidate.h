/*clsInputValidate Overview
================================================================================
								  clsInputValidate.h
================================================================================
Overview:
---------
clsInputValidate is a utility class designed to validate and safely read user
input from the console. It provides methods for numbers, floating-point numbers,
dates, strings, Emails, phone numbers, and yes/no options.

================================================================================
Public Methods:
---------------

1. Number Validation:
	static bool IsNumberBetween(short Number, short From, short To)
	static bool IsNumberBetween(int Number, int From, int To)
	static bool IsNumberBetween(double Number, double From, double To)

2. Date Validation:
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	static bool IsValideDate(clsDate Date)

3. Read Numbers:
	static int ReadIntNumber(const string& ErrorMessage = "Invalid Number, Enter again\n", int Min = INT_MIN, int Max = INT_MAX)
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n", double Min = -DBL_MAX, double Max = DBL_MAX)
	static double ReadFloatNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n", double Min = -DBL_MAX, double Max = DBL_MAX)
	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	static double ReadPositiveDouble();
4. String Validation:
	static string ReadString(string ErrorMessage = "Invalid input, Enter again\n", size_t MaxLength = 1000)

5. Email Validation:
	static bool IsValidEmail(const string& Email)
	static string ReadEmail(string ErrorMessage = "Invalid Email, Please Enter again:\n")

6. Phone Validation:
	static bool IsValidPhone(const string& phone)
	static string ReadPhone(string ErrorMessage = "Invalid phone number, Please Enter again:\n")

7. Yes/No Input:
	static char ReadYesOrNo(string ErrorMessage = "Invalid choice, Please Enter again (y/n): ")

================================================================================
Usage Examples:
---------------

	int age = clsInputValidate::ReadIntNumberBetween(18, 60);
	double salary = clsInputValidate::ReadFloatNumberBetween(1000.0, 10000.0);

	string name = clsInputValidate::ReadString("Please Enter a valid name:\n", 50);
	string Email = clsInputValidate::ReadEmail();
	string phone = clsInputValidate::ReadPhone();

	clsDate birthDate;
	do {
		birthDate = clsInputValidate::ReadDate();
	} while (!clsInputValidate::IsValideDate(birthDate));

	char choice = clsInputValidate::ReadYesOrNo();

================================================================================
Notes:
------
- The class uses regex to validate Emails and phone numbers.
- All Read* methods loop until a valid input is received.
- Automatically trims spaces from input when necessary.
- Prevents buffer overflow by limiting string input length.

================================================================================
End of Documentation
================================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cfloat>
#include <algorithm>
#include <sstream>
#include <regex>

#include "clsString.h"  // utils/clsString.h
#include "clsDate.h"    // utils/clsDate.h

class clsInputValidate
{

public:
	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		// Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)) &&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
		{
			return true;
		}

		// Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)) &&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)))
		{
			return true;
		}

		return false;
	}

	static int ReadIntNumber(const string &ErrorMessage = "\nInvalid Number, Enter again.\n", int Min = INT_MIN, int Max = INT_MAX)
	{
		string input;
		int number;

		while (true)
		{
			getline(cin, input);
			stringstream ss(input);

			if (ss >> number)
			{
				char leftover;
				if (ss >> leftover)
				{
					
					cout << ErrorMessage;
					continue;
				}

				
				if (number < Min || number > Max)
				{
					cout << "Number out of range! (" << Min << " - " << Max << ")\n";
					continue;
				}

				return number;
			}
			else
			{
				cout << ErrorMessage;
			}
		}
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadFloatNumber(string ErrorMessage = "\nInvalid Number, Enter again\n", double Min = std::numeric_limits<double>::lowest(), double Max = std::numeric_limits<double>::max())
	{
		string input;
		double number;

		while (true)
		{
			getline(cin, input);
			stringstream ss(input);

			if (ss >> number)
			{
				char leftover;
				if (ss >> leftover)
				{
				
					cout << ErrorMessage;
					continue;
				}

				
				if (number < Min || number > Max)
				{
					cout << "Number out of range! (" << Min << " - " << Max << ")\n";
					continue;
				}

				return number;
			}
			else
			{
				cout << ErrorMessage;
			}
		}
	}

	static double ReadFloatNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "\nInvalid Number, Enter again\n", double Min = std::numeric_limits<double>::lowest(), double Max = std::numeric_limits<double>::max())
	{
		string input;
		double number;

		while (true)
		{
			getline(cin, input);
			stringstream ss(input);

			if (ss >> number)
			{
				char leftover;
				if (ss >> leftover)
				{
					cout << ErrorMessage;
					continue;
				}
				if (number < Min || number > Max)
				{
					cout << "Number out of range! (" << Min << " - " << Max << ")\n";
					continue;
				}

				return number;
			}
			else
			{
				cout << ErrorMessage;
			}
		}
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}
	
	static double ReadPositiveDouble(const string& ErrorMessage = "Invalid! Enter a positive number: ")
	{
	    double number;

	    while (true)
	    {
	        number = ReadDblNumber();

	        if (number > 0)
	            return number;

	        cout << ErrorMessage;
	    }
	}

	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString(string ErrorMessage = "\nInvalid input, Enter again\n", size_t MaxLength = 1000)
	{
		string input;

		while (true)
		{
			getline(cin >> ws, input); 

			if (input.empty())
			{
				cout << ErrorMessage; 
				continue;
			}

			if (input.length() > MaxLength)
			{
				cout << "Input too long! Maximum length is " << MaxLength << " characters.\n";
				continue;
			}

			return input; 
		}
	}

	static bool IsValidEmail(const string &Email)
	{
		const regex pattern(R"(^[A-Za-z0-9._%+-]+@([A-Za-z0-9-]+\.)+[A-Za-z]{2,}$)");
		return regex_match(Email, pattern);
	}

	static string ReadEmail(string ErrorMessage = "\nInvalid Email, Please Enter again:\n")
	{
		string Email = ReadString();

		while (!IsValidEmail(Email))
		{
			cout << ErrorMessage;
			Email = ReadString();
		}
		return Email;
	}

	static bool IsValidPhone(const string &phone)
	{
		string trimmed = phone;
		trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
		trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);

		const regex pattern(R"(^\+?\d{10,15}$)");
		return regex_match(trimmed, pattern);
	}

	static string ReadPhone(string ErrorMessage = "\nInvalid phone number, Please Enter again:\n")
	{
		string phone = ReadString();

		while (!IsValidPhone(phone))
		{
			cout << ErrorMessage;
			phone = ReadString();
		}
		return phone;
	}

	static char ReadYesOrNo(string ErrorMessage = "\nInvalid choice, Please Enter again (y/n): ")
	{
		string input;

		while (true)
		{
			getline(cin >> ws, input); 

			
			input.erase(0, input.find_first_not_of(" \t\n\r"));
			input.erase(input.find_last_not_of(" \t\n\r") + 1);

			
			for (auto &c : input)
				c = tolower(c);

			if (input == "y" || input == "yes")
				return 'y';
			else if (input == "n" || input == "no")
				return 'n';
			else
				cout << ErrorMessage;
		}
	}
};
