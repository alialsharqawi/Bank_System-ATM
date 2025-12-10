#include <windows.h>
#include <rpc.h>
#include <rpcndr.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

#include "../Welcome_Screen/clsStartUpBankSystem.h"

int main()
{
    while (true) // Infinite loop to keep the application running
    {
        clsStartUpBankSystem::ShowStartUpMenu();
    }
    return 0;
}