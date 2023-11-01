#pragma once
#include <iostream>
#include <string>

using namespace std;

class User {
private:
	string name;

public:
	User();
	User(string UserName);
	string getUserName();
};