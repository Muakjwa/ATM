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
	//bank �ø��� �ѹ��� ���¹�ȣ ���ļ� ����
}

void Account::deposit(int cash) {
	//balance�� cash �߰�
}

void Account::withdrawal(int cash) {
	//balance���� ����
}

void Account::setUser(User* set_user) {
	this->user = *set_user;
}

long long int Account::getCardNum() {
	return cardNum;
}

string Account::getName() {
	return user.getUserName();
	//����� �̸� ���?
}
string Account::snapShot() {
	return "Hello";
	//������ ���
}

int Account::getPassword() {
	return password;
}