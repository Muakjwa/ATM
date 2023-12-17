#include "Bank.h"
#include "Account.h"
#include <iostream>
#include <string>

class Account;

using namespace std;

Bank::Bank() {
}

Bank::Bank(string BankName, int SerialNum) {
	this->BankName = BankName;
	this->SerialNum = SerialNum;
}

string Bank::getName() {
	return this->BankName;
}

int Bank::getSerialNum() {
	return this->SerialNum;
}

int Bank::getAccountNum() {
	return accountArr.size();
}

void Bank::addAccount(Account* account) {
	accountArr.push_back(account);
}

Account* Bank::getAccountArr(int cnt) {
	return accountArr[cnt];
}