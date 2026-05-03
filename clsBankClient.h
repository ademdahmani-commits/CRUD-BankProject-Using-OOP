#pragma once
#include <iostream>
#include <fstream>
#include "clsPerson.h";
#include "clsString.h";
class clsBankClient : public clsPerson
{
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line) {
		vector <string> ClientInfo = clsString::Split(Line , "#//#");

		return clsBankClient (enMode::UpdateMode, ClientInfo[0], ClientInfo[1],
			ClientInfo[2], ClientInfo[3], ClientInfo[4], ClientInfo[5], stoi(ClientInfo[6]));
	}
	
	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode , "","","","","","",0);
	}
	
	static vector <clsBankClient> _LoadClientsDataFromFile() {
		vector <clsBankClient> Load;
		fstream MyFile;
		string Line;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				Load.push_back(Client);
			}
			MyFile.close();
		}
		return Load;
	}
	
	static string _ConvertClientObjectToLine(clsBankClient Client , string Seperator = "#//#") {
		string FullObject = "";
		FullObject += Client.FirstName + Seperator;
		FullObject += Client.LastName + Seperator;
		FullObject += Client.Email + Seperator;
		FullObject += Client.Phone + Seperator;
		FullObject += Client.AccountNumber() + Seperator;
		FullObject += Client.PinCode + Seperator;
		FullObject += to_string(Client.AccountBalance);
		return FullObject;
	}
	
	static void _SaveClientsDataToFile(vector <clsBankClient> vClient) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsBankClient &C : vClient) {
				if (C._MarkForDelete != true) {
				string Convert = _ConvertClientObjectToLine(C);
				MyFile << Convert << endl;
				}
			}
			MyFile.close();
		}
	}
	
	void _Update() {
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
		for (clsBankClient &C : _vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}
	
	static void _SaveNewClientToFile(clsBankClient Client) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);
		if (MyFile.is_open()) {
			MyFile << _ConvertClientObjectToLine(Client) << endl;
		}
		MyFile.close();
	}
	
	void _AddNew() {
		_SaveNewClientToFile(*this);
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
			_PinCode = PinCode;
			_AccountBalance = AccountBalance;
	}
	
	bool IsEmpty() {
		return (_Mode == EmptyMode);
	}
	
	string AccountNumber() {
		return _AccountNumber;
	}
	
	void SetPassword(string PinCode) {
		_PinCode = PinCode;
	}
	
	string GetPassword() {
		return _PinCode;
	}
	
	__declspec(property(get = GetPassword, put = SetPassword)) string PinCode;
	
	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance; 
	}
	
	float GetAccountBalance() {
		return _AccountBalance;
	}
	
	__declspec(property(get = GetAccountBalance , put = SetAccountBalance))float AccountBalance;

	static clsBankClient Find(string AccountNumber) {
		fstream MyFile;
		vector <clsBankClient> vClient;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}
			MyFile.close();
			}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		fstream File;
		File.open("Clients.txt", ios::in);
			if (File.is_open()) {
				string Line;
				while (getline(File, Line)) {
					clsBankClient Client = _ConvertLineToClientObject(Line);
					if (Client.AccountNumber() == AccountNumber && Client.GetPassword() == PinCode) {
						File.close();
						return Client;
					}
				}
				File.close();
			}
			return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResult {svFailedEmptyObject = 0, svSucceeded = 1 , svFailedAccountExist = 2};

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "" , 0);
	}
	
	enSaveResult Save() {
		switch (_Mode)
		{
		case clsBankClient::enMode::EmptyMode:
			if (IsEmpty()) {
				return enSaveResult::svFailedEmptyObject;
			}
				break;
		case clsBankClient::enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
			break;
		case clsBankClient::enMode::AddNewMode:
			if (clsBankClient::IsClientExist(AccountNumber())) {
				return enSaveResult::svFailedAccountExist;
			}
			else
				_AddNew();
			return enSaveResult::svSucceeded;
			break;
		}
	}

	bool Delete() {
		fstream MyFile;
		vector <clsBankClient> Clients = _LoadClientsDataFromFile();
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsBankClient& C : Clients) {
				if (C.AccountNumber() == AccountNumber()) {
					C._MarkForDelete = true;
					break;
				}
			}
			_SaveClientsDataToFile(Clients);
			*this = _GetEmptyClientObject();
		}
		MyFile.close();
		return true;
	}

	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalance = 0;
		for (clsBankClient& C : vClients) {
			TotalBalance += C.AccountBalance;
		}
		return TotalBalance;
	}

	bool Deposit(double Amount) {
		if (Amount <= 0) {
			return false;
		}
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > GetAccountBalance() || Amount < 0) {
			return false;
		}
		_AccountBalance -= Amount;
		Save();
	}

	bool MoneyTransfer(double Amount , clsBankClient& TransferDestination) {
		if (Amount > AccountBalance || Amount < 0) {
			return false;
		}
		Withdraw(Amount);
		TransferDestination.Deposit(Amount);
		return true;
	}

};

