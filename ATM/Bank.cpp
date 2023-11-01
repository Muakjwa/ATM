#include "Bank.h"
#include <iostream>
#include <string>

using namespace std;

Bank::Bank() {

}

Bank::Bank(string BankName, int SerialNum) {
	this->BankName = BankName;
	this->SerialNum = SerialNum;
}

string Bank::getName() {
	cout << this->BankName << endl;
	return this->BankName;
}

int Bank::getSerialNum() {
	cout << this->SerialNum << endl;
	return this->SerialNum;
}