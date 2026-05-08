#pragma once
#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen :clsScreen
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
    static void _ShowByCode()
    {
        cout << "Pls Enter Currency Code : ";
        string code = clsInputValidate::ReadString();
        clsCurrency Currency = clsCurrency::FindByCode(code);
        while (Currency.isEmpty()) {
            cout << "Code Not Found, Try Another One : ";
            code = clsInputValidate::ReadString();
            Currency = clsCurrency::FindByCode(code);
        }
        _PrintCurrency(Currency);
    }
    static void _ShowByCountry()
    {
        cout << "Pls Enter The Country : ";
        string country = clsInputValidate::ReadString();
        clsCurrency Currency = clsCurrency::FindByCountry(country);
        while (Currency.isEmpty()) {
            cout << "Country Not Found, Try Another One : ";
            country = clsInputValidate::ReadString();
            Currency = clsCurrency::FindByCountry(country);
        }
        _PrintCurrency(Currency);
    }
public:

    static void ShowFindCurrencyScreen() {
        clsScreen::_DrawScreenHeader("Find Currency Screen");
        enum enOption{ Code = 1 , Country = 2};
        cout << "Find By [1] Code or [2] Country : ";
        short Option = clsInputValidate::ReadShrtNumberBetween(1, 2);
        if (Option == Code) {
           _ShowByCode();
        }
        else if (Option == Country) {
            _ShowByCountry();
        }
        else {
            cout << "Error Out Of Range"<<endl;
        }
    
    }


};

