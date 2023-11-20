#include "ATM.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Account.h"
// 유선우 화이팅!
using namespace std;

int ATM::subBankCnt = 0;

ATM::ATM() {
	set_balance(0, 0, 0, 0);
}

ATM::ATM(int SerialNum, Bank* primaryBank) {
	setSerialNum(SerialNum);
	setPrimaryBank(primaryBank);
	//set_balance(0, 0, 0, 0);
}

Bank ATM::getPrimaryBank() {
	return primaryBank;
}

Bank ATM::getSubBank(int cnt) {
	return subBank[cnt];
}

long long int ATM::getBalance() {
	return 1000 * balance[0] + 5000 * balance[1] + 10000 * balance[2] + 50000 * balance[3];
}

void ATM::setPrimaryBank(Bank* bank) {
	primaryBank = *bank;
}

void ATM::deposit(int moneyPage[]) {
	cout << this->balance[0] << endl;
	//for (int i = 0; i < 4; i++) {
	//	this->balance[i] += moneyPage[i];
	//}
}

bool ATM::calWithdrawal(int money) {
	int arr[4] = { 1000, 5000, 10000, 50000 };
	int balanceArr[4] = { 0, };
	for (int i = 3; i >= 0; i--) {
		balanceArr[i] = min((int)(money / arr[i]), balance[i]);
		money -= balanceArr[i] * arr[i];
	}
	if (money == 0) {
		return true;
	}
	else {
		return false;
	}
}

void ATM::withdrawal(int money) {
	int arr[4] = { 1000, 5000, 10000, 50000 };
	int balanceArr[4] = { 0, };
	for (int i = 3; i >= 0; i--) {
		balanceArr[i] = min((int)(money / arr[i]), balance[i]);
		money -= balanceArr[i] * arr[i];
		balance[i] -= balanceArr[i];
	}
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

void ATM::set_balance(int a, int b, int c, int d) {
	this->balance[0] = a;
	this->balance[1] = b;
	this->balance[2] = c;
	this->balance[3] = d;
}

void ATM::setSerialNum(int serialNum) {
	this->serialNum = serialNum;
}