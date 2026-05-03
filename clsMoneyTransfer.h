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
	static clsBankClient _ReadAccountNumber(string AccountNum , string Message) {
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
			char YorN = 'n';
			cout << "Are u Sure u Want To Perform This Transaction Y/N : ";
			cin >> YorN;
			clsInputValidate::CheckYesOrNO(YorN);
			if (YorN == 'Y' || YorN == 'y') {
				while (!Client1.MoneyTransfer(MoneyToTransfer, Client2)) {
					cout << "Inssuficient Amount, Pls Enter Another Amount : ";
					MoneyToTransfer = clsInputValidate::ReadDblNumber();
				}
				cout << "Transfer Done Successfully" << endl;
				_PrintClientCard(Client1.AccountNumber());
				_PrintClientCard(Client2.AccountNumber());
			}
			else {
				cout << "Transfer Cancelled "<<endl;
				return;
			}
	}
	static bool _VerifyAccounts(clsBankClient& Client1 , clsBankClient& Client2) {
		return Client1.AccountNumber() != Client2.AccountNumber();
	}

public:
	static void ShowMoneyTransferScreen() {
		clsScreen::_DrawScreenHeader("Money Transfer Screen");
		string AccountNumber;
		clsBankClient Client1 = _ReadAccountNumber(AccountNumber, "Pls Enter account Number To Transfer From : ");
		_PrintClientCard(Client1.AccountNumber());
		clsBankClient Client2 = _ReadAccountNumber(AccountNumber, "Pls Enter account Number To Transfer To : ");
		while (!_VerifyAccounts(Client1, Client2)) {
			Client2 = _ReadAccountNumber(AccountNumber, "Pls Don't Enter The Same Account , Try again : ");
		}
		_PrintClientCard(Client2.AccountNumber());
		_MoneyTransfer(Client1, Client2);

		}

};

