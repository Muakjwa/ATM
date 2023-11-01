#pragma once
#include <iostream>
#include <string>

using namespace std;

class Card {
private:
	string BankName;
	int SerialNum;

public:
	Card();
	Card(string BankName, int SerialNum);
	string getName();
	int getSerialNum();
};