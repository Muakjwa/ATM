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
	long long int balance;
	int password;
	string accountHistory;

public:
	Account();
	Account(Bank bank, User user, long long int accountNum, int password, int balance = 0);
	//������ ������ ��, �ش� User�� accountArr�� Account ��ü�� �����ؾ���.
	void deposit(int cash);
	void withdrawal(int cash);
	string getName();
	string snapShot();
};