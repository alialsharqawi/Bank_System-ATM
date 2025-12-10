/*clsDate Overview
================================================================================
                                    clsDate.h
================================================================================
Overview:
---------
This file defines the clsDate class — a comprehensive date management utility
responsible for handling dates, performing calculations, and providing
calendar-related functionality.

It allows the user to:
1. Create and manipulate date objects.
2. Validate dates and handle leap years.
3. Perform date arithmetic (add/subtract days, weeks, months, years, decades, centuries, millennia).
4. Compare dates (before, after, equal).
5. Retrieve system date and time.
6. Print date in various formats.
7. Calculate business days, vacation days, and return dates.
8. Generate month and year calendars.

================================================================================
Class Responsibilities:
-----------------------

1. Store day, month, and year internally.
2. Provide multiple constructors:
       - Default constructor (system date)
       - String-based date (DD/MM/YYYY)
       - Specific day, month, year
       - Construct by day order in year
3. Validate dates with leap year consideration.
4. Perform date arithmetic:
       - Add/subtract days, weeks, months, years, decades, centuries, millennia
5. Determine day of week, short day/month names.
6. Calculate differences between dates (in days).
7. Generate calendars for months or years.
8. Handle business and vacation days calculations.
9. Provide comparison utilities for date ordering.

================================================================================
Public Methods:
---------------

- Constructors:
    clsDate()
    clsDate(string sDate)
    clsDate(short Day, short Month, short Year)
    clsDate(short DateOrderInYear, short Year)

- Getters / Setters:
    GetDay(), SetDay()
    GetMonth(), SetMonth()
    GetYear(), SetYear()

- Print and string utilities:
    Print()
    DateToString()
    GetAccurateTime()

- Validation:
    IsValid()
    static IsValidDate(const clsDate&)

- Leap year calculations:
    isLeapYear()
    static isLeapYear(short Year)

- Date arithmetic:
    AddDays(), AddOneDay()
    IncreaseDateByXDays(), IncreaseDateByXWeeks(), IncreaseDateByXMonths(), IncreaseDateByXYears(), IncreaseDateByXDecades(), IncreaseDateByOneMillennium()
    DecreaseDateByXDays(), DecreaseDateByXWeeks(), DecreaseDateByXMonths(), DecreaseDateByXYears(), DecreaseDateByXDecades(), DecreaseDateByOneMillennium()

- Calendar utilities:
    PrintMonthCalendar(), PrintYearCalendar()

- Day/month/year helpers:
    NumberOfDaysInAYear(), NumberOfDaysInAMonth()
    DaysFromTheBeginingOfTheYear()
    GetDateFromDayOrderInYear()

- Date comparisons:
    IsDateBeforeDate2(), IsDateEqualDate2(), IsDateAfterDate2(), CompareDates()

- Business/vacation day calculations:
    IsBusinessDay()
    CalculateBusinessDays()
    CalculateVacationDays()
    CalculateVacationReturnDate()

================================================================================
Design Notes:
-------------

- Provides both static and non-static methods for flexibility.
- Leap year handling is implemented according to correct Gregorian rules.
- Modular design separates calculation logic from printing/display logic.
- Supports multiple calendars operations (month/year).
- Handles end-of-week, end-of-month, and end-of-year calculations.
- Provides utilities for day, week, month, year, decade, century, millennium operations.

================================================================================
Usage Example:
--------------

    clsDate Today;
    Today.Print();

    clsDate BirthDate("15/08/2000");
    short AgeInDays = clsDate::CalculateMyAgeInDays(BirthDate);

    clsDate FutureDate = Today;
    FutureDate.AddDays(30);
    FutureDate.PrintMonthCalendar();

    bool IsWeekend = FutureDate.IsWeekEnd();
    bool IsValid = FutureDate.IsValid();

================================================================================
End of Documentation
================================================================================
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdio>

#include "clsString.h"  // utils/clsString.h

using namespace std;

class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

public:
    // Constructors
    clsDate()
    {
        // return system date in private variable
        time_t t = time(0);
        tm *now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(string sDate)
    {
        vector<string> vDate;
        vDate = clsString::Split(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DateOrderInYear, short Year)
    {
        // This will construct a date by date order in year
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date1._Day;
        _Month = Date1._Month;
        _Year = Date1._Year;
    }

    // Getters / Setters (use these in your code)
    void SetDay(short Day) { _Day = Day; }
    short GetDay() const { return _Day; }

    void SetMonth(short Month) { _Month = Month; }
    short GetMonth() const { return _Month; }

    void SetYear(short Year) { _Year = Year; }
    short GetYear() const { return _Year; }

    // Print
    void Print()
    {
        cout << DateToString() << endl;
    }

    // System date
    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);

        short Day = now->tm_mday;
        short Month = now->tm_mon + 1;
        short Year = now->tm_year + 1900;

        return clsDate(Day, Month, Year);
    }
    static string GetAccurateTime()
    {
        time_t now = time(0);
        tm *localTime = localtime(&now);

        char TimeBuffer[20];
        strftime(TimeBuffer, sizeof(TimeBuffer), "%I:%M:%S %p", localTime);

        return string(TimeBuffer);
    }

    // Validation
    static bool IsValidDate(const clsDate &Date)
    {
        if (Date._Day < 1 || Date._Day > 31)
            return false;
        if (Date._Month < 1 || Date._Month > 12)
            return false;

        if (Date._Month == 2)
        {
            if (isLeapYear(Date._Year))
            {
                if (Date._Day > 29)
                    return false;
            }
            else
            {
                if (Date._Day > 28)
                    return false;
            }
        }

        short DaysInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > DaysInMonth)
            return false;

        return true;
    }

    bool IsValid() const
    {
        return IsValidDate(*this);
    }

    // String conversion
    static string DateToString(const clsDate &Date)
    {
        return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
    }

    string DateToString() const
    {
        return DateToString(*this);
    }

    // Leap year
    static bool isLeapYear(short Year)
    {
        // correct rule: leap => divisible by 4 and (not by 100 unless also by 400)
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear() const
    {
        return isLeapYear(_Year);
    }

    // NOTE: fixed day counts (previous code had wrong values)
    static short NumberOfDaysInAYear(short Year)
    {
        return isLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear() const
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear() const
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear() const
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear() const
    {
        return NumberOfSecondsInAYear(_Year);
    }

    // Month/day helpers
    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;
        int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
    }

    short NumberOfDaysInAMonth() const
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth() const
    {
        return NumberOfDaysInAMonth(_Month, _Year) * 24;
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth() const
    {
        return NumberOfHoursInAMonth(_Month, _Year) * 60;
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth() const
    {
        return NumberOfMinutesInAMonth(_Month, _Year) * 60;
    }

    // Day of week (0 = Sun, 1 = Mon, ...)
    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder() const
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    // Day names
    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayShortName(short Day, short Month, short Year)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }

    string DayShortName() const
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
    }

    // Month short name
    static string MonthShortName(short MonthNumber)
    {
        string Months[12] = {"Jan", "Feb", "Mar",
                             "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep",
                             "Oct", "Nov", "Dec"};
        if (MonthNumber < 1 || MonthNumber > 12)
            return "";
        return Months[MonthNumber - 1];
    }

    string MonthShortName() const
    {
        return MonthShortName(_Month);
    }

    // Print month/year calendars
    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberOfDays = NumberOfDaysInAMonth(Month, Year);
        int current = DayOfWeekOrder(1, Month, Year);

        printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < current; i++)
            printf("     ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar() const
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(int Year)
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar() const
    {
        PrintYearCalendar(_Year);
    }

    // Days from beginning of year
    static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;
        for (int i = 1; i <= Month - 1; i++)
            TotalDays += NumberOfDaysInAMonth(i, Year);
        TotalDays += Day;
        return TotalDays;
    }

    short DaysFromTheBeginingOfTheYear() const
    {
        return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    }

    // Get date from day-order in year
    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        Date._Year = Year;
        Date._Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date._Month++;
            }
            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    // Adding days
    void AddDays(short Days)
    {
        short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
        short MonthDays = 0;
        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    // Date comparisons
    static bool IsDate1BeforeDate2(const clsDate &Date1, const clsDate &Date2)
    {
        if (Date1._Year < Date2._Year)
            return true;
        if (Date1._Year > Date2._Year)
            return false;
        if (Date1._Month < Date2._Month)
            return true;
        if (Date1._Month > Date2._Month)
            return false;
        return Date1._Day < Date2._Day;
    }

    bool IsDateBeforeDate2(const clsDate &Date2) const
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(const clsDate &Date1, const clsDate &Date2)
    {
        return Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day;
    }

    bool IsDateEqualDate2(const clsDate &Date2) const
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(const clsDate &Date)
    {
        return Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year);
    }

    bool IsLastDayInMonth() const
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date._Month))
            {
                Date._Month = 1;
                Date._Day = 1;
                Date._Year++;
            }
            else
            {
                Date._Day = 1;
                Date._Month++;
            }
        }
        else
        {
            Date._Day++;
        }
        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    static void SwapDates(clsDate &Date1, clsDate &Date2)
    {
        clsDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        int SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        return IncludeEndDay ? (++Days * SwapFlagValue) : (Days * SwapFlagValue);
    }

    int GetDifferenceInDays(const clsDate &Date2, bool IncludeEndDay = false) const
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(const clsDate &DateOfBirth)
    {
        return static_cast<short>(GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true));
    }

    // Weeks / months / years operations
    static clsDate IncreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
            Date = AddOneDay(Date);
        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    clsDate IncreaseDateByXWeeks(short Weeks, clsDate &Date)
    {
        for (short i = 1; i <= Weeks; i++)
            Date = IncreaseDateByOneWeek(Date);
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }

    clsDate IncreaseDateByOneMonth(clsDate &Date)
    {
        if (Date._Month == 12)
        {
            Date._Month = 1;
            Date._Year++;
        }
        else
            Date._Month++;

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > NumberOfDaysInCurrentMonth)
            Date._Day = NumberOfDaysInCurrentMonth;

        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    clsDate IncreaseDateByXDays(short Days, clsDate &Date)
    {
        for (short i = 1; i <= Days; i++)
            Date = AddOneDay(Date);
        return Date;
    }

    void IncreaseDateByXDays(short Days)
    {
        IncreaseDateByXDays(Days, *this);
    }

    clsDate IncreaseDateByXMonths(short Months, clsDate &Date)
    {
        for (short i = 1; i <= Months; i++)
            Date = IncreaseDateByOneMonth(Date);
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate &Date)
    {
        Date._Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    clsDate IncreaseDateByXYears(short Years, clsDate &Date)
    {
        Date._Year += Years;
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    clsDate IncreaseDateByOneDecade(clsDate &Date)
    {
        Date._Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    clsDate IncreaseDateByXDecades(short Decade, clsDate &Date)
    {
        Date._Year += Decade * 10;
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        IncreaseDateByXDecades(Decade, *this);
    }

    clsDate IncreaseDateByOneCentury(clsDate &Date)
    {
        Date._Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    clsDate IncreaseDateByOneMillennium(clsDate &Date)
    {
        Date._Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

    // Decrease operations
    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date._Day == 1)
        {
            if (Date._Month == 1)
            {
                Date._Month = 12;
                Date._Day = 31;
                Date._Year--;
            }
            else
            {
                Date._Month--;
                Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
            }
        }
        else
        {
            Date._Day--;
        }
        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
            Date = DecreaseDateByOneDay(Date);
        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate &Date)
    {
        for (short i = 1; i <= Weeks; i++)
            Date = DecreaseDateByOneWeek(Date);
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate &Date)
    {
        if (Date._Month == 1)
        {
            Date._Month = 12;
            Date._Year--;
        }
        else
            Date._Month--;

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > NumberOfDaysInCurrentMonth)
            Date._Day = NumberOfDaysInCurrentMonth;

        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate &Date)
    {
        for (short i = 1; i <= Days; i++)
            Date = DecreaseDateByOneDay(Date);
        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate &Date)
    {
        for (short i = 1; i <= Months; i++)
            Date = DecreaseDateByOneMonth(Date);
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate &Date)
    {
        Date._Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate &Date)
    {
        Date._Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate &Date)
    {
        Date._Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate &Date)
    {
        Date._Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate &Date)
    {
        Date._Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate &Date)
    {
        Date._Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    // Week/day helpers
    static short IsEndOfWeek(const clsDate &Date)
    {
        return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
    }

    short IsEndOfWeek() const
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(const clsDate &Date)
    {
        short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd() const
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(const clsDate &Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay() const
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(const clsDate &Date)
    {
        return 6 - DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
    }

    short DaysUntilTheEndOfWeek() const
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(const clsDate &Date1)
    {
        clsDate EndOfMonthDate;
        EndOfMonthDate._Day = NumberOfDaysInAMonth(Date1._Month, Date1._Year);
        EndOfMonthDate._Month = Date1._Month;
        EndOfMonthDate._Year = Date1._Year;
        return GetDifferenceInDays(Date1, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOfMonth() const
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(const clsDate &Date1)
    {
        clsDate EndOfYearDate;
        EndOfYearDate._Day = 31;
        EndOfYearDate._Month = 12;
        EndOfYearDate._Year = Date1._Year;
        return GetDifferenceInDays(Date1, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear() const
    {
        return DaysUntilTheEndOfYear(*this);
    }

    // Business / vacation helpers
    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short Days = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;
            DateFrom = AddOneDay(DateFrom);
        }
        return Days;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        return CalculateBusinessDays(DateFrom, DateTo);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;
        for (short i = 1; i <= VacationDays; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;
            DateFrom = AddOneDay(DateFrom);
        }
        for (short i = 1; i <= WeekEndCounter; i++)
            DateFrom = AddOneDay(DateFrom);
        return DateFrom;
    }

    // Date comparisons
    static bool IsDate1AfterDate2(const clsDate &Date1, const clsDate &Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(const clsDate &Date2) const
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare
    {
        Before = -1,
        Equal = 0,
        After = 1
    };

    static enDateCompare CompareDates(const clsDate &Date1, const clsDate &Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;
        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;
        return enDateCompare::After;
    }

    enDateCompare CompareDates(const clsDate &Date2) const
    {
        return CompareDates(*this, Date2);
    }
};