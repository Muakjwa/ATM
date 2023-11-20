#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"
#include "MultiATM.h"

using namespace std;

class Bank;
class ATM;

MultiATM::MultiATM() {
	set_balance(0, 0, 0, 0);
}

MultiATM::MultiATM(int SerialNum, Bank* primaryBank) {
	setSerialNum(SerialNum);
	setPrimaryBank(primaryBank);
	set_balance(0, 0, 0, 0);
}

void MultiATM::addSubBank(Bank* BankName) {
	this->subBank[subBankCnt] = *BankName;
	subBankCnt++;
}