#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h";
#include "clsInputValidate.h";
#include "Global.h";
#include "clsMainScreen.h"
class clsLoginScreen : protected clsScreen
{
	static void _LoginScreen() {
		bool LoginFailed = false;
		string UserName, Password;
		do {
			if (LoginFailed) {
				cout << "\nInvalid UserName Or Password" << endl;
			}
			cout << "UserName : ";
			UserName = clsInputValidate::ReadString();
			cout << "Password : ";
			Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);
		clsMainScreen::ShowMainMenue();
	}

public:

	static void _ShowLoginScreen() {
		system("cls");
		clsScreen::_DrawScreenHeader("Login Screen");
		_LoginScreen();
	}

};

