#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"
#include "MultiATM.h"

using namespace std;

class Bank;
class ATM;

MultiATM::MultiATM() {
}

MultiATM::MultiATM(string SerialNum, Bank* primaryBank, bool bilingual) {
	setBilingual(bilingual);
	setSerialNum(SerialNum);
	setPrimaryBank(primaryBank);
}

void MultiATM::addSubBank(Bank* BankName) {
	this->subBank.push_back(BankName);
}