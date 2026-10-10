#pragma once

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace clsConsole
{
    inline void ClearScreen()
    {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::cout << "\033[2J\033[H" << std::flush;
#endif
    }

    inline void Pause()
    {
        std::cout << "Press any key to continue..." << std::flush;
#if defined(_WIN32) || defined(_WIN64)
        (void)_getch();
#else
        termios originalSettings{};
        if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &originalSettings) == 0)
        {
            termios rawSettings = originalSettings;
            rawSettings.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
            if (tcsetattr(STDIN_FILENO, TCSANOW, &rawSettings) == 0)
            {
                (void)std::cin.get();
                tcsetattr(STDIN_FILENO, TCSANOW, &originalSettings);
            }
            else
            {
                (void)std::cin.get();
            }
        }
        else
        {
            (void)std::cin.get();
        }
        std::cout << '\n';
#endif
    }

    inline void SetColor(int color)
    {
#if defined(_WIN32) || defined(_WIN64)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
#else
        constexpr int foregroundColors[] = {30, 34, 32, 36, 31, 35, 33, 37};
        const int foreground = color & 0x07;
        const bool isBright = (color & 0x08) != 0;
        std::cout << "\033[" << (isBright ? foregroundColors[foreground] + 60 : foregroundColors[foreground]) << 'm';
#endif
    }

    inline void Sleep(unsigned long milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}
