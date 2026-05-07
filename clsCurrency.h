#pragma once
#include <iostream>
#include <fstream>
#include "clsString.h"
#include <string>
class clsCurrency
{
	enum enMode{EmptyMode = 0 , UpdateMode = 1};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineIntoCurrencyObject(string Line) {
		vector <string> vObject = clsString::Split(Line);
		return clsCurrency(UpdateMode, vObject[0], vObject[1], vObject[2], stof(vObject[3]));
	}
	static string _ConvertCurrencyObjectIntoLine(clsCurrency Object , string Sep ="#//#") {
		string CovertedObj;
		CovertedObj += Object.Country() + Sep;
		CovertedObj += Object.CurrencyCode() + Sep;
		CovertedObj += Object.CurrencyName() + Sep;
		CovertedObj += to_string(Object.Rate()) + Sep;
		return CovertedObj;
	}
	static vector <clsCurrency> _LoadCurrencyDataFormFile() {
		vector <clsCurrency> vCurrency;
		string Line;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsCurrency Data = _ConvertLineIntoCurrencyObject(Line);
				vCurrency.push_back(Data);
			}
		}
		MyFile.close();
		return vCurrency;
	}
	static void SaveCurrencyDataToFile(vector <clsCurrency> vData) {
		vector <clsCurrency> Currency = vData;
		string Line;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsCurrency& C : Currency) {
				Line = _ConvertCurrencyObjectIntoLine(C);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	void _Update() {
		vector <clsCurrency> vData = _LoadCurrencyDataFormFile();
		for (clsCurrency& Obj : vData) {
			if (Obj.CurrencyCode() == CurrencyCode()) {
				Obj = *this;
				SaveCurrencyDataToFile(vData);
				break;
			}
		}
	}
	static clsCurrency GetEmptyObject() {
		return clsCurrency(EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	bool isEmpty() {
		return _Mode == EmptyMode;
	}
	string Country() {
		return _Country;
	}
	string CurrencyCode() {
		return _CurrencyCode;
	}
	string CurrencyName() {
		return _CurrencyName;
	}
	void UpdateRate(float Rate) {
		_Rate = Rate;
		_Update();
	}
	float Rate() {
		return _Rate;
	}
	static clsCurrency FindByCode(string Code) {
		Code = clsString::UpperAllString(Code);
		string Line;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsCurrency Data = _ConvertLineIntoCurrencyObject(Line);
				if (Data.CurrencyCode() == Code) {
					MyFile.close();
					return Data;
				}
			}
		}
		MyFile.close();
		return GetEmptyObject();
	}
	static clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllString(Country);
		string Line;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsCurrency Data = _ConvertLineIntoCurrencyObject(Line);
				if (clsString::UpperAllString(Data.Country()) == Country) {
					MyFile.close();
					return Data;
				}
			}
		}
		MyFile.close();
		return GetEmptyObject();
	}
	static bool IsCurrencyExist(string Code) {
		clsCurrency Currency = FindByCode(Code);
		return(!Currency.isEmpty());
	}
	static vector <clsCurrency> GetCurrenciesList() {
		vector <clsCurrency> vList = _LoadCurrencyDataFormFile();
		return vList;
	}
};

