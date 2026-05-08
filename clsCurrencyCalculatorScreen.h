#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : clsScreen
{
	static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
	{

		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_____________________________\n\n";

	}
	static float _ConvertFromCurrencyToUSD(float Amount, string Code) {
		clsCurrency Currency = clsCurrency::FindByCode(Code);
		return Amount / Currency.Rate();
	}
	static float _ConvertFromUSDToCurrency(float Amount , string code) {
		clsCurrency Currency = clsCurrency::FindByCode(code);
		return (Currency.Rate() * Amount);
	}
	static clsCurrency _ReadCurrencyCode(string CurrencyNum = "") {
		cout << "\nPls Enter Currency"<< CurrencyNum <<" : ";
		string Currencycode = clsInputValidate::ReadString();
		Currencycode = clsString::UpperAllString(Currencycode);
		while (!clsCurrency::IsCurrencyExist(Currencycode)) {
			Currencycode = clsInputValidate::ReadString("Currency Not Found, Verify Again Pls : ");
			Currencycode = clsString::UpperAllString(Currencycode);
		}
		clsCurrency Currency= clsCurrency::FindByCode(Currencycode);
		return Currency;
	}
	static void _ConvertCurrencies(clsCurrency Currency1, clsCurrency Currency2) {
		cout << "Pls Enter Amount To Exchange : ";
		float Amount = clsInputValidate::ReadFloatNumber();
		if (Currency1.CurrencyCode() == "USD") {
			float USDToCurrency = _ConvertFromUSDToCurrency(Amount, Currency2.CurrencyCode());
			_PrintCurrencyCard(Currency2);
			cout << Amount <<" " << Currency1.CurrencyCode() <<" = " << USDToCurrency << " " << Currency2.CurrencyCode();
		}
		if (Currency2.CurrencyCode() == "USD") {
			float CurrencyToUSD = _ConvertFromCurrencyToUSD(Amount, Currency1.CurrencyCode());
			_PrintCurrencyCard(Currency2);
			cout << Amount <<" " << Currency1.CurrencyCode() <<" = " << CurrencyToUSD << " " << Currency2.CurrencyCode();
		}
		if (Currency1.CurrencyCode() != "USD" && Currency2.CurrencyCode() != "USD") {
			float CurrencyToUSD = _ConvertFromCurrencyToUSD(Amount, Currency1.CurrencyCode());
			_PrintCurrencyCard(Currency1);
			cout << Amount << " " << Currency1.CurrencyCode() << " = " << CurrencyToUSD << " " << "USD";
			float USDToCurrency = _ConvertFromUSDToCurrency(CurrencyToUSD, Currency2.CurrencyCode());
			cout << "\nConverting To " << Currency2.CurrencyName()<<" : "<<endl;
			_PrintCurrencyCard(Currency2);
			cout << Amount << " " << Currency1.CurrencyCode() << " = " << USDToCurrency << " " << Currency2.CurrencyCode();

		}
	}
public:
	static void ShowCurrencyCalculatorScreen() {
		char YorN = 'y';
		while (YorN == 'Y'|| YorN == 'y') {
		system("cls");
		clsScreen::_DrawScreenHeader("Currency Calculator Screen");
		clsCurrency Currency1 = _ReadCurrencyCode("1");
		clsCurrency Currency2 = _ReadCurrencyCode("2");
		_ConvertCurrencies(Currency1 , Currency2);
		cout << "\nDo U Want To Perform Another Calculation? [Y/N] : ";
		cin >> YorN;
		clsInputValidate::CheckYesOrNO(YorN);
		}
	}

};

