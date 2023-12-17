#pragma once
#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"

using namespace std;

class MultiATM : public ATM {
public:
	MultiATM();
	MultiATM(string SerialNum, Bank* primaryBank, bool bilingual);
	void addSubBank(Bank* BankName);
};