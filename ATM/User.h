#pragma once
#include <iostream>
#include <string>

using namespace std;

class Account;

class User {
private:
	int accountCnt = 0;
	string name;
	//Account accountArr[100];

public:
	User();
	User(string UserName);
	string getUserName();
	void setAccountArr(Account account);
	//accountArr에 append 해준다.
};