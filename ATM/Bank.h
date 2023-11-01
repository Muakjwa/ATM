#pragma once
#include <iostream>
#include <string>

using namespace std;

class Bank {
private:
	string BankName;
	int SerialNum;

public:
	Bank();
	Bank(string BankName, int SerialNum);
	string getName();
	int getSerialNum();
};