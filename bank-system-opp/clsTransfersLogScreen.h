#pragma once
#include<iostream>
#include <iomanip>
#include <fstream>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransfersLogScreen : protected clsScreen
{
private: 
    static void _PrintRegisterTransferLogRecordLine(clsBankClient::stRegisterTransferLogRecord TransferLogRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << TransferLogRegisterRecord.DateTime;
        cout << "| " << setw(10) << left << TransferLogRegisterRecord.AccNumSender;
        cout << "| " << setw(10) << left << TransferLogRegisterRecord.AccNumReceiver;
        cout << "| " << setw(10) << left << TransferLogRegisterRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRegisterRecord.BalanceSender;
        cout << "| " << setw(10) << left << TransferLogRegisterRecord.BalanceReceiver;
        cout << "| " << setw(10) << left << TransferLogRegisterRecord.UserName;
    }

public:
    static void ShowTransferLogRegisterRecordsList() {

        vector <clsBankClient::stRegisterTransferLogRecord> vTransferLogRegisterRecords = clsBankClient::GetRegisterTransferLogRecords();
        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRegisterRecords.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t____________________________________________________________";
        cout << "________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(10) << "S.AccNum";
        cout << "| " << left << setw(10) << "D.AccNum";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(10) << "UserName";
        cout << setw(8) << left << "" << "\n\t____________________________________________________________";
        cout << "________________________________________________\n" << endl;

        if (vTransferLogRegisterRecords.size() == 0)
            cout << "\t\t\t\tNo Transfer Logins Available In the System!";
        else

            for (clsBankClient::stRegisterTransferLogRecord Record : vTransferLogRegisterRecords)
            {
                _PrintRegisterTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t____________________________________________________________";
        cout << "________________________________________________\n" << endl;

    }
};

