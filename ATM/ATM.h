#pragma once
#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

class ATM {
protected:
	static int subBankCnt;
	Bank primaryBank;
	Bank subBank[100];
	int balance[4];
	int serialNum;
	string transHistory;

public:
	ATM();
	Bank getPrimaryBank();
	Bank getSubBank(int cnt);
	void setPrimaryBank(string BankName);
	//balance에 moneyPage 넣어주기
	void deposit(int moneyPage[]);
	void withdrawal(int* moneyPage);
	void transfer(Account sender, Account reciever, int money);
	void transfer(Account sender, Account reciever, int* moneyPage);
	int getSerialNum();
	int getSubBankNum();
};