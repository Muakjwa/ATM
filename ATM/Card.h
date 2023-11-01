#pragma once
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class Card {
private:
	friend class Account;
public:
	Card();
};