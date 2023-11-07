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
	return bank->getName();
}

void ATM::addBank(string BankName) {
	//this->bank[this->bankCnt] = BankName;
}

void ATM::setDeposit(int* moneyPage) {

}

void ATM::deposit(int* moneyPage) {

}

void ATM::withdrawal(int* moneyPage) {

}

void ATM::transfer(Account sender, Account reciever, int money) {

}

void ATM::transfer(Account sender, Account reciever, int* moneyPage) {

}