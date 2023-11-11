#pragma once
#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"

using namespace std;

class MultiATM : public ATM {
public:
	MultiATM();
	MultiATM(int SerialNum, Bank* primaryBank);
	void addSubBank(Bank* BankName);
};