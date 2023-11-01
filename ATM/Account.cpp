#include "Account.h"
#include <iostream>
#include <string>

using namespace std;

Account::Account() {

}

Account::Account(Bank bank, User user, long long int accountNum, int balance = 0) {
	//bank 시리얼 넘버와 계좌번호 합쳐서 저장
}

void deposit(int cash) {
	//balance에 cash 추가
}

void withdrawal(int cash) {
	//balance에서 인출
}
string getName() {
	//사용자 이름 출력?
}
string snapShot() {
	//스냅샷 출력
}