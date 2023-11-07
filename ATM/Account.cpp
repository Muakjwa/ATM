#include "Account.h"
#include <iostream>
#include <string>
#include "User.h"
#include "Bank.h"

using namespace std;

class Account;

Account::Account() {

}

Account::Account(Bank bank, User user, long long int accountNum, int password, int balance = 0) {
	//bank 시리얼 넘버와 계좌번호 합쳐서 저장
}

void Account::deposit(int cash) {
	//balance에 cash 추가
}

void Account::withdrawal(int cash) {
	//balance에서 인출
}
string Account::getName() {
	//사용자 이름 출력?
}
string Account::snapShot() {
	//스냅샷 출력
}