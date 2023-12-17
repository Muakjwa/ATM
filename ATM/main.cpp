#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ATM.h"
#include "Bank.h"
#include "User.h"
#include "Account.h"
#include "SingleATM.h"
#include "MultiATM.h"
#include "Session.h"

class ATM;
class Bank;
class User;
class Account;
class Session;

using namespace std;

static int BankCnt = 0;
static int UserCnt = 0;
static int AccountCnt = 0;
static int ATMCnt = 0;
// STL vector 사용
vector<Account*> AccountArr(100);
vector<ATM*> ATMArr(100);

int Session::transNum = 1;


// Admin 카드 번호 : 0000

void state(string statement) {
    cout << "*-------------------- " << statement << " --------------------*" << endl << endl;
}


// ------------------------------  ATM, User balance 확인  --------------------------------
void snapshot() {
    state("SnapShot");
    for (int i = 0; i < AccountCnt; i++) {
        cout << "[Account " << i + 1 << "] Name : " << AccountArr[i]->getUserName() << ", Account Number : " << AccountArr[i]->getAccountNum()<< " Balance : " << AccountArr[i]->getBalance() << endl;
    }
    for (int i = 0; i < ATMCnt; i++) {
        cout << "[ATM " << i + 1 << "] Remaining Cash : " << ATMArr[i]->getBalance() << "  ";
        ATMArr[i]->printBalanceCnt();
    }
    state("SnapShot Finish");
}


// 세션 설정 (한국어)
void Session::sessionKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub) {
    tempSessionTransaction = "";
    int withdrawalNum = 0;
    while (1) {
        char operation;
        cout << "1. 입금" << endl;
        cout << "2. 출금" << endl;
        cout << "3. 송금" << endl;
        cin >> operation;
        cout << endl;

        // (REQ10.1) SnapShot
        if (operation == 'x' or operation == 'X') {
            snapshot();
        }

        // ATM 종료!
        if (operation == 'c' or operation == 'C') {
            state("ATM이 종료됩니다.");
            break;
        }

        // (REQ2.2) 비정상적인 작동이나 사용자가 종료하면 입,출,송금에서 1을 return해 ATM 종료 (C입력 받으면 세션 종료)
        if (operation == '1') {
            int stop = sessionDepositKorean(ChosenATM, userAccount, cardNum, isSub);
            if (stop == 1) {
                state("ATM이 종료됩니다.");
                break;
            }
        }
        else if (operation == '2') {
            int stop = sessionWithDrawalKorean(ChosenATM, userAccount, cardNum, isSub, withdrawalNum);
            if (stop == 1) {
                state("ATM이 종료됩니다.");
                break;
            }
        }
        else if (operation == '3') {
            int stop = sessionTransferKorean(ChosenATM, userAccount, cardNum, isSub);
            if (stop == 1) {
                state("ATM이 종료됩니다.");
                break;
            }
        }
    }
    // (REQ2.3) summary of all transactions is displayed
    state("Session Transaction");
    cout << tempSessionTransaction << endl;
    ChosenATM->updateTransaction(tempSessionTransaction);
    state("Session Transaction Finish");

}

// 입금 (한국어)
int Session::sessionDepositKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub) {
    // cash = 1 , check = 2
    char cashORcheck;

    // (REQ4.1) ATM take either cash or check from a user
    cout << "현금을 사용할지 수표를 사용할지 골라주세요." << endl;
    cout << "1. 현금" << endl;
    cout << "2. 수표" << endl;
    cin >> cashORcheck;

    // (REQ10.1) SnapShot
    if (cashORcheck == 'x' or cashORcheck == 'X') {
        snapshot();
    }

    // ATM 종료 
    if (cashORcheck != '1' and cashORcheck != '2') {
        cout << "잘못된 입력입니다." << endl;
        return 1;
    }
    if (cashORcheck == 'C' or cashORcheck == 'c') {
        return 1;
    }

    if (cashORcheck == '1') {
        cout << "현금을 입금해주세요. " << ChosenATM->getPrimaryBank()->getName() << "은행이 아니면 수수료 1000원이 부과됩니다." << endl;
        // Deposit 입력받는다.
        int moneyPage[4];
        cout << "50,000 : ";
        cin >> moneyPage[3];
        cout << "10,000 : ";
        cin >> moneyPage[2];
        cout << "5,000 : ";
        cin >> moneyPage[1];
        cout << "1,000 : ";
        cin >> moneyPage[0];
        int totalCash = 50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * moneyPage[0];

        // (REQ4.2) ATM display error. Number of inserted cash exceed.
        if (moneyPage[0] + moneyPage[1] + moneyPage[2] + moneyPage[3] > 50) {
            state("너무 많은 현금이 입금되었습니다. 입금 실패!!");
            return 1;
        }
        else {
            // (REQ1.8) Non-primary bank deposit fee : 1000
            // (REQ1.8) primary bank deposit fee : 0
            // (REQ4.3) Transaction updates bank account, too.
            // (REQ4.4) Deposit fee is charged.
            userAccount->deposit(50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * (moneyPage[0] - (int)isSub));
            // (REQ4.5) Deposit increase available cash in ATM.
            ChosenATM->deposit(moneyPage);
            this->addTransaction(cardNum, totalCash, userAccount, "Cash");
            state("입금이 완료되었습니다.");
            return 0;
        }
    }
    else {
        string check;
        int totalCheck = 0;
        int checkNum = 0;
        cout << "각 수표의 값을 입력해주세요. C가 입력되면 입금이 종료됩니다." << endl;
        while (1) {
            // Exception Handling (예외 처리)
            try {
                cin >> check;
                // (REQ10.1) SnapShot
                if (check == "x" or check == "X") {
                    snapshot();
                }
                if (check == "C" or check == "c") {
                    throw check;
                }
                // (REQ1.10) 수표는 100,000원 이상의 금액이어야한다.
                if ((long long int)stoll(check) < 100000) {
                    throw (long long int)stoll(check);
                }
                totalCheck += (long long int)stoll(check);
                checkNum++;
            }
            catch (long long int check) {
                state("입금하신 금액은 수표에 맞지 않는 금액입니다. 100,000원 이상의 수표를 입금해주세요.");
                continue;
            }
            catch (string check) {
                state("입금이 완료되었습니다.");
                break;
            }
        }

        // (REQ4.2) ATM display error. Number of inserted check exceed.
        if (checkNum > 30) {
            state("너무 많은 수표가 입금되었습니다. 입금 실패!!");
            return 1;
        }
        else {
            // (REQ4.3) Transaction updates bank account, too.
            // (REQ4.4) Deposit fee is charged.
            // (REQ4.6) Deposit check do not increase available cash in ATM.
            userAccount->deposit(totalCheck - 1000 * (int)isSub);
            this->addTransaction(cardNum, totalCheck, userAccount, "Check");
            return 0;
        }
    }
}

// 출금 (한국어)
int Session::sessionWithDrawalKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub, int& withdrawalNum) {
    // (REQ5.6) 해당 세션에서 3번 출금한 경우 출금 불가능
    if (withdrawalNum >= 3) {
        cout << "해당 세션에서 더 이상 출금이 불가능합니다." << endl << endl;
        return 0;
    }

    int moneyPage[4] = { 0, };
    cout << "###(주은행은 1000원 서브은행은 2000원의 수수료가 자동으로 부과됩니다.)###" << endl;
    // (REQ5.1) ATM ask a user to enter the amount of fund to withdraw
    cout << "출금할 금액을 입력해주세요 : " << endl;
    cout << "50,000 : ";
    cin >> moneyPage[3];
    cout << "10,000 : ";
    cin >> moneyPage[2];
    cout << "5,000 : ";
    cin >> moneyPage[1];
    cout << "1,000 : ";
    cin >> moneyPage[0];

    int total_money = 50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * moneyPage[0];

    // (REQ5.7) 500,000원 이상의 금액은 출금 불가능
    if (total_money > 500000) {
        cout << "한번의 거래에서 500,000원 이상의 금액은 출금이 불가능합니다." << endl << endl;
        return 1;
    }
    // (REQ5.2) ATM이 해당 금액을 출금할 경우의 수가 안될 경우 출금 불가능
    else if (ChosenATM->calWithdrawal(moneyPage)) {
        cout << "ATM기가 현재 보유한 금액 이상의 출금이 불가능합니다." << endl << endl;
        return 1;
    }
    // (REQ1.8) primary bank withdrawal fee : 1000
    // (REQ1.8) Non-primary bank withdrawal fee : 2000
    // (REQ5.2) 계좌에 돈이 충분하지 않으면 에러 출력
    else if (userAccount->getBalance() < total_money + 1000 * (1 + (int)isSub)) {
        cout << "계좌에 보유한 금액 이상의 금액은 출금이 불가능합니다." << endl << endl;
        return 1;
    }
    else {
        // (REQ5.3) Transaction is reflected to the bank account.
        // (REQ5.4) 출금할 때 수수료 부과 (주은행이면 1000원 sub은행이면 2000원)
        userAccount->withdrawal(total_money + 1000 * (1 + (int)isSub));
        // (REQ5.5) Withdrawal lower available cash in ATM.
        ChosenATM->withdrawal(moneyPage);
        this->addTransaction(cardNum, total_money, userAccount);
        withdrawalNum += 1;
        state("출금이 완료되었습니다.");
        return 0;
    }
}

// 송금 (한국어)
int Session::sessionTransferKorean(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub) {
    // (REQ6.1) 사용자에게 transfer type을 물어본다.
    char transfer_type;
    // Exception Handling (예외 처리)
    try {
        cout << "1. 현금 전송" << endl;
        cout << "2. 계좌 잔액 전송" << endl;
        cin >> transfer_type;
        // (REQ10.1) SnapShot
        if (transfer_type == 'x' or transfer_type == 'X') {
            snapshot();
        }
        if (transfer_type != '1' and transfer_type != '2') {
            throw(transfer_type);
        }
    }
    catch (char transfer_type) {
        cout << transfer_type << "은 잘못된 입력입니다." << endl;
        return 1;
    }

    // (REQ6.2) 전송받을 사람의 account number는 항상 확인한다.
    long long int accountNum;
    Account* reciever = ChosenATM->getPrimaryBank()->getAccountArr(0);
    bool exist = false;
    bool recieverPrimary = false;
    cout << "송금받을 계좌의 계좌번호를 입력해주세요." << endl;
    cin >> accountNum;
    for (int i = 0; i < ChosenATM->getPrimaryBank()->getAccountNum(); i++) {
        if (accountNum == ChosenATM->getPrimaryBank()->getAccountArr(i)->getAccountNum()) {
            reciever = ChosenATM->getPrimaryBank()->getAccountArr(i);
            exist = true;
            recieverPrimary = true;
        }
    }
    for (int i = 0; i < ChosenATM->getSubBankNum(); i++) {
        for (int j = 0; j < ChosenATM->getSubBank(i)->getAccountNum(); j++) {
            if (accountNum == ChosenATM->getSubBank(i)->getAccountArr(j)->getAccountNum()) {
                reciever = ChosenATM->getSubBank(i)->getAccountArr(j);
                exist = true;
            }
        }
    }
    // 틀리면 ATM 종료
    if (exist == false) {
        state("해당 계좌가 존재하지 않습니다.");
        return 1;
    }

    // (REQ6.3) 현금 전송의 경우, transaction fee를 공지하고, 현금을 정확히 넣었는지 확인한다.
    if (transfer_type == '1') {
        int moneyPage[4] = { 0, };
        char go;
        // Exception Handling (예외 처리)
        try {
            cout << "5000원의 수수료가 발생합니다. 진행하시겠습니까? [y/n]" << endl;
            cin >> go;
            if (go == 'n' or go == 'N') {
                state("송금을 취소합니다. ATM이 종료됩니다.");
                return 1;
            }
            else if (go != 'y' and go != 'Y') {
                throw(go);
            }
        }
        catch (char go) {
            cout << go << "는 잘못된 입력입니다." << endl;
            return 1;
        }

        cout << "송금할 금액을 입력해주세요 : " << endl;
        cout << "50,000 : ";
        cin >> moneyPage[3];
        cout << "10,000 : ";
        cin >> moneyPage[2];
        cout << "5,000 : ";
        cin >> moneyPage[1];
        cout << "1,000 : ";
        cin >> moneyPage[0];

        int total_money = 50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * moneyPage[0];
        char howtopay;
        // Exception Handling (예외 처리)
        try {
            cout << endl << "수수료 5000원을 지불할 방식을 선택해주세요." << endl;
            cout << "1. 5000원 X 1" << endl;
            cout << "2. 1000원 X 5" << endl;
            cin >> howtopay;
            // (REQ10.1) SnapShot
            if (howtopay == 'x' or howtopay == 'X') {
                snapshot();
            }
            if (howtopay != '1' and howtopay != '2') {
                throw(howtopay);
            }
        }
        catch (char howtopay) {
            cout << howtopay << "는 잘못된 입력입니다." << endl;
            return 1;
        }


        // (REQ1.8) Cash transfer fee : 5000
        if (howtopay == '1' or howtopay == '2') {
            state("수수료 지불을 완료하였습니다.");
            // (REQ6.7) Transaction is reflected to the bank account (destination account)
            reciever->deposit(total_money);
            // (REQ6.6) ATM의 사용가능한 현금이 증가한다.
            if (howtopay == '1') {
                moneyPage[1] += 1;
                ChosenATM->deposit(moneyPage);
                this->addTransaction(cardNum, total_money, reciever, 5000);
                return 0;
            }
            else if (howtopay == '2') {
                moneyPage[0] += 5;
                ChosenATM->deposit(moneyPage);
                this->addTransaction(cardNum, total_money, reciever, 5000);
                return 0;
            }
        }
    }
    else if (transfer_type == '2') {
        
        // (REQ6.4) 돈를 보낼 계좌의 계좌번호를 입력받는다.
        long long int accountNum;
        Account* sender = ChosenATM->getPrimaryBank()->getAccountArr(0);
        bool exist = false;
        bool senderPrimary = false;
        cout << "송금할 계좌의 계좌번호를 입력해주세요." << endl;
        cin >> accountNum;
        for (int i = 0; i < ChosenATM->getPrimaryBank()->getAccountNum(); i++) {
            if (accountNum == ChosenATM->getPrimaryBank()->getAccountArr(i)->getAccountNum()) {
                sender = ChosenATM->getPrimaryBank()->getAccountArr(i);
                exist = true;
                senderPrimary = true;
            }
        }
        for (int i = 0; i < ChosenATM->getSubBankNum(); i++) {
            for (int j = 0; j < ChosenATM->getSubBank(i)->getAccountNum(); j++) {
                if (accountNum == ChosenATM->getSubBank(i)->getAccountArr(j)->getAccountNum()) {
                    sender = ChosenATM->getSubBank(i)->getAccountArr(j);
                    exist = true;
                }
            }
        }

        // 틀리면 ATM 종료
        if (exist == false) {
            state("해당 계좌가 존재하지 않습니다.");
            return 1;
        }

        int sendMoney;
        cout << "송금할 금액을 입력해주세요." << endl;
        cin >> sendMoney;

        // (REQ1.8) Account transfer fee between primary banks : 2000
        // (REQ1.8) Account transfer fee between primary bank and non-primary bank : 3000
        // (REQ1.8) Account transfer fee between non-primary banks : 4000
        // (REQ6.5) 수수료 설정
        int MoneyWithFee;
        string go;
        if (recieverPrimary == true and senderPrimary == true) {
            cout << "2000원의 수수료가 부과되었습니다." << endl;
            cout << "송금하시겠습니까? [y/n]" << endl;
            cin >> go;
            MoneyWithFee = sendMoney + 2000;
        }
        else if (recieverPrimary == true or senderPrimary == true) {
            cout << "3000원의 수수료가 부과됩니다." << endl;
            cout << "송금하시겠습니까? [y/n]" << endl;
            cin >> go;
            MoneyWithFee = sendMoney + 3000;
        }
        else if (recieverPrimary == false and senderPrimary == false) {
            cout << "4000원의 수수료가 부과됩니다." << endl;
            cout << "송금하시겠습니까? [y/n]" << endl;
            cin >> go;
            MoneyWithFee = sendMoney + 4000;
        }

        if (go == "n" or go =="N") {
            return 1;
        }

        // 계좌에 돈이 충분하지 않으면 에러 출력
        if (sender->getBalance() < MoneyWithFee) {
            cout << "계좌에 보유한 금액 이상의 금액은 출금이 불가능합니다." << endl << endl;
            return 1;
        }
        else {
            // (REQ6.7) Transaction is reflected to the bank account (source, destination account)
            reciever->deposit(sendMoney);
            sender->withdrawal(MoneyWithFee);
            this->addTransaction(cardNum, sendMoney, sender, reciever, MoneyWithFee - sendMoney);
            return 0;
        }
    }
}

// 세션 설정 (영어)
void Session::sessionEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub) {
    tempSessionTransaction = "";
    int withdrawalNum = 0;
    while (1) {
        char operation;
        cout << "1. Deposit" << endl;
        cout << "2. Withdrawal" << endl;
        cout << "3. Transfer" << endl;
        cin >> operation;
        cout << endl;

        // (REQ10.1) SnapShot
        if (operation == 'x' or operation == 'X') {
            snapshot();
        }

        // ATM 종료!
        if (operation == 'c' or operation == 'C') {
            state("The ATM will be terminated.");
            break;
        }

        // (REQ2.2) 비정상적인 작동이나 사용자가 종료하면 입,출,송금에서 1을 return해 ATM 종료 (C입력 받으면 세션 종료)
        if (operation == '1') {
            int stop = sessionDepositEnglish(ChosenATM, userAccount, cardNum, isSub);
            if (stop == 1) {
                state("The ATM will be terminated.");
                break;
            }
        }
        else if (operation == '2') {
            int stop = sessionWithDrawalEnglish(ChosenATM, userAccount, cardNum, isSub, withdrawalNum);
            if (stop == 1) {
                state("The ATM will be terminated.");
                break;
            }
        }
        else if (operation == '3') {
            int stop = sessionTransferEnglish(ChosenATM, userAccount, cardNum, isSub);
            if (stop == 1) {
                state("The ATM will be terminated.");
                break;
            }
        }
    }
    // (REQ2.3) summary of all transactions is displayed
    state("Session Transaction");
    cout << tempSessionTransaction << endl;
    ChosenATM->updateTransaction(tempSessionTransaction);
    state("Session Transaction Finish");

}

// 입금 (영어)
int Session::sessionDepositEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub) {
    // cash = 1 , check = 2
    char cashORcheck;

    // (REQ4.1) ATM take either cash or check from a user
    cout << "Please choose whether to use cash or checks." << endl;
    cout << "1. Cash" << endl;
    cout << "2. Check" << endl;
    cin >> cashORcheck;

    // (REQ10.1) SnapShot
    if (cashORcheck == 'x' or cashORcheck == 'X') {
        snapshot();
    }

    // ATM 종료 
    if (cashORcheck != '1' and cashORcheck != '2') {
        cout << "Invalid input." << endl;
        return 1;
    }
    if (cashORcheck == 'C' or cashORcheck == 'c') {
        return 1;
    }

    if (cashORcheck == '1') {
        cout << "Please deposit the cash. If it's not a bank" << ChosenATM->getPrimaryBank()->getName() << ", a fee of 1,000 won will be charged." << endl;
        // Deposit 입력받는다.
        int moneyPage[4];
        cout << "50,000 : ";
        cin >> moneyPage[3];
        cout << "10,000 : ";
        cin >> moneyPage[2];
        cout << "5,000 : ";
        cin >> moneyPage[1];
        cout << "1,000 : ";
        cin >> moneyPage[0];
        int totalCash = 50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * moneyPage[0];

        // (REQ4.2) ATM display error. Number of inserted cash exceed.
        if (moneyPage[0] + moneyPage[1] + moneyPage[2] + moneyPage[3] > 50) {
            state("Too much cash has been deposited. Deposit failed!!");
            return 1;
        }
        else {
            // (REQ1.8) Non-primary bank deposit fee : 1000
            // (REQ1.8) primary bank deposit fee : 0
            // (REQ4.3) Transaction updates bank account, too.
            // (REQ4.4) Deposit fee is charged.
            userAccount->deposit(50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * (moneyPage[0] - (int)isSub));
            // (REQ4.5) Deposit increase available cash in ATM.
            ChosenATM->deposit(moneyPage);
            this->addTransaction(cardNum, totalCash, userAccount, "Cash");
            state("The deposit has been completed.");
            return 0;
        }
    }
    else {
        string check;
        int totalCheck = 0;
        int checkNum = 0;
        cout << "Please enter a value for each check. When C is entered, the deposit will be terminated." << endl;
        while (1) {
            // Exception Handling (예외 처리)
            try {
                cin >> check;
                // (REQ10.1) SnapShot
                if (check == "x" or check == "X") {
                    snapshot();
                }
                if (check == "C" or check == "c") {
                    throw check;
                }
                // (REQ1.10) 수표는 100,000원 이상의 금액이어야한다.
                if ((long long int)stoll(check) < 100000) {
                    throw (long long int)stoll(check);
                }
                totalCheck += (long long int)stoll(check);
                checkNum++;
            }
            catch (long long int check) {
                state("The amount you deposited does not fit the check. Please deposit a check of 100,000 won or more.");
                continue;
            }
            catch (string check) {
                state("The deposit has been completed.");
                break;
            }
        }

        // (REQ4.2) ATM display error. Number of inserted check exceed.
        if (checkNum > 30) {
            state("Too many checks have been deposited. Deposit failed!!");
            return 1;
        }
        else {
            // (REQ4.3) Transaction updates bank account, too.
            // (REQ4.4) Deposit fee is charged.
            // (REQ4.6) Deposit check do not increase available cash in ATM.
            userAccount->deposit(totalCheck - 1000 * (int)isSub);
            this->addTransaction(cardNum, totalCheck, userAccount, "Check");
            return 0;
        }
    }
}

// 출금 (영어)
int Session::sessionWithDrawalEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub, int& withdrawalNum) {
    // (REQ5.6) 해당 세션에서 3번 출금한 경우 출금 불가능
    if (withdrawalNum >= 3) {
        cout << "No more withdrawals are available from this session." << endl << endl;
        return 0;
    }

    int moneyPage[4] = { 0, };
    cout << "###(The main bank is charged 1000 won and the sub-bank is charged 2000 won automatically.)###" << endl;
    // (REQ5.1) ATM ask a user to enter the amount of fund to withdraw
    cout << "Please enter the amount to withdraw : " << endl;
    cout << "50,000 : ";
    cin >> moneyPage[3];
    cout << "10,000 : ";
    cin >> moneyPage[2];
    cout << "5,000 : ";
    cin >> moneyPage[1];
    cout << "1,000 : ";
    cin >> moneyPage[0];

    int total_money = 50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * moneyPage[0];

    // (REQ5.7) 500,000원 이상의 금액은 출금 불가능
    if (total_money > 500000) {
        cout << "It is not possible to withdraw more than 500,000 won from one transaction." << endl << endl;
        return 1;
    }
    // (REQ5.2) ATM이 해당 금액을 출금할 경우의 수가 안될 경우 출금 불가능
    else if (ChosenATM->calWithdrawal(moneyPage)) {
        cout << "It is not possible to withdraw more than the amount currently held by the ATM." << endl << endl;
        return 1;
    }
    // (REQ1.8) primary bank withdrawal fee : 1000
    // (REQ1.8) Non-primary bank withdrawal fee : 2000
    // (REQ5.2) 계좌에 돈이 충분하지 않으면 에러 출력
    else if (userAccount->getBalance() < total_money + 1000 * (1 + (int)isSub)) {
        cout << "You cannot withdraw more than the amount you have in your account." << endl << endl;
        return 1;
    }
    else {
        // (REQ5.3) Transaction is reflected to the bank account.
        // (REQ5.4) 출금할 때 수수료 부과 (주은행이면 1000원 sub은행이면 2000원)
        userAccount->withdrawal(total_money + 1000 * (1 + (int)isSub));
        // (REQ5.5) Withdrawal lower available cash in ATM.
        ChosenATM->withdrawal(moneyPage);
        this->addTransaction(cardNum, total_money, userAccount);
        withdrawalNum += 1;
        state("Withdrawal is completed.");
        return 0;
    }
}

// 송금 (영어)
int Session::sessionTransferEnglish(ATM* ChosenATM, Account* userAccount, string cardNum, bool isSub) {
    // (REQ6.1) 사용자에게 transfer type을 물어본다.
    char transfer_type;
    // Exception Handling (예외 처리)
    try {
        cout << "1. Transfer Cash" << endl;
        cout << "2. Transfer account balance" << endl;
        cin >> transfer_type;
        // (REQ10.1) SnapShot
        if (transfer_type == 'x' or transfer_type == 'X') {
            snapshot();
        }
        if (transfer_type != '1' and transfer_type != '2') {
            throw(transfer_type);
        }
    }
    catch (char transfer_type) {
        cout << transfer_type << "is an invalid input." << endl;
        return 1;
    }

    // (REQ6.2) 전송받을 사람의 account number는 항상 확인한다.
    long long int accountNum;
    Account* reciever = ChosenATM->getPrimaryBank()->getAccountArr(0);
    bool exist = false;
    bool recieverPrimary = false;
    cout << "Please enter the account number of the account to receive the remittance." << endl;
    cin >> accountNum;
    for (int i = 0; i < ChosenATM->getPrimaryBank()->getAccountNum(); i++) {
        if (accountNum == ChosenATM->getPrimaryBank()->getAccountArr(i)->getAccountNum()) {
            reciever = ChosenATM->getPrimaryBank()->getAccountArr(i);
            exist = true;
            recieverPrimary = true;
        }
    }
    for (int i = 0; i < ChosenATM->getSubBankNum(); i++) {
        for (int j = 0; j < ChosenATM->getSubBank(i)->getAccountNum(); j++) {
            if (accountNum == ChosenATM->getSubBank(i)->getAccountArr(j)->getAccountNum()) {
                reciever = ChosenATM->getSubBank(i)->getAccountArr(j);
                exist = true;
            }
        }
    }
    // 틀리면 ATM 종료
    if (exist == false) {
        state("This account does not exist.");
        return 1;
    }

    // (REQ6.3) 현금 전송의 경우, transaction fee를 공지하고, 현금을 정확히 넣었는지 확인한다.
    if (transfer_type == '1') {
        int moneyPage[4] = { 0, };
        char go;
        // Exception Handling (예외 처리)
        try {
            cout << "A fee of 5,000 won will be incurred. Do you want to proceed? [y/n]" << endl;
            cin >> go;
            if (go == 'n' or go == 'N') {
                state("Cancel the remittance. The ATM will be terminated.");
                return 1;
            }
            else if (go != 'y' and go != 'Y') {
                throw(go);
            }
        }
        catch (char go) {
            cout << go << "is an invalid input." << endl;
            return 1;
        }

        cout << "Please enter the amount to be transferred : " << endl;
        cout << "50,000 : ";
        cin >> moneyPage[3];
        cout << "10,000 : ";
        cin >> moneyPage[2];
        cout << "5,000 : ";
        cin >> moneyPage[1];
        cout << "1,000 : ";
        cin >> moneyPage[0];

        int total_money = 50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * moneyPage[0];
        char howtopay;
        // Exception Handling (예외 처리)
        try {
            cout << endl << "Please choose how to pay the fee of 5000 won." << endl;
            cout << "1. 5000Won X 1" << endl;
            cout << "2. 1000Won X 5" << endl;
            cin >> howtopay;
            // (REQ10.1) SnapShot
            if (howtopay == 'x' or howtopay == 'X') {
                snapshot();
            }
            if (howtopay != '1' and howtopay != '2') {
                throw(howtopay);
            }
        }
        catch (char howtopay) {
            cout << howtopay << "is an invalid input." << endl;
            return 1;
        }


        // (REQ1.8) Cash transfer fee : 5000
        if (howtopay == '1' or howtopay == '2') {
            state("I have completed the payment of the fee.");
            // (REQ6.7) Transaction is reflected to the bank account (destination account)
            reciever->deposit(total_money);
            // (REQ6.6) ATM의 사용가능한 현금이 증가한다.
            if (howtopay == '1') {
                moneyPage[1] += 1;
                ChosenATM->deposit(moneyPage);
                this->addTransaction(cardNum, total_money, reciever, 5000);
                return 0;
            }
            else if (howtopay == '2') {
                moneyPage[0] += 5;
                ChosenATM->deposit(moneyPage);
                this->addTransaction(cardNum, total_money, reciever, 5000);
                return 0;
            }
        }
    }
    else if (transfer_type == '2') {
        // (REQ6.4) 돈를 보낼 계좌의 계좌번호를 입력받는다.
        long long int accountNum;
        Account* sender = ChosenATM->getPrimaryBank()->getAccountArr(0);
        bool exist = false;
        bool senderPrimary = false;
        cout << "Please enter the account number of the account you want to transfer." << endl;
        cin >> accountNum;

        for (int i = 0; i < ChosenATM->getPrimaryBank()->getAccountNum(); i++) {
            if (accountNum == ChosenATM->getPrimaryBank()->getAccountArr(i)->getAccountNum()) {
                sender = ChosenATM->getPrimaryBank()->getAccountArr(i);
                exist = true;
                senderPrimary = true;
            }
        }
        for (int i = 0; i < ChosenATM->getSubBankNum(); i++) {
            for (int j = 0; j < ChosenATM->getSubBank(i)->getAccountNum(); j++) {
                if (accountNum == ChosenATM->getSubBank(i)->getAccountArr(j)->getAccountNum()) {
                    sender = ChosenATM->getSubBank(i)->getAccountArr(j);
                    exist = true;
                }
            }
        }

        // 틀리면 ATM 종료
        if (exist == false) {
            state("This account does not exist.");
            return 1;
        }

        int sendMoney;
        cout << "Please enter the amount to be transferred." << endl;
        cin >> sendMoney;

        // (REQ1.8) Account transfer fee between primary banks : 2000
        // (REQ1.8) Account transfer fee between primary bank and non-primary bank : 3000
        // (REQ1.8) Account transfer fee between non-primary banks : 4000
        // (REQ6.5) 수수료 설정
        int MoneyWithFee;
        string go;
        if (recieverPrimary == true and senderPrimary == true) {
            cout << "You will be charged a fee of 2,000 won." << endl;
            cout << "Transfer? [y/n]" << endl;
            cin >> go;
            MoneyWithFee = sendMoney + 2000;
        }
        else if (recieverPrimary == true or senderPrimary == true) {
            cout << "You will be charged a fee of 3,000 won." << endl;
            cout << "Transfer? [y/n]" << endl;
            cin >> go;
            MoneyWithFee = sendMoney + 3000;
        }
        else if (recieverPrimary == false and senderPrimary == false) {
            cout << "You will be charged a fee of 4,000 won." << endl;
            cout << "Transfer? [y/n]" << endl;
            cin >> go;
            MoneyWithFee = sendMoney + 4000;
        }

        if (go == "n" or go == "N") {
            return 1;
        }

        // 계좌에 돈이 충분하지 않으면 에러 출력
        if (sender->getBalance() < MoneyWithFee) {
            cout << "You cannot transfer more than the amount you have in your account." << endl << endl;
            return 1;
        }
        else {
            // (REQ6.7) Transaction is reflected to the bank account (source, destination account)
            reciever->deposit(sendMoney);
            sender->withdrawal(MoneyWithFee);
            this->addTransaction(cardNum, sendMoney, sender, reciever, MoneyWithFee - sendMoney);
            return 0;
        }
    }
}


int main()
{
    Session session;
    // Bank Initialization
    // STL vector 사용
    vector<Bank*> BankArr(100);
    cout << "*-------------------- Bank Initialization -------------------*" << endl;
    cout << "은행 생성 도중 취소하면 은행 생성이 되지 않습니다." << endl;
    cout << "취소를 원하시면 C를 눌러주세요." << endl;
    while (1)
    {
        string BankName; 
        string SerialNum;
        cout << "은행 이름을 입력해주세요 : ";
        cin >> BankName;
        if (BankName == "C" or BankName == "c")
            break;
        cout << "은행 시리얼 넘버를 입력해주세요 : ";
        cin >> SerialNum;
        BankArr[BankCnt] = new Bank(BankName, (long long int)stoll(SerialNum));
        cout << BankArr[BankCnt]->getName() << "은행이 생성되었습니다." << endl << endl;
        BankCnt++;

    }
    cout << "*-------------------- Bank Initialization Finish --------------------*" << endl << endl;


    // User Initialization
    // STL vector 사용
    vector<User*> UserArr(100);
    cout << "*-------------------- User Initialization -------------------*" << endl;
    cout << "User 생성 도중 취소하면 User 생성이 되지 않습니다." << endl;
    cout << "취소를 원하시면 C를 눌러주세요." << endl;
    while (1)
    {
        string UserName;
        cout << "이름을 입력해주세요 : ";
        cin >> UserName;
        if (UserName == "C" or UserName == "c")
            break;
        UserArr[UserCnt] = new User(UserName);
        cout << UserArr[UserCnt]->getUserName() << " User가 생성되었습니다." << endl << endl;
        UserCnt++;
    }
    cout << "*-------------------- User Initialization Finish --------------------*" << endl << endl;


    // User Selection Page
    while (1)
    {
    selection:
        char SelectMenu;
        cout << "1. ATM 생성" << endl;
        cout << "2. 계좌 생성" << endl;
        cout << "3. ATM 실행" << endl;
        cout << "실행 메뉴를 선택해주세요 : ";
        cin >> SelectMenu;
        cout << endl;

        // (REQ10.1) SnapShot
        if (SelectMenu == 'x' or SelectMenu == 'X') {
            snapshot();
        }

        // 종료 코드
        if (SelectMenu == 'C' or SelectMenu == 'c') {
            state("프로그램이 종료됩니다.");
            break;
        }
      
        // (REQ1.11) All ATM is created by user input
        // ------------------------------  ATM 생성 코드  --------------------------------
        if (SelectMenu == '1')
        {
            cout << "*-------------------- ATM 생성 --------------------*" << endl;
            // (REQ1.2) single ATM인지 multi ATM인지 입력받아서 생성
            char SingleORMulti;
            cout << "1. SingleATM" << endl;
            cout << "2. MultiATM" << endl;
            cin >> SingleORMulti;
            
            // (REQ10.1) SnapShot
            if (SingleORMulti == 'x' or SingleORMulti == 'X') {
                snapshot();
            }
            // 종료 코드
            if (SingleORMulti == 'C' or SingleORMulti == 'c') {
                state("프로그램이 종료됩니다.");
                break;
            }
            
            char Bilingual;
            cout << "1. Unilingual" << endl;
            cout << "2. Bilingual" << endl;
            cin >> Bilingual;
            bool bil;
            if (Bilingual == '2') {
                bil = true;
            }
            else if (Bilingual=='1') {
            bil = false;
            }

            // (REQ10.1) SnapShot
            if (Bilingual == 'x' or Bilingual == 'X') {
                snapshot();
            }
            // 종료 코드
            if (Bilingual == 'C' or Bilingual == 'c') {
                state("프로그램이 종료됩니다.");
                break;
            }

            string SerialNum;
            cout << "ATM Serial Number를 입력해주세요 : ";
            cin >> SerialNum;

            // (REQ10.1) SnapShot
            if (SerialNum == "x" or SerialNum == "X") {
                snapshot();
            }
            // 종료 코드
            if (SerialNum == "C" or SerialNum == "c") {
                state("프로그램이 종료됩니다.");
                break;
            }

            // (REQ1.1) ATM이 6자리가 아니면 생성불가
            if (strlen(SerialNum.c_str()) != 6) {
                state("6자리 외의 Serial Number는 입력이 불가능합니다.");
                goto selection;
            }
            // (REQ1.1) ATM이 unique한 Serial Num을 가져야함
            for (int i = 0; i < ATMCnt; i++) {
                if (ATMArr[i]->getSerialNum() == (SerialNum)) {
                    state("이미 존재하는 Serial Number입니다.");
                    goto selection;
                }
            }

            string primaryBank;
            cout << "메인 은행을 입력해주세요 : ";
            cin >> primaryBank;

            // (REQ10.1) SnapShot
            if (primaryBank == "x" or primaryBank == "X") {
                snapshot();
            }
            // 종료 코드
            if (primaryBank == "C" or primaryBank == "c") {
                state("프로그램이 종료됩니다.");
                break;
            }

            // (REQ1.2) single ATM인지 multi ATM인지 입력받아서 생성
            for (int i = 0; i < BankCnt; i++) {
                if (BankArr[i]->getName() == primaryBank) {
                    // Single ATM 생성
                    if (SingleORMulti == '1') {
                        SingleATM singleATM = SingleATM((SerialNum), BankArr[i], bil);
                        ATM* single = new SingleATM(singleATM);
                        ATMArr[ATMCnt] = single;
                        break;
                    }
                    // Multi ATM 생성
                    else if (SingleORMulti == '2') {
                        MultiATM multi = MultiATM((SerialNum), BankArr[i],bil);

                        string subName;

                        while (1)
                        {
                            cout << "연결되어 있는 Bank를 입력해주세요 (끝나면 C입력) : " << endl;
                            cin >> subName;
                            // (REQ10.1) SnapShot
                            if (subName == "x" or subName == "X") {
                                snapshot();
                            }
                            if (subName == "C" or subName == "c") {
                                state("Bank 입력을 종료합니다.");
                                break;
                            }
                            for (int j = 0; j < BankCnt;j++) {
                                if (BankArr[j]->getName() == subName) {
                                    multi.addSubBank(BankArr[j]);
                                    cout << subName << "은행이 ATM의 Sub은행으로 추가되었습니다." << endl << endl;
                                    break;
                                }
                                else if (j == BankCnt - 1) {
                                    cout << "###해당 Bank가 존재하지 않습니다. 다시 입력해주세요###" << endl << endl;
                                    break;
                                }
                            }
                        }
                        ATM* multi_to_ATM = new MultiATM(multi);
                        ATMArr[ATMCnt] = multi_to_ATM;
                        break;
                    }
                }
                else if (i == BankCnt - 1) {
                    state("해당 Bank가 존재하지 않습니다.");
                    goto selection;
                }
            }

            // (REQ1.10) ATM only accepts 1000, 5000, 10000, 50000
            // Deposit 입력받는다.
            cout << "ATM이 소유한 deposit을 입력하시오." << endl;
            int moneyPage[4] = { 0, };
            cout << "50,000 : ";
            cin >> moneyPage[3];
            cout << "10,000 : ";
            cin >> moneyPage[2];
            cout << "5,000 : ";
            cin >> moneyPage[1];
            cout << "1,000 : ";
            cin >> moneyPage[0];

            // (REQ1.4) ATM 생성시, user가 사용하기 위한 초기금을 deposit
            ATMArr[ATMCnt]->deposit(moneyPage);
            ATMCnt++;
            cout << "*-------------------- ATM을 생성하였습니다. --------------------*" << endl;
        }

        // (REQ1.11) All Account is created by user input
        // ------------------------------  계좌 생성 코드  ------------------------------
        if (SelectMenu == '2')
        {
            cout << "*-------------------- 계좌 생성 --------------------*" << endl;
            string tempAccountNum;
            long long int AccountNum;
            string tempcardNum;
            long long int cardNum;
            string UserName;
            cout << "이름을 입력하세요 : ";
            cin >> UserName;

            // (REQ1.6) 유저가 같은 은행 계좌 생성하는 것에 제한 X
            // (REQ1.7) 다양한 은행에 계좌 생성해도 문제 X
            //User loop를 돌면서 해당 이름과 동일한 사람이 없으면 오류 있으면 그 사람으로 계좌 생성
            for (int i = 0; i < UserCnt; i++) {
                if (UserArr[i]->getUserName() == UserName) {

                    cout << "사용하실 계좌번호를 입력하세요 : ";
                    cin >> tempAccountNum;

                    // (REQ10.1) SnapShot
                    if (tempAccountNum == "x" or tempAccountNum == "X") {
                        snapshot();
                    }
                    // 종료 코드
                    if (tempAccountNum == "C" or tempAccountNum == "c") {
                        state("ATM이 종료됩니다.");
                        break;
                    }
                    // 계좌번호길이는 무조건 12
                    if (strlen(tempAccountNum.c_str()) != 12) {
                        state("계좌번호는 길이가 12여야 합니다. ATM을 종료합니다.");
                        goto selection;
                    }

                    AccountNum = (long long int)stoll(tempAccountNum);

                    cout << "사용하실 카드번호를 입력하세요 : ";
                    cin >> tempcardNum;

                    // (REQ10.1) SnapShot
                    if (tempcardNum == "x" or tempcardNum == "X") {
                        snapshot();
                    }
                    // 종료 코드
                    if (tempcardNum == "C" or tempcardNum == "c") {
                        state("ATM이 종료됩니다.");
                        break;
                    }

                    cardNum = (long long int)stoll(tempcardNum);

                    int password;
                    cout << "사용하실 비밀번호를 입력해주세요 : ";
                    cin >> password;

                    string accountBank;
                    cout << "전용 은행을 입력하세요 : ";
                    cin >> accountBank;

                    for (int j = 0; j < BankCnt; j++) {
                        if (BankArr[j]->getName() == accountBank) {
                            AccountArr[AccountCnt] = new Account(BankArr[j], UserArr[i], AccountNum, cardNum, password);

                            int money;
                            cout << "최초 입금액을 입력하세요 : ";
                            cin >> money;
                            AccountArr[AccountCnt]->deposit(money);
                            BankArr[j]->addAccount(AccountArr[AccountCnt]);

                            AccountCnt++;
                            break;
                        }
                        else if ((j == BankCnt - 1) and (BankArr[j]->getName() != accountBank)) {
                            state("There is no bank");
                            goto selection;
                        }
                    }
                    break;
                }

                // 여기서 cout가 계속 실행되는 error가 있다.
                else if (i == UserCnt - 1) {
                    state("There is no user name.");
                    goto selection;
                }
            }
            //위의 User loop에서 찾은 user에 계좌 생성
            cout << "*-------------------- 계좌를 생성하였습니다. --------------------*" << endl << endl;
        }

        // ATM 실행 (카드 삽입)
        if (SelectMenu == '3')
        {
            cout << "*-------------------- ATM을 실행하였습니다. --------------------*" << endl;

            // 사용할 ATM 선택
            int whatATM;
            for (int i = 0; i < ATMCnt; i++) {
                cout << i + 1 << ". Primary Bank : " << ATMArr[i]->getPrimaryBank()->getName() << ", Serial Number : " << ATMArr[i]->getSerialNum() << endl;
            }
            cout << endl << "Enter the number of the ATM you want to use : ";
            cin >> whatATM;
            if (whatATM <= ATMCnt and whatATM > 0) {
                whatATM -= 1;
            }
            else {
                state("This ATM does not exist.");
                goto selection;
            }

            ATM* ChosenATM = ATMArr[whatATM];

            string SelectLang;

            if (ChosenATM->getBilingual() == false) {
                SelectLang = "2";
            }
            else {
                cout << "1. 한국어" << endl;
                cout << "2. English" << endl;

                cin >> SelectLang;

                // (REQ10.1) SnapShot
                if (SelectLang == "x" or SelectLang == "X") {
                    snapshot();
                }

                // ATM 종료
                if (SelectLang == "c" or SelectLang == "C") {
                    state("ATM이 종료됩니다.");
                    goto selection;
                }
            }
            
            // 한글 선택
            if (SelectLang == "1") {

                bool isPrimary = false;
                bool isSub = false;
                Account* userAccount = NULL;


                // (REQ2.1) user가 card를 insert하고 나서 session이 시작된다.
                string cardNum;
                cout << "카드 번호를 입력해주세요 : ";
                cin >> cardNum;

                // (REQ10.1) SnapShot
                if (cardNum == "x" or cardNum == "X") {
                    snapshot();
                }

                // (REQ1.9) Admin card 번호 : 0000 입력시 Transaction History 접근 가능
                // Admin 카드 사용시 Transaction 보여주기
                if (cardNum == "0000") {
                    string select;
                    // (REQ7.1) 선택창에 Transaction History를 보여주는 선택지만 보여줌
                    cout << "1. Transaction History" << endl;
                    cin >> select;
                    if (select == "1") {
                        state("Transaction History");
                        // (REQ7.2) ATM class 내부 함수 printTransaction으로 Transaction History 출력
                        ChosenATM->printTransaction();
                        state("Transaction History Finish");

                        // (REQ7.3) Transaction History -> external file
                        ofstream fout("TransactionHistory.txt", ios::app);
                        fout << "*-------------------- Transaction History --------------------*\n";
                        fout << session.printTransaction();
                    }
                    continue;
                }

                // ATM 종료 케이스
                if (cardNum == "C" or cardNum == "c") {
                    state("ATM기를 종료합니다.");
                    goto selection;
                }

                // (REQ3.1)
                // 선택한 ATM에 입력한 카드가 주은행 카드인지, sub은행 카드인지, 둘다 아닌지 판별
                // (REQ1.2) Single ATM에서는 primary bank에 해당하는 카드만, Multi ATM에서는 primary, sub bank에 해당하는 카드만 사용 가능
                // (REQ1.5) Bank can open an Account for user (Bank has all Account array using that bank)
                for (int i = 0; i < ChosenATM->getPrimaryBank()->getAccountNum(); i++) {
                    if (ChosenATM->getPrimaryBank()->getAccountArr(i)->getCardNum() == (long long int)stoll(cardNum)) {
                        userAccount = ChosenATM->getPrimaryBank()->getAccountArr(i);
                        isPrimary = true;
                        break;
                    }
                }

                if (isPrimary == false) {
                    for (int i = 0; i<ChosenATM->getSubBankNum(); i++) {
                        for (int j = 0; j<ChosenATM->getSubBank(i)->getAccountNum(); j++) {
                            if (ChosenATM->getSubBank(i)->getAccountArr(j)->getCardNum() == (long long int)stoll(cardNum)) {
                                userAccount = ChosenATM->getSubBank(i)->getAccountArr(j);
                                isSub = true;
                            }
                        }
                    }
                    if (isSub == false) {
                        // (REQ3.2) ATM에서 primary 은행, sub 은행에 해당하는 카드가 아니면 유효하지 않으므로 에러발생!
                        state("유효하지 않은 카드번호입니다.");
                        goto selection;
                    }
                }

                // (REQ3.5) 3번 연속으로 비밀번호 틀리면 ATM 종료
                // 비밀번호 입력받아 3번 이상 틀리면 ATM 종료!
                int pwFailCnt = 3;
                int gotPW;
                while (pwFailCnt > 0) {
                    try{
                        // (REQ3.3) 비밀번호 입력받고 검증
                        cout << "비밀번호를 입력해주세요 : ";
                        cin >> gotPW;
                        if (gotPW != userAccount->getPassword()) {
                            throw(gotPW);
                        }
                        else if (gotPW == userAccount->getPassword()) {
                            break;
                        }
                    }
                    catch (int gotPW) {
                        --pwFailCnt;
                        if (pwFailCnt == 0) {
                            state("틀렸습니다. ATM 실행이 종료됩니다.");
                            goto selection;
                        }
                        // (REQ3.4) 비밀번호를 틀렸을 때, 에러 발생하고, 남은 기회 알려준다.
                        cout << "틀렸습니다. " << pwFailCnt << "번의 기회가 남았습니다." << endl;
                    }
                }

                // 입금, 출금, 송금, 영수증 출력 선택 페이지
                session.sessionKorean(ChosenATM, userAccount, cardNum, isSub);
            }
            
            // 영어 선택
            else if (SelectLang == "2") {

                bool isPrimary = false;
                bool isSub = false;
                Account* userAccount = NULL;


                // (REQ2.1) user가 card를 insert하고 나서 session이 시작된다.
                string cardNum;
                cout << "Please enter your card number : ";
                cin >> cardNum;

                // (REQ10.1) SnapShot
                if (cardNum == "x" or cardNum == "X") {
                    snapshot();
                }

                // (REQ1.9) Admin card 번호 : 0000 입력시 Transaction History 접근 가능
                // Admin 카드 사용시 Transaction 보여주기
                if (cardNum == "0000") {
                    string select;
                    // (REQ7.1) 선택창에 Transaction History를 보여주는 선택지만 보여줌
                    cout << "1. Transaction History" << endl;
                    cin >> select;
                    if (select == "1") {
                        state("Transaction History");
                        // (REQ7.2) ATM class 내부 함수 printTransaction으로 Transaction History 출력
                        ChosenATM->printTransaction();
                        state("Transaction History Finish");

                        // (REQ7.3) Transaction History -> external file
                        ofstream fout("TransactionHistory.txt", ios::app);
                        fout << "*-------------------- Transaction History --------------------*\n";
                        fout << session.printTransaction();
                    }
                    continue;
                }

                // ATM 종료 케이스
                if (cardNum == "C" or cardNum == "c") {
                    state("Shut down the ATM.");
                    goto selection;
                }

                // (REQ3.1)
                // 선택한 ATM에 입력한 카드가 주은행 카드인지, sub은행 카드인지, 둘다 아닌지 판별
                // (REQ1.2) Single ATM에서는 primary bank에 해당하는 카드만, Multi ATM에서는 primary, sub bank에 해당하는 카드만 사용 가능
                // (REQ1.5) Bank can open an Account for user (Bank has all Account array using that bank)
                for (int i = 0; i < ChosenATM->getPrimaryBank()->getAccountNum(); i++) {
                    if (ChosenATM->getPrimaryBank()->getAccountArr(i)->getCardNum() == (long long int)stoll(cardNum)) {
                        userAccount = ChosenATM->getPrimaryBank()->getAccountArr(i);
                        isPrimary = true;
                        break;
                    }
                }

                if (isPrimary == false) {
                    for (int i = 0; i < ChosenATM->getSubBankNum(); i++) {
                        for (int j = 0; j < ChosenATM->getSubBank(i)->getAccountNum(); j++) {
                            if (ChosenATM->getSubBank(i)->getAccountArr(j)->getCardNum() == (long long int)stoll(cardNum)) {
                                userAccount = ChosenATM->getSubBank(i)->getAccountArr(j);
                                isSub = true;
                            }
                        }
                    }
                    if (isSub == false) {
                        // (REQ3.2) ATM에서 primary 은행, sub 은행에 해당하는 카드가 아니면 유효하지 않으므로 에러발생!
                        state("Invalid card number.");
                        goto selection;
                    }
                }

                // (REQ3.5) 3번 연속으로 비밀번호 틀리면 ATM 종료
                // 비밀번호 입력받아 3번 이상 틀리면 ATM 종료!
                int pwFailCnt = 3;
                int gotPW;
                while (pwFailCnt > 0) {
                    try {
                        // (REQ3.3) 비밀번호 입력받고 검증
                        cout << "Please enter your password : ";
                        cin >> gotPW;
                        if (gotPW != userAccount->getPassword()) {
                            throw(gotPW);
                        }
                        else if (gotPW == userAccount->getPassword()) {
                            break;
                        }
                    }
                    catch (int gotPW) {
                        --pwFailCnt;
                        if (pwFailCnt == 0) {
                            state("Invalid, ATM execution will end.");
                            goto selection;
                        }
                        // (REQ3.4) 비밀번호를 틀렸을 때, 에러 발생하고, 남은 기회 알려준다.
                        cout << "Incorrect. You have " << pwFailCnt << " chances left." << endl;
                    }
                }

                // 입금, 출금, 송금, 영수증 출력 선택 페이지
                session.sessionEnglish(ChosenATM, userAccount, cardNum, isSub);
            }
        }
    }
}