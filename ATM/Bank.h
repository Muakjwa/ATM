#pragma once
#include <iostream>
#include <string>

using namespace std;

class Account;

class Bank {
private:
	string BankName;
	int SerialNum;
	//Account accountArr[100];

public:
	Bank();
	Bank(string BankName, int SerialNum);
	string getName();
	int getSerialNum();
};