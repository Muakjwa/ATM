#pragma once
#include "ATM.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Session.h"

using namespace std;


Session::Session() {

}


void Session::addTransaction(string cardNum, int amount, Account* target_account, string cash_or_check) {
	// (REQ2.4) Each transaction has a unique identifier (transCnt)
	string inform = to_string(transNum) + ". [Deposit " + cash_or_check + "] Card Number : " + cardNum + ", Deposit amount : " + to_string(amount) + ", Balance after Deposit : " + to_string(target_account->getBalance());
	transHistory.push_back(inform);
	sessionTransaction += inform + "\n";
	tempSessionTransaction += inform + "\n";
	transNum += 1;
}

void Session::addTransaction(string cardNum, int amount, Account* source_account) {
	// (REQ2.4) Each transaction has a unique identifier (transCnt)
	string inform = to_string(transNum) + ". [Withdrawal] Card Number : " + cardNum + ", Withdrawal amount : " + to_string(amount) + ", Balance after Withdrawal : " + to_string(source_account->getBalance());
	transHistory.push_back(inform);
	sessionTransaction += inform + "\n";
	tempSessionTransaction += inform + "\n";
	transNum += 1;
}

// ¼Û±Ý (Çö±Ý)
void Session::addTransaction(string cardNum, int amount, Account* target_account, int fee) {
	// (REQ2.4) Each transaction has a unique identifier (transCnt)
	string inform = to_string(transNum) + ". [Withdrawal] Card Number : " + cardNum + ", Reciever Account Number : " + to_string(target_account->getAccountNum()) + ", Transfer amount : " + to_string(amount) + ", Fee : " + to_string(fee);
	transHistory.push_back(inform);
	sessionTransaction += inform + "\n";
	tempSessionTransaction += inform + "\n";
	transNum += 1;
}

// ¼Û±Ý (°èÁÂ->°èÁÂ)
void Session::addTransaction(string cardNum, int amount, Account* source_account, Account* target_account, int fee) {
	// (REQ2.4) Each transaction has a unique identifier (transCnt)
	string inform = to_string(transNum) + ". [Withdrawal] Card Number : " + cardNum + ", Sender Account Number : " + to_string(source_account->getAccountNum()) + ", Reciever Account Number : " + to_string(target_account->getAccountNum()) + ", Transfer amount : " + to_string(amount) + ", Fee : " + to_string(fee);
	transHistory.push_back(inform);
	sessionTransaction += inform + "\n";
	tempSessionTransaction += inform + "\n";
	transNum += 1;
}

string Session::printTransaction() {
	/*string trans = "";
	for (int i = 0; i < transNum; i++) {
		trans += (transHistory[i] + "\n");
	}*/
	return sessionTransaction;
}