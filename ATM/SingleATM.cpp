#include <iostream>
#include <string>
#include "Bank.h"
#include "ATM.h"
#include "SingleATM.h"

using namespace std;

class Bank;
class ATM;

SingleATM::SingleATM(){
}

SingleATM::SingleATM(int SerialNum, Bank* primaryBank){
	setSerialNum(SerialNum);
	setPrimaryBank(primaryBank);
	set_balance(0, 0, 0, 0);
}