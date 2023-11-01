#pragma once
#include <iostream>
#include <string>

using namespace std;

class ATM {
private:
	static int bankCnt;
	string bank[100];
	int serialNum;

public:
	ATM();
	ATM(int SerialNum);
	string getBankName();
	void addBank(string BankName);
	void setDeposit(int* moneyPage);
};