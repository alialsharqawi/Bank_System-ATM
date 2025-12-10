/*clsUtil Overview
================================================================================
                                    clsUtil.h
================================================================================
Overview:
---------
A “utils” class is a collection of helper methods or functions designed to handle common,
often low-level tasks that are reusable across different parts of an application

This file defines the clsUtil class — a utility class containing a set of
general-purpose static methods for random generation, swapping, shuffling,
string encryption/decryption, and number-to-text conversion.

================================================================================
Class Responsibilities:
-----------------------
1. Generate random numbers, characters, words, and keys.
2. Fill arrays with random numbers, words, or keys.
3. Swap values of primitive types and clsDate objects.
4. Shuffle arrays of numbers or strings.
5. Provide formatting helpers like Tabs.
6. Convert numbers to their English textual representation.
7. Encrypt and decrypt strings using a simple Caesar cipher.

================================================================================
Public Methods:
---------------
- Random Generators:
    static void Srand()                         // Seed the random number generator
    static int RandomNumber(int From, int To)   // Generate random number in range
    static char GetRandomCharacter(enCharType CharType)
    static string GenerateWord(enCharType CharType, short Length)
    static string GenerateKey(enCharType CharType = CapitalLetter)
    static void GenerateKeys(short NumberOfKeys, enCharType CharType)

- Array Utilities:
    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short WordLength)
    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    static void ShuffleArray(int arr[100], int arrLength)
    static void ShuffleArray(string arr[100], int arrLength)

- Swap Functions:
    static void Swap(int& A, int& B)
    static void Swap(double& A, double& B)
    static void Swap(bool& A, bool& B)
    static void Swap(char& A, char& B)
    static void Swap(string& A, string& B)
    static void Swap(clsDate& A, clsDate& B)

- Formatting Helper:
    static string Tabs(short NumberOfTabs)

- Number to Text Conversion:
    static string NumberToText(int num)

- Simple Text Encryption/Decryption:
    static string EncryptText(string Text, short EncryptionKey = 2)
    static string DecryptText(string Text, short EncryptionKey = 2)

================================================================================
Enums:
------
- enCharType:
    SamallLetter = 1
    CapitalLetter = 2
    Digit = 3
    MixChars = 4
    SpecialCharacter = 5

================================================================================
Usage Examples:
---------------

    clsUtil::Srand();
    int r = clsUtil::RandomNumber(1, 100);
    char c = clsUtil::GetRandomCharacter(clsUtil::CapitalLetter);
    string word = clsUtil::GenerateWord(clsUtil::SamallLetter, 6);
    string key = clsUtil::GenerateKey();
    clsUtil::GenerateKeys(5, clsUtil::MixChars);

    int arr[100];
    clsUtil::FillArrayWithRandomNumbers(arr, 10, 1, 50);
    clsUtil::ShuffleArray(arr, 10);

    string text = "Hello";
    string encrypted = clsUtil::EncryptText(text, 3);
    string decrypted = clsUtil::DecryptText(encrypted, 3);

    string numText = clsUtil::NumberToText(1234); // "One Thousand Two Hundred Thirty Four"

================================================================================
End of Documentation
================================================================================
*/

#pragma once

#include <iostream>
#include <string>

#include "clsDate.h"  // utils/clsDate.h

using namespace std;

class clsUtil
{

public:
    enum enCharType
    {
        SamallLetter = 1,
        CapitalLetter = 2,
        Digit = 3,
        MixChars = 4,
        SpecialCharacter = 5
    };
    static void Srand()
    {
        // Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        // Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {

        // updated this method to accept mixchars
        if (CharType == MixChars)
        {
            // Capital/Samll/Digits only
            CharType = (enCharType)RandomNumber(1, 3);
        }

        switch (CharType)
        {

        case enCharType::SamallLetter:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        defualt:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        }
    }

    static string GenerateWord(enCharType CharType, short Length)

    {
        string Word;

        for (int i = 1; i <= Length; i++)

        {

            Word = Word + GetRandomCharacter(CharType);
        }
        return Word;
    }

    static string GenerateKey(enCharType CharType = CapitalLetter)
    {

        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {

        for (int i = 1; i <= NumberOfKeys; i++)

        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);
    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    static void Swap(int &A, int &B)
    {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(double &A, double &B)
    {
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(bool &A, bool &B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(char &A, char &B)
    {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(string &A, string &B)
    {
        string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(clsDate &A, clsDate &B)
    {
        clsDate::SwapDates(A, B);
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void ShuffleArray(string arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string NumberToText(long long num)
    {
        if (num == 0)
            return "Zero";
    
        if (num < 0)
            return "Minus " + NumberToText(-num);
    
        static const string below20[] = {
            "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
            "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
            "Sixteen", "Seventeen", "Eighteen", "Nineteen"
        };
    
        static const string tens[] = {
            "", "", "Twenty", "Thirty", "Forty", "Fifty",
            "Sixty", "Seventy", "Eighty", "Ninety"
        };
    
        struct Scale { long long value; const char* name; };
        static const Scale scales[] = {
            {1000000000000000000LL, "Quintillion"},
            {1000000000000000LL,    "Quadrillion"},
            {1000000000000LL,       "Trillion"},
            {1000000000LL,          "Billion"},
            {1000000LL,             "Million"},
            {1000LL,                "Thousand"},
            {100LL,                 "Hundred"}
        };
    
        string result = "";
    
        for (const Scale& s : scales)
        {
            if (num >= s.value)
            {
                result += NumberToText(num / s.value) + " " + s.name;
                num %= s.value;
                if (num > 0)
                    result += " ";
            }
        }
    
        if (num >= 20)
        {
            result += tens[num / 10];
            num %= 10;
            if (num > 0)
                result += " " + below20[num];
        }
        else if (num > 0)
        {
            result += below20[num];
        }
    
        return result;
    }


    static string EncryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }
};
