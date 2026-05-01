#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
class clsWithdrawScreen : protected clsScreen
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
	static void ShowWithdrawScreen() {
		clsScreen::_DrawScreenHeader("Withdraw Screen");
		string AccountNumber = clsInputValidate::ReadString("Pls Enter Account number : ");
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Client Account Number [" << AccountNumber << "] Not Found,Try Again : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		double Amount;
		cout << "Enter The Amount U Want To Withdraw : ";
		Amount = clsInputValidate::ReadDblNumber();
		cout << "\nAre you sure you want to perform this transaction? Y/N ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Withdraw(Amount)) {
			cout << "\nNew Balance Is: " << Client.AccountBalance;
			cout << "\nAmount Withdrawn Successfully.\n";
			}
			else {
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client.AccountBalance;
			}

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};

