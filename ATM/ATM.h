#pragma once
#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

class ATM {
private:
	static int bankCnt;
	Bank bank[100];
	int balance[4];
	int serialNum;
	string transHistory;

public:
	ATM();
	ATM(int SerialNum);
	string getBankName();
	void addBank(string BankName);
	void setDeposit(int* moneyPage);
	//balance�� moneyPage �־��ֱ�
	void deposit(int* moneyPage);
	void withdrawal(int* moneyPage);
	void transfer(Account sender, Account reciever, int money);
	void transfer(Account sender, Account reciever, int* moneyPage);
};