#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h";
#include "clsUser.h";
class clsFindUserScreen : clsScreen
{
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:
	static void ShowFindUserScreen() {
		clsScreen::_DrawScreenHeader("\t  Update User Screen");
		string UserName;
		cout << "Pls Enter UserName : ";
		UserName = clsInputValidate::ReadString();
		if (!clsUser::IsUserExist(UserName)) {
			cout << "\nUser Not Found"<<endl;
		}
		else {
			clsUser User1 = clsUser::Find(UserName);
			cout << "User Found : \n";
			_PrintUser(User1);
		}
		
	}

};

