#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "../input-validate/clsInputValidate.h" // You can get this lib from https://github.com/yacineragueb/InputValidate-lib-cpp

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static void _TransferAmount(clsBankClient Sender, clsBankClient Receiver) {
        double Amount = 0;

        cout << "\nEnter Transfer Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount > Sender.AccountBalance) {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount: ";
            Amount = clsInputValidate::ReadDblNumber();
        }

        char Answer = 'n';
        cout << "\nAre you sure you want to perform this Operation? y/n ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            
            if (Sender.Transfer(Amount, Receiver, CurrentUser.UserName)) {
                cout << "\nTransfer done successfully\n";
            }
            else {
                cout << "\nTransfer Faild\n";
            }

            _PrintClient(Sender);
            _PrintClient(Receiver);
        }
        else {
            cout << "\nTransfer has been canceled\n";
        }
    }

public:
	static void ShowTransferScreen() {
		_DrawScreenHeader("\t  Transfer Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number To Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, Try again: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Sender = clsBankClient::Find(AccountNumber);
        _PrintClient(Sender);

        cout << "\nPlease Enter Account Number To Transfer To: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, Try again: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Receiver = clsBankClient::Find(AccountNumber);
        _PrintClient(Receiver);

        _TransferAmount(Sender, Receiver);
	}
};

