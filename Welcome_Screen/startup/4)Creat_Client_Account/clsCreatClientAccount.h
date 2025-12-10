#pragma once
#include "../1)Login_As_Admin/Admin_Dashboard_Screens/Manage_Clients_Menu/Manage_Clients_Screens/clsAddNewClientScreen.h"

class clsCreatClientAccount{
    public:
    static void CreateNewClient(){
        clsAddNewClientScreen::AddNewClientScreen("     Register New Client Account");
    }
    
};