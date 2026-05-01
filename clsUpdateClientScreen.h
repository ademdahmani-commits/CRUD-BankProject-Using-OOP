#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include <string>
#include "clsScreen.h" 
class clsUpdateClientScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient &Client)
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
	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "Pls Enter FirstName : ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "Pls Enter LastName : ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "Pls Enter Email : ";
		Client.Email = clsInputValidate::ReadString();
		cout << "Pls Enter Phone : ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "Pls Enter PinCode : ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "Pls Enter Account Balance : ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

public:
	static void UpdateClient() {
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
			return;
		}
		clsScreen::_DrawScreenHeader("\t Update Client Screen");
		string AccountNumber; 
		cout << "Pls Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Pls Enter Account Number, Client Not Found : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		cout << "-------------------------" << endl;
		cout << "Update Client Info : " << endl;
		_ReadClientInfo(Client);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSucceeded:
			cout << "Client Updated Successfully : " << endl;
			_PrintClient(Client);
			break;
		case clsBankClient::enSaveResult::svFailedEmptyObject:
			cout << "Account Was Not Saved Because It's Empty : " << endl;
			break;
		}

	}

};

