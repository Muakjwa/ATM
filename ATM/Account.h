#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Bank.h"

class Bank;

using namespace std;

class Account{
private:
	User *user;
	Bank *bank;
	long long int accountNum;
	long long int cardNum;
	long long int balance = 0;
	int password;
	string accountHistory;

public:
	Account();
	Account(Bank* bank, User* user, long long int accountNum, long long int cardNum, int password);
	//생성자 실행할 때, 해당 User의 accountArr에 Account 객체도 저장해야함.
	void deposit(int cash);
	long long int getBalance();
	void withdrawal(int cash);
	void setUser(User *set_user);
	long long int getCardNum();
	string getName();
	string snapShot();
	int getPassword();
};