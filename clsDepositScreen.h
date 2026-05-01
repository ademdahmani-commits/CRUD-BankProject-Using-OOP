#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"


class clsDepositScreen : protected clsScreen
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

public : 
	static void ShowDepositScreen() {
		clsScreen::_DrawScreenHeader("Deposit Screen"); 
		string AccountNumber = clsInputValidate::ReadString("Pls Enter Account number : ");
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Client Account Number [" << AccountNumber << "] Not Found,Try Again : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		double Amount;
		cout << "Enter The Amount U Want To Deposit : ";
		Amount = clsInputValidate::ReadDblNumber();
		cout << "\nAre you sure you want to perform this transaction? Y/N ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client.Deposit(Amount)) {
				cout << "\nAmount Deposited Successfully.\n";
				cout << "\nNew Balance Is: " << Client.AccountBalance;
			}
			else
				cout << "Amount Is Not Valid";

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}

};

