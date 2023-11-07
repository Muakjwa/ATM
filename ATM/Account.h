#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Bank.h"
#include "Card.h"

using namespace std;

// git stash && git pull origin master && git stash pop

class User;
class Bank;

class Account{
private:
	friend class Card;
	User user;
	Bank bank;
	long long int accountNum;
	long long int balance = 0;
	int password;
	string accountHistory;

public:
	Account();
	Account(Bank* bank, User* user, long long int accountNum, int password);
	//������ ������ ��, �ش� User�� accountArr�� Account ��ü�� �����ؾ���.
	void deposit(int cash);
	void withdrawal(int cash);
	void setUser(User *set_user);
	string getName();
	string snapShot();
};