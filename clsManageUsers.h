#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h"
#include <iomanip>
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h";
#include "clsFindUserScreen.h";
#include "clsUser.h";
class clsManageUsers : protected clsScreen
{
    static short _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose Option? [1 to 6]? ";
        short Option = clsInputValidate::ReadShrtNumberBetween(1, 6);
        return Option;
    }

    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };

    static void _ShowListUsersScreen()
    {
       // cout << "\nList Users Screen Will Be Here.\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
       // cout << "\nAdd New User Screen Will Be Here.\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        //cout << "\nDelete User Screen Will Be Here.\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        //cout << "\nUpdate User Screen Will Be Here.\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        //cout << "\nFind User Screen Will Be Here.\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    void _GoBackToManageUsersScreen() {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions Option) {
        switch (Option)
        {
        case clsManageUsers::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            system("pause>0");
            clsManageUsers::ShowManageUsersMenue();
            break;
        case clsManageUsers::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            system("pause>0");
            clsManageUsers::ShowManageUsersMenue();
            break;
        case clsManageUsers::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            system("pause>0");
            clsManageUsers::ShowManageUsersMenue();
            break;
        case clsManageUsers::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            system("pause>0");
            clsManageUsers::ShowManageUsersMenue();
            break;
        case clsManageUsers::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            system("pause>0");
            clsManageUsers::ShowManageUsersMenue();
            break;
        case clsManageUsers::eMainMenue:
            break;
        }
    }

public: 

    static void ShowManageUsersMenue()
    {
        system("cls");
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)) {
            return;
        }
        clsScreen::_DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformManageUsersMenueOption(enManageUsersMenueOptions(_ReadManageUsersMenueOption()));
    }

};

