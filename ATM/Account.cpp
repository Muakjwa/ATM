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

Account::Account(Bank* bank, User* user, long long int accountNum, int password) {
	//bank 시리얼 넘버와 계좌번호 합쳐서 저장
}

void Account::deposit(int cash) {
	//balance에 cash 추가
}

void Account::withdrawal(int cash) {
	//balance에서 인출
}

void Account::setUser(User* set_user) {
	this->user = *set_user;
}

string Account::getName() {
	return user.getUserName();
	//사용자 이름 출력?
}
string Account::snapShot() {
	return "Hello";
	//스냅샷 출력
}