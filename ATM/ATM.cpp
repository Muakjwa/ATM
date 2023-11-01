#include "ATM.h"
#include <iostream>
#include <string>

using namespace std;

int ATM::bankCnt = 0;

ATM::ATM() {

}

ATM::ATM(int SerialNum) {
	this->serialNum = SerialNum;
}

string ATM::getBankName() {
	return bank[0];
}

void ATM::addBank(string BankName) {
	this->bank[this->bankCnt] = BankName;
}

void ATM::setDeposit(int* moneyPage) {

}