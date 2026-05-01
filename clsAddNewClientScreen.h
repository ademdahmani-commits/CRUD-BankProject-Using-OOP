#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
#include "clsInputValidate.h";
class clsAddNewClientScreen : clsScreen
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

	static void AddNewClient() {
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
			return;
		}
		string AccountNumber;
		clsScreen::_DrawScreenHeader("\tAdd New Client Screen");

		cout << "Pls Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Account Exist , Pls Enter Another Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSucceeded:
			cout << "Saved Successfully : " << endl;
			_PrintClient(NewClient);
			break;
		case clsBankClient::enSaveResult::svFailedEmptyObject:
			cout << "Account Was Not Saved Because It's Empty " << endl;
			break;
		case clsBankClient::enSaveResult::svFailedAccountExist:
			cout << "Save Failed, Account Exist " << endl;
			break;
		}
	}

};

