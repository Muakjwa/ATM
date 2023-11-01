#pragma once
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class Bank {
private:
	string BankName;
	int SerialNum;
	Account accountArr[100];

public:
	Bank();
	Bank(string BankName, int SerialNum);
	string getName();
	int getSerialNum();
};