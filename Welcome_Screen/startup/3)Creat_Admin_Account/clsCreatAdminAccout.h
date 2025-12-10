#pragma once

#include "../1)Login_As_Admin/Admin_Dashboard_Screens/Manage_Admins_Menu/Manage_Admins_Screens/clsAddNewAdminScreen.h"

class clsCreatAdminAccount{
    public:
    static void CreateNewAdmin(){
        clsAddNewAdminScreen::ShowAddNewAdminScreen("     Register New Admin Account");
    }
};