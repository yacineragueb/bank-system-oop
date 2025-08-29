#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "../string/clsString.h" // You Can get this lib from https://github.com/yacineragueb/String-lib-cpp

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	struct stRegisterTransferLogRecord;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stoi(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out); // overwrite

		string DataLine;

		if (MyFile.is_open()) {
			for (clsBankClient &C : vClients)
			{
				if (C.MarkedForDelete == false) {

					// We only write records that are not marked for delete.
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static stRegisterTransferLogRecord _ConvertRegisterTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stRegisterTransferLogRecord RegisterTransferLogRecord;

		vector<string> vRegisterTransferLogRecordDataLine;
		vRegisterTransferLogRecordDataLine = clsString::Split(Line, Seperator);

		RegisterTransferLogRecord.DateTime = vRegisterTransferLogRecordDataLine[0];
		RegisterTransferLogRecord.AccNumSender = vRegisterTransferLogRecordDataLine[1];
		RegisterTransferLogRecord.AccNumReceiver = vRegisterTransferLogRecordDataLine[2];
		RegisterTransferLogRecord.Amount = stoi(vRegisterTransferLogRecordDataLine[3]);
		RegisterTransferLogRecord.BalanceSender = stoi(vRegisterTransferLogRecordDataLine[4]);
		RegisterTransferLogRecord.BalanceReceiver = stoi(vRegisterTransferLogRecordDataLine[5]);
		RegisterTransferLogRecord.UserName = vRegisterTransferLogRecordDataLine[6];

		return RegisterTransferLogRecord;
	}

	string _PrepareTransferLogRecord(double Amount, clsBankClient Receiver, string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = clsDate::GetSystemDateTimeString() + Seperator + AccountNumber() + Seperator + Receiver.AccountNumber() + Seperator + to_string(Amount)
			+ Seperator + to_string(AccountBalance) + Seperator + to_string(Receiver.AccountBalance) + Seperator + UserName;
		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient Receiver, string UserName)
	{

		string stDataLine = _PrepareTransferLogRecord(Amount, Receiver, UserName);

		fstream MyFile;
		MyFile.open("RegisterTransferLog.txt", ios::out | ios::app);


		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();

		}
	}

public:

	struct stRegisterTransferLogRecord {
		string DateTime;
		string UserName;
		string AccNumSender;
		string AccNumReceiver;
		double Amount;
		double BalanceSender;
		double BalanceReceiver;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	string GetPinCode() {
		return _PinCode;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	float GetAccountBalance() {
		return _AccountBalance;
	}

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	bool GetMarkedForDelete() {
		return _MarkedForDelete;
	}

	void SetMarkedForDelete(bool MarkedForDelete) {
		_MarkedForDelete = MarkedForDelete;
	}

	__declspec(property(get = GetMarkedForDelete, put = SetMarkedForDelete)) bool MarkedForDelete;

	static clsBankClient Find(string AccountNumber) {
		// vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}

				// vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		// vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("", ios::in); // Read Mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}

				// vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};

	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;

		case enMode::UpdateMode:
			_Update();

			return enSaveResults::svSucceeded;

		case enMode::AddNewMode:
			// This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFaildAccountNumberExists;
			}
			else {
				_AddNew();

				// We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector<clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == _AccountNumber) {
				C._MarkedForDelete = true;
				_SaveClientsDataToFile(_vClients);
				*this = _GetEmptyClientObject();
				return true;
			}
		}

		return false;
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalances = 0;

		for (clsBankClient Client : vClients) {
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	static vector <stRegisterTransferLogRecord> GetRegisterTransferLogRecords() {
		vector <stRegisterTransferLogRecord> vRegisterTransferLogRecords;

		fstream MyFile;
		MyFile.open("RegisterTransferLog.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				stRegisterTransferLogRecord Record = _ConvertRegisterTransferLogLineToRecord(Line);

				vRegisterTransferLogRecords.push_back(Record);
			}

			MyFile.close();

		}

		return vRegisterTransferLogRecords;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}
};

