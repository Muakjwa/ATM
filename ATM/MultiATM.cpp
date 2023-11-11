#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"
#include "MultiATM.h"

using namespace std;

class Bank;
class ATM;

MultiATM::MultiATM() {
	this->balance[4] = { 0, };
}

MultiATM::MultiATM(int SerialNum, Bank* primaryBank) {
	this->serialNum = SerialNum;
	this->primaryBank = *primaryBank;
	this->balance[4] = { 0, };
}

void MultiATM::addSubBank(Bank* BankName) {
	this->subBank[subBankCnt] = *BankName;
	subBankCnt++;
}