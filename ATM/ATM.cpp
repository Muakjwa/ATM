#pragma once
#include "ATM.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Account.h"

using namespace std;

void states(string statement) {
	cout << "*-------------------- " << statement << " --------------------*" << endl;
}


ATM::ATM() {
	set_balance(0, 0, 0, 0);
	transCnt += 1;
	sessionTransaction = "";
}

ATM::ATM(string SerialNum, Bank* primaryBank) {
	setSerialNum(SerialNum);
	setPrimaryBank(primaryBank);
	set_balance(0, 0, 0, 0);
	transCnt += 1;
	sessionTransaction = "";
}

Bank* ATM::getPrimaryBank() {
	return primaryBank;
}

Bank* ATM::getSubBank(int cnt) {
	return subBank[cnt];
}

long long int ATM::getBalance() {
	return 1000 * balance[0] + 5000 * balance[1] + 10000 * balance[2] + 50000 * balance[3];
}

void ATM::setPrimaryBank(Bank* bank) {
	primaryBank = bank;
}

void ATM::setBilingual(bool bilingual) {
	this->bilingual = bilingual;
}

bool ATM::getBilingual() {
	return bilingual;
}

void ATM::deposit(int moneyPage[]) {
	for (int i = 0; i < 4; i++) {
		this->balance[i] += moneyPage[i];
	}
}

bool ATM::calWithdrawal(int money[]) {
	for (int i = 3; i >= 0; i--) {
		if (balance[i] < money[i]) {
			// 인출이 불가능할 때 true return
			return true;
		}
	}
	return false;
}

void ATM::withdrawal(int money[]) {
	for (int i = 3; i >= 0; i--) {
		balance[i] -= money[i];
	}
}

string ATM::getSerialNum() {
	return serialNum;
}

int ATM::getSubBankNum() {
	return subBank.size();
}

void ATM::set_balance(int a, int b, int c, int d) {
	this->balance[0] = a;
	this->balance[1] = b;
	this->balance[2] = c;
	this->balance[3] = d;
}

void ATM::setSerialNum(string serialNum) {
	this->serialNum = serialNum;
}

void ATM::printBalanceCnt() {
	cout << "(";
	if (balance[3] != 0) {
		cout << "50000원X" << balance[3] << "장";
	}
	if (balance[2] != 0) {
		if (balance[3] > 0) {
			cout << ", ";
		}
		cout << "10000원X" << balance[2] << "장";
	}
	if (balance[1] != 0) {
		if (balance[3] + balance[2] > 0) {
			cout << ", ";
		}
		cout << "5000원X" << balance[1] << "장";
	}
	if (balance[0] != 0) {
		if (balance[3] + balance[2] + balance[1] > 0) {
			cout << ", ";
		}
		cout << "1000원X" << balance[0] << "장";
	}
	cout << ")" << endl;
}




void ATM::updateTransaction(string trans) {
	sessionTransaction += trans;
}
void ATM::printTransaction() {
	cout << sessionTransaction << endl;
}