#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Bank.h"
#include "ATM.h"

using namespace std;

class Session {
private:
	static int transNum;
	string sessionTransaction;
	string tempSessionTransaction;
	vector<string> transHistory;
public:
	// 세션 설정
	Session();

	// Polymorphism
	// 입,출금, 송금 내역 Transaction 저장

	// 입금
	void addTransaction(string cardNum, int amount, Account* target_account, string cash_or_check);
	// 출금
	void addTransaction(string cardNum, int amount, Account* source_account);
	// 송금 (현금)
	void addTransaction(string cardNum, int amount, Account* target_account, int fee);
	// 송금 (계좌->계좌)
	void addTransaction(string cardNum, int amount, Account* source_account, Account* target_account, int fee);
	string printTransaction();

	void sessionKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub);
	int sessionDepositKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub);
	int sessionWithDrawalKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub, int& withdrawalNum);
	int sessionTransferKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub);

	void sessionEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub);
	int sessionDepositEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub);
	int sessionWithDrawalEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub, int& withdrawalNum);
	int sessionTransferEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub);
};