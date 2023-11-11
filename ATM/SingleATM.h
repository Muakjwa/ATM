#pragma once
#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"

using namespace std;

class SingleATM : public ATM {
public:
	SingleATM();
	SingleATM(int SerialNum, Bank* primaryBank);
};