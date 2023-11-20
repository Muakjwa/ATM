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
	int balance[4] = { 0,0,0,0 };
	int serialNum;
	string transHistory;

public:
	ATM();
	ATM(int SerialNum, Bank* primaryBank);
	Bank getPrimaryBank();
	Bank getSubBank(int cnt);
	long long int getBalance();
	void setPrimaryBank(Bank* bank);
	//balance에 moneyPage 넣어주기
	void deposit(int moneyPage[]);
	bool calWithdrawal(int money);
	void withdrawal(int money);
	void transfer(Account sender, Account reciever, int money);
	void transfer(Account sender, Account reciever, int* moneyPage);
	int getSerialNum();
	int getSubBankNum();
	void set_balance(int a, int b, int c, int d);
	void setSerialNum(int serialNum);
};