#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h";
#include "clsUser.h";
class clsDeleteUserScreen : clsScreen
{
	static void _PrintUser(clsUser User) {
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
	static void ShowDeleteUserScreen() {
		clsScreen::_DrawScreenHeader("Delete User Screen");
		string UserName;
		cout << "Pls Enter UserName : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "User Not Found, Try Again : ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);
		char YorN = 'n';
		cout << "Do u Want to Delete This User? Y/N : ";
		cin >> YorN;
		clsInputValidate::CheckYesOrNO(YorN);
		if (YorN == 'y' || YorN == 'Y') {
			User1.Delete();
			cout << "User Deleted Successfully" << endl;
		}
		else
			cout << "User Not deleted"<<endl;
	}

};

