#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include <string>
#include "clsScreen.h"


class clsDeleteClientScreen : clsScreen
{
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:

	static void DeleteClient() {
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return;
		}
		clsScreen::_DrawScreenHeader("\tDelete Client Screen");
		string AccountNumber;
		cout << "Pls Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Account Not Found, Pls Enter Another Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		char YesOrNo = 'n';
		cout << "Do u Want To Delete Client? Y/N : ";
		cin >> YesOrNo;
		clsInputValidate::CheckYesOrNO(YesOrNo);
		if (YesOrNo == 'Y' || YesOrNo == 'y') {
			Client.Delete();
			cout << "\nClient Card After Delete : " << endl;
			_PrintClient(Client);
		}
		else
			cout << "Client Not Deleted" << endl;

	}
};

