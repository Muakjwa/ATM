#include "User.h"
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class User;

User::User() {

}

User::User(string UserName) {
	this->name = UserName;
}

string User::getUserName() {
	return this->name;
}

void User::setAccountArr(Account account) {
	//this->accountArr[accountCnt] = account;
	accountCnt += 1;
}