#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h"
class clsFindClientScreen : protected clsScreen
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
	static void FindClient() {
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
			return;
		}
		clsScreen::_DrawScreenHeader("\tFind Client Screen");
		string AccountNumber = "";
		cout << "Pls Enter Account Number : ";
		cin >> AccountNumber;
		if (clsBankClient::IsClientExist(AccountNumber)) {
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			cout << "Client Exist : " << endl;
			_PrintClient(Client);
		}
		else
			cout << "Client Not Found " << endl;
		

	}

};

