#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
#include "clsUser.h";
class clsClientListScreen : protected clsScreen
{
	static void _PrintClientRecordLine(clsBankClient &Client)
	{
		
		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		if (CurrentUser.UserName == "Admin") {
			cout << "| " << setw(10) << left << clsUtil::DecryptClientPass(Client.PinCode);
		}
		else
		{
		cout << "| " << setw(10) << left << Client.PinCode;
		}
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}

public:
	static void ShowClientsList()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
			return;
		}
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		clsScreen::_DrawScreenHeader("\t   ClientListScren", "\t    (" +to_string(vClients.size())+")"+"Client(s)");

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0) {
			cout << "\t\t\t\tNo Clients Available In the System!";
		}
		else {
			for (clsBankClient& C : vClients) {
				_PrintClientRecordLine(C);
				cout << endl;
			}
		}



		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};

