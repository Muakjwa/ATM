#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Bank.h"

using namespace std;

class Account{
private:
	User user;
	Bank bank;
	long long int accountNum;
	long long int balance;
	string accountHistory;

public:
	Account();
	Account(Bank bank, User user, long long int accountNum, int balance = 0);
	void deposit(int cash);
	void withdrawal(int cash);
	string getName();
	string snapShot();
};