#include "User.h"
#include <iostream>
#include <string>

using namespace std;

User::User() {

}

User::User(string UserName) {
	this->name = UserName;
}

string User::getUserName() {
	cout << this->name << endl;
	return this->name;
}