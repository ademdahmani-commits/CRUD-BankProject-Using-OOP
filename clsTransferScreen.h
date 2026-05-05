#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h";
#include "clsString.h";
#include <iomanip>
#include <fstream>
class clsTransferScreen : clsScreen
{
   static void _PrintOneClientTrans(clsBankClient::stClientTransferLog Log)
    {

        cout << left << "" << "| " << setw(25) << left << Log.DateAndTime;
        cout << "| " << setw(12) << left << Log.AccountNumber1;
        cout << "| " << setw(10) << left << Log.AccountNumber2;
        cout << "| " << setw(12) << left << Log.Amount;
        cout << "| " << setw(15) << left << Log.AccountBalance1;
        cout << "| " << setw(15) << left << Log.AccountBalance2;
        cout << "| " << setw(12) << left << Log.User<<endl;

    }
   static vector <clsBankClient::stClientTransferLog> _LoadLogs() {
       vector <clsBankClient::stClientTransferLog> ConvRegisterTransferToData;
       clsBankClient::stClientTransferLog Client;
       string Line;
       fstream MyFile;
       MyFile.open("TransferLog.txt" , ios::in);
       if (MyFile.is_open()) {
           while (getline(MyFile, Line)) {
               Client = clsBankClient::ConvRegisterTransferToData(Line);
               ConvRegisterTransferToData.push_back(Client);

           }
           MyFile.close();
       }
       return ConvRegisterTransferToData;
   }

public:
    static void ShowTransferLogScreen() {
        vector <clsBankClient::stClientTransferLog> vLoadLogs = _LoadLogs();
        string Title = "\t  Transfer Logs Screen";
        string SubTitle = "\t    ("   + to_string(vLoadLogs.size())+  ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << left << "" << "\n_______________________________________________________";
        cout << "______________________________________________________\n" << endl;
        cout << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(12) << "S.Acct";
        cout << "| " << left << setw(10) << "D.Acct";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(15) << "S.Balance";
        cout << "| " << left << setw(15) << "D.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n__________________________________________________________";
        cout << "___________________________________________________\n" << endl;

        if (vLoadLogs.size() == 0)
            cout << "\t\t\t\tNo logs Available In the System!";
        else
            
            for (clsBankClient::stClientTransferLog ClientTransLog : vLoadLogs)
            {

                _PrintOneClientTrans(ClientTransLog);
                cout << endl; 
            }
        cout << setw(8) << left << "" << "\n_______________________________________________________";
        cout << "______________________________________________________\n" << endl;


    }
};

