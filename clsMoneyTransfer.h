#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h";
class clsMoneyTransfer : clsScreen
{
	static void _PrintClientCard(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		cout << "Client Card : " << endl;
		cout << "\n_______________________" << endl;
		cout << "Full Name : " << Client.FullName() << endl;
		cout << "Account Number : " << Client.AccountNumber() << endl;
		cout << "Balance : " << Client.AccountBalance << endl;
		cout << "_______________________" << endl;
	}
	static clsBankClient _VerifyAccountNumber(string AccountNum , string Message) {
		string AccountNumber = clsInputValidate::ReadString(Message);
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("Account Not Found Enter Another One : ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return Client;
	}
	static void _MoneyTransfer(clsBankClient &Client1, clsBankClient &Client2) {
		double MoneyToTransfer;
		cout << "Enter Transfer Amount : ";
		MoneyToTransfer = clsInputValidate::ReadDblNumber();
		while (MoneyToTransfer > Client1.AccountBalance || MoneyToTransfer < 0) {
			cout << "Inssuficient Amount, Pls Enter Another Amount : ";
			MoneyToTransfer = clsInputValidate::ReadDblNumber();
		}
		if (MoneyToTransfer <= Client1.AccountBalance) {
			char YorN = 'n';
			cout << "Are u Sure u Want To Perform This Transaction Y/N : ";
			cin >> YorN;
			clsInputValidate::CheckYesOrNO(YorN);
			if (YorN == 'Y' || YorN == 'y') {
				Client1.AccountBalance - MoneyToTransfer;
				Client2.AccountBalance + MoneyToTransfer;
				Client1.Save();
				Client2.Save();
				cout << "Transfer Done Successfully" << endl;
				_PrintClientCard(Client1.AccountNumber());
				_PrintClientCard(Client2.AccountNumber());
			}
			else {
				cout << "Transfer Cancelled : ";
			}
		}
	}
public:
	static void ShowMoneyTransferScreen() {
		clsScreen::_DrawScreenHeader("Money Transfer Screen");
		string AccountNumber;
		clsBankClient Client1 = _VerifyAccountNumber(AccountNumber , "Pls Enter account Number To Transfer From : ");
		_PrintClientCard(Client1.AccountNumber());
		clsBankClient Client2 = _VerifyAccountNumber(AccountNumber, "Pls Enter account Number To Transfer To : ");
		_PrintClientCard(Client2.AccountNumber());
		_MoneyTransfer(Client1, Client2);

		}

};

