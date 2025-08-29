#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "../input-validate/clsInputValidate.h" // You can get this lib from https://github.com/yacineragueb/InputValidate-lib-cpp

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyMenueOptions {
		eListCurrencies = 1, eFindCurrency = 2,
		eUpdatedRate = 3, eCurrencyCalculator = 4, eShowMainMenue = 5
	};

	static short ReadCurrencyMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static void _ShowListCurrenciesScreen() {
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen() {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen() {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

    static void _GoBackToCurrencyMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowCurrencyExchangeMenue();
    }

    static void _PerformCurrencyExchangeMenueOption(enCurrencyMenueOptions CurrencyMenueOptions)
    {
        switch (CurrencyMenueOptions)
        {
        case enCurrencyMenueOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyMenue();
            break;
        }

        case enCurrencyMenueOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenue();
            break;
        }

        case enCurrencyMenueOptions::eUpdatedRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyMenue();
            break;
        }

        case enCurrencyMenueOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyMenue();
            break;
        }

        case enCurrencyMenueOptions::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:

	static void ShowCurrencyExchangeMenue() {

		if (!CheckAccessRights(clsUser::enPermissions::pShowCurrencyExchange))
		{
			return;// this will exit the function and it will not continue
		}

        system("cls");
		_DrawScreenHeader("   Currency Exchange Main Screen");


        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchangeMenueOption((enCurrencyMenueOptions)ReadCurrencyMenueOption());
	}
};

