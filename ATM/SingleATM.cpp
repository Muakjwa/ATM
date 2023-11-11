#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"
#include "SingleATM.h"

using namespace std;

class Bank;
class ATM;

SingleATM::SingleATM(){
	this->balance[4] = { 0, };
}

SingleATM::SingleATM(int SerialNum, Bank* primaryBank){
	this->serialNum = SerialNum;
	this->primaryBank = *primaryBank;
	this->balance[4] = {0,};
}