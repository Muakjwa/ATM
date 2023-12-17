#include "Account.h"
#include <iostream>
#include <string>
#include "User.h"
#include "Bank.h"

using namespace std;

class Account;
class Bank;

Account::Account() {

}

Account::Account(Bank* bank, User* user, long long int accountNum, long long int cardNum, int password) {
	this->bank = bank;
	this->user = user;
	this->accountNum = accountNum;
	this->cardNum = cardNum;
	this->password = password;
}

void Account::deposit(int cash) {
	balance += cash;
}

long long int Account::getBalance() {
	return balance;
}

void Account::withdrawal(int cash) {
	balance -= cash;
}

long long int Account::getCardNum() {
	return cardNum;
}

long long int Account::getAccountNum() {
	return accountNum;
}

string Account::getUserName() {
	return user->getUserName();
}
string Account::snapShot() {
	return "Hello";
	//½º³À¼¦ Ãâ·Â
}

int Account::getPassword() {
	return password;
}