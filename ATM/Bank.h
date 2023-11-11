#pragma once
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class Account;

class Bank {
private:
	string BankName;
	int SerialNum;
	int AccountCnt;
	Account *accountArr[100];

public:
	Bank();
	Bank(string BankName, int SerialNum);
	string getName();
	int getSerialNum();
	int getAccountNum();
	Account* getAccountArr(int cnt);
};