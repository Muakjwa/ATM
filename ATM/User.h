#pragma once
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class User {
private:
	string name;
	Account accountArr[100];

public:
	User();
	User(string UserName);
	string getUserName();
	void setAccountArr(Account account);
	//accountArr에 append 해준다.
};