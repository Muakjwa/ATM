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
	//bank �ø��� �ѹ��� ���¹�ȣ ���ļ� ����
}

void Account::deposit(int cash) {
	//balance�� cash �߰�
}

void Account::withdrawal(int cash) {
	//balance���� ����
}
string Account::getName() {
	//����� �̸� ���?
}
string Account::snapShot() {
	//������ ���
}