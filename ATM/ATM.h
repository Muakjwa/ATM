#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Bank.h"

using namespace std;

class ATM {
protected:
	Bank* primaryBank;
	vector<Bank*> subBank;
	int balance[4] = { 0,0,0,0 };
	string serialNum;
	string sessionTransaction;
	bool bilingual;
	int transCnt;

public:
	ATM();
	ATM(string SerialNum, Bank* primaryBank);
	Bank* getPrimaryBank();
	Bank* getSubBank(int cnt);
	long long int getBalance();
	void setPrimaryBank(Bank* bank);
	void setBilingual(bool bilingual);
	bool getBilingual();
	//balance에 moneyPage 넣어주기
	void deposit(int moneyPage[]);
	bool calWithdrawal(int money[]);
	void withdrawal(int money[]);
	string getSerialNum();
	int getSubBankNum();
	void set_balance(int a, int b, int c, int d);
	void setSerialNum(string serialNum);
	void printBalanceCnt();
	void updateTransaction(string trans);
	void printTransaction();

};