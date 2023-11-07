#include "User.h"
#include <iostream>
#include <string>

using namespace std;

class User;

User::User() {

}

User::User(string UserName) {
	this->name = UserName;
}

string User::getUserName() {
	cout << this->name << endl;
	return this->name;
}

void User::setAccountArr(Account account) {
	this->accountArr[accountCnt] = account;
	accountCnt += 1;
}