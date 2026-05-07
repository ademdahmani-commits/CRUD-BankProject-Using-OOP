#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
class clsCurrencyExchangeMainScreen : clsScreen
{
	enum enCurrenciesMainMenueOptions { ListCurrencies = 0 , FindCurrency =1,
		UpdateRate =2 , CurrencyCalculator = 3 , MainMenu =4
	};
	static void _ListCurrencies() {
		//cout << "List Currencies Screen Will Be Here";
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _FindCurrency() {
	//	cout << "Find Currency Screen Will Be Here";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _UpdateRate() {
		//cout << "Update Rate Screen Will Be Here";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _CurrencyCalculator() {
		cout << "Currency Calculator Screen Will Be Here";
	}
	static void _MainMenu() {

	}
	static void _GoBackToScreen() {
		cout << "\nPress Any Key To Go Back To Main Screen";
		system("pause>0");
		ShowCurrenciesMenue();
	}
	static short ReadCurrenciesMainMenueOptions() {
		cout << setw(37) << left << "" << "Pls Enter a Number between [1-5] : ";
		short Num = clsInputValidate::ReadShrtNumberBetween(1, 5);
		return Num-1;
	}
	static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions Option) {
		switch (Option)
		{
		case clsCurrencyExchangeMainScreen::ListCurrencies:
			system("cls");
			_ListCurrencies();
			_GoBackToScreen();
			break;
		case clsCurrencyExchangeMainScreen::FindCurrency:
			system("cls");
			_FindCurrency();
			_GoBackToScreen();
			break;
		case clsCurrencyExchangeMainScreen::UpdateRate:
			system("cls");
			_UpdateRate();
			_GoBackToScreen();
			break;
		case clsCurrencyExchangeMainScreen::CurrencyCalculator:
			system("cls");
			_CurrencyCalculator();
			_GoBackToScreen();
			break;
		case clsCurrencyExchangeMainScreen::MainMenu:
			break;
		}
	}
public : 
	static void ShowCurrenciesMenue()
	{

		system("cls");
		_DrawScreenHeader("    Currancy Exhange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exhange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

_PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions(ReadCurrenciesMainMenueOptions()));
	}

};

