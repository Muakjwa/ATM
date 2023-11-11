#include "ATM.h"
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

int ATM::subBankCnt = 0;

ATM::ATM() {}

Bank ATM::getPrimaryBank() {
	return primaryBank;
}

Bank ATM::getSubBank(int cnt) {
	return subBank[cnt];
}

void ATM::setPrimaryBank(string BankName) {
	//this->primaryBank = BankName;
}

void ATM::deposit(int moneyPage[]) {
	for (int i = 0; i < 4; i++) {
		balance[i] += moneyPage[i];
	}
}

void ATM::withdrawal(int* moneyPage) {

}

void ATM::transfer(Account sender, Account reciever, int money) {

}

void ATM::transfer(Account sender, Account reciever, int* moneyPage) {

}

int ATM::getSerialNum() {
	return serialNum;
}

int ATM::getSubBankNum() {
	return subBankCnt;
}