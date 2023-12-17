#pragma once
#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"

using namespace std;

class SingleATM : public ATM {
public:
	SingleATM();
	SingleATM(string SerialNum, Bank* primaryBank, bool bilingual);
};