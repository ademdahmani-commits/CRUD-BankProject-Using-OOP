#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyRateScreen : clsScreen
{
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
    static void _ShowByCode(string &code)
    {
        clsCurrency Currency = clsCurrency::FindByCode(code);
        while (Currency.isEmpty()) {
            cout << "Code Not Found, Try Another One : ";
            code = clsInputValidate::ReadString();
            Currency = clsCurrency::FindByCode(code);
        }
        _PrintCurrency(Currency);
    }
    static void _UpdateRate(string code) {
        clsCurrency UpdateCurrencyRate = clsCurrency::FindByCode(code);
        cout << "\nUpdate Currency Rate : "<<endl;
        cout << "_________________________________"<<endl;
        cout << "Enter New Rate : ";
        float Rate = clsInputValidate::ReadFloatNumber();
        UpdateCurrencyRate.UpdateRate(Rate);
    }
public:
	static void ShowUpdateCurrencyRateScreen() {
        clsScreen::_DrawScreenHeader("Update Currency Rate Screen");
        cout << "Pls Enter Currency Code : ";
        string code = clsInputValidate::ReadString();
        _ShowByCode(code);
        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
        char YorN = 'n';
        cin >> YorN;
        clsInputValidate::CheckYesOrNO(YorN);
        if (YorN == 'y' || YorN == 'Y') {
            _UpdateRate(code);
            cout << "Currency Updated Successfully" << endl;
            _PrintCurrency(clsCurrency::FindByCode(code));
        }
        else {
            cout << "Update Rate Cancelled" <<endl;
        }
	}

};

