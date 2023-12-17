#pragma once
#include <iostream>
#include <string>
#include "Account.h"
#include <vector>

using namespace std;

class Account;

class Bank {
private:
	string BankName;
	int SerialNum;
	vector<Account*> accountArr;

public:
	Bank();
	Bank(string BankName, int SerialNum);
	string getName();
	int getSerialNum();
	int getAccountNum();
	void addAccount(Account* account);
	Account* getAccountArr(int cnt);
};