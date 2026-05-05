#pragma once
#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "clsUser.h";
#include "clsInputValidate.h";
#include "Global.h";
#include "clsMainScreen.h"
class clsLoginScreen : protected clsScreen
{
	static void _LoginRegister(clsUser User) {
		vector <string> LoginRegisterObject;
		string LoginRegisterLine;
		fstream MyFile;
		MyFile.open("LoginRegister.txt",ios::app);
		if (MyFile.is_open()) {
			LoginRegisterLine = clsUser::LoginRegisterToLine(User);
			MyFile << LoginRegisterLine << endl;
		}
		MyFile.close();
	}
	static bool _LoginScreen() {
		bool LoginFailed = false;
		short counter = 2;
		string UserName, Password;
		do {
			if (LoginFailed) {
				cout << "\nLogin Failed u have " << counter << " More Trials To Login" << endl;
				cout << "Invalid UserName Or Password" << endl;
				if (counter == 0) {
					cout << "\nYou are Locked After 3 Failed Trials" << endl;
					return false;
				}
				counter--;
			}
			cout << "\nUserName : ";
			UserName = clsInputValidate::ReadString();
			cout << "Password : ";
			Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();
			
			
		} while (LoginFailed);
		
		_LoginRegister(CurrentUser);
		clsMainScreen::ShowMainMenue();
		
	}
public:

	static bool _ShowLoginScreen() {
		CurrentUser = clsUser::Find("","");
		system("cls");
		clsScreen::_DrawScreenHeader("Login Screen");
		return _LoginScreen();
	}

};

