#pragma once
#include <iostream>
#include <string>
#include "ATM.h"
#include "Bank.h"
#include "User.h"
#include "Account.h"
#include "SingleATM.h"
#include "MultiATM.h"

class ATM;
class Bank;
class User;
class Account;

using namespace std;

static int BankCnt = 0;
static int UserCnt = 0;
static int AccountCnt = 0;
static int ATMCnt = 0;


void state(string statement) {
    cout << "*-------------------- " << statement << " --------------------*" << endl << endl;
}

// Bank와 ATM serial 넘버 입력받는게 아니라 자동으로 생성되게 (ex BankCnt + 100)
// Bank이름 겹치는거 없는지 확인해주기

int main()
{
    // Bank Initialization
    Bank* BankArr[100];
    cout << "*-------------------- Bank Initialization -------------------*" << endl;
    cout << "은행 생성 도중 취소하면 은행 생성이 되지 않습니다." << endl;
    cout << "취소를 원하시면 C를 눌러주세요." << endl;
    while (1)
    {
        string BankName; int SerialNum;
        cout << "은행 이름을 입력해주세요 : ";
        cin >> BankName;
        if (BankName == "C" or BankName == "c")
            break;
        cout << "은행 시리얼 넘버를 입력해주세요 : ";
        cin >> SerialNum;
        BankArr[BankCnt] = new Bank(BankName, SerialNum);
        cout << BankArr[BankCnt]->getName() << "은행이 생성되었습니다." << endl << endl;
        //BankArr[BankCnt]->getName();
        //BankArr[BankCnt]->getSerialNum();
        BankCnt++;

    }
    cout << "*-------------------- Bank Initialization Finish --------------------*" << endl << endl;


    // User Initialization
    User* UserArr[100];
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
    Account* AccountArr[100];
    ATM* ATMArr[100];
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

        // 종료 코드
        if (SelectMenu == 'C' or SelectMenu == 'c') {
            state("프로그램이 종료됩니다.");
            break;
        }
      
        // ------------------------------  ATM 생성 코드  --------------------------------
        if (SelectMenu == '1')
        {
            cout << "*-------------------- ATM 생성 --------------------*" << endl;
            char SingleORMulti;
            cout << "1. SingleATM" << endl;
            cout << "2. MultiATM" << endl;
            cin >> SingleORMulti;
            
            int SerialNum;
            cout << "ATM Serial Number를 입력해주세요 : ";
            cin >> SerialNum;

            string primaryBank;
            cout << "메인 은행을 입력해주세요 : ";
            cin >> primaryBank;

            // BankArr에 BankName이 없으면 에러 출력 코드 작성해야함 에러시 다시 입력받을 수 있도록 하면 됨
            for (int i = 0; i < BankCnt; i++) {
                if (BankArr[i]->getName() == primaryBank) {
                    if (SingleORMulti == '1') {
                        //SingleATM singleATM = SingleATM(SerialNum, BankArr[i]);
                        //ATM* single = new SingleATM(singleATM);
                        ATM single = ATM(SerialNum, BankArr[i]);
                        ATMArr[ATMCnt] = &single;
                        ATMCnt += 1;
                        break;
                    }
                    else if (SingleORMulti == '2') {
                        MultiATM multi = MultiATM(SerialNum, BankArr[i]);

                        string subName;

                        while (1)
                        {
                            cout << "연결되어 있는 Bank를 입력해주세요 (끝나면 C입력) : " << endl;
                            cin >> subName;
                            if (subName == "C" or subName == "c") {
                                state("ATM생성을 취소합니다.");
                                goto selection;
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
                        ATMCnt += 1;
                        break;
                    }
                }
                else if (i == BankCnt - 1) {
                    state("해당 Bank가 존재하지 않습니다.");
                    goto selection;
                }
            }

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

            ATMArr[ATMCnt]->deposit(moneyPage);
            ATMCnt++;
            cout << "*-------------------- ATM을 생성하였습니다. --------------------*" << endl;
        }

        // ------------------------------  계좌 생성 코드  ------------------------------
        if (SelectMenu == '2')
        {
            cout << "*-------------------- 계좌 생성 --------------------*" << endl;
            long long int AccountNum;
            long long int cardNum;
            string UserName;
            cout << "이름을 입력하세요 : ";
            cin >> UserName;

            //User loop를 돌면서 해당 이름과 동일한 사람이 없으면 오류 있으면 그 사람으로 계좌 생성
            for (int i = 0; i < UserCnt; i++) {
                if (UserArr[i]->getUserName() == UserName) {

                    cout << "사용하실 계좌번호를 입력하세요 : ";
                    cin >> AccountNum;

                    cout << "사용하실 카드번호를 입력하세요 : ";
                    cin >> cardNum;

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
            char SelectLang;
            cout << "1. 한국어" << endl;
            cout << "2. English" << endl;

            cin >> SelectLang;
            
            // ATM 종료
            if (SelectLang == 'c' or SelectLang == 'C') {
                state("ATM이 종료됩니다.");
                goto selection;
            }
            
            if (SelectLang == '1') {
                int whatATM;
                for (int i = 0; i < ATMCnt; i++) {
                    cout << i + 1 << ". 주 은행 : " << ATMArr[i]->getPrimaryBank().getName() << ", 시리얼 번호 : " << ATMArr[i]->getPrimaryBank().getSerialNum() << endl;
                }
                cout << endl << "사용하실 ATM기의 번호를 입력하세요 : ";
                cin >> whatATM;
                if (whatATM <= ATMCnt and whatATM > 0) {
                    whatATM -= 1;
                }
                else {
                    state("해당 ATM은 존재하지 않습니다.");
                    goto selection;
                }

                ATM ChosenATM = *ATMArr[whatATM];

                bool isPrimary = false;
                bool isSub = false;
                Account* userAccount = NULL;

                    
                char cardNum;
                cout << "카드 번호를 입력해주세요 : ";
                cin >> cardNum;
                if (cardNum == 'C' or cardNum == 'c') {
                    state("ATM기를 종료합니다.");
                    goto selection;
                }
                for (int i = 0; i < ChosenATM.getPrimaryBank().getAccountNum(); i++) {
                    if (ChosenATM.getPrimaryBank().getAccountArr(i)->getCardNum() == cardNum) {
                        userAccount = ChosenATM.getPrimaryBank().getAccountArr(i);
                        isPrimary = true;
                        break;
                    }
                }
                if (isPrimary == false) {
                    for (int i = 0; ChosenATM.getSubBankNum(); i++) {
                        for (int j = 0; ChosenATM.getSubBank(i).getAccountNum(); j++) {
                            if (ChosenATM.getSubBank(i).getAccountArr(j)->getCardNum() == cardNum) {
                                userAccount = ChosenATM.getSubBank(i).getAccountArr(j);
                                isSub = true;
                            }
                        }
                    }
                    if (isSub == false) {
                        state("유효하지 않은 카드번호입니다.");
                        goto selection;
                    }
                }

                int pwFailCnt = 3;
                int gotPW;
                while (pwFailCnt > 0) {
                    cout << "비밀번호를 입력해주세요 : ";
                    cin >> gotPW;
                    if (gotPW == userAccount->getPassword()) {
                        break;
                    }
                    --pwFailCnt;
                    if (pwFailCnt == 0) {
                        state("틀렸습니다. ATM 실행이 종료됩니다.");
                        break;
                    }
                    cout << "틀렸습니다. " << pwFailCnt << "번의 기회가 남았습니다." << endl;
                }
                while (1) {
                    int withdrawalNum = 0;
                    char operation;
                    cout << "1. 입금" << endl;
                    cout << "2. 출금" << endl;
                    cout << "3. 송금" << endl;
                    cout << "4. 영수증 출력" << endl;
                    cin >> operation;

                    // ATM 종료!
                    if (operation == 'c' or operation == 'C') {
                        state("ATM이 종료됩니다.");
                        goto selection;
                    }

                    // 입금 CASE
                    if (operation == '1') {

                        // cash = 1 , check = 2
                        char cashORcheck;

                        cout << "현금을 사용할지 수표를 사용할지 골라주세요." << endl;
                        cout << "1. 현금" << endl;
                        cout << "2. 수표" << endl;
                        cin >> cashORcheck;

                        // 현금이나 수표가 아닌 다른 값을 입력 받으면 다시 입력받도록 하고, C를 입력받으면 ATM기를 종료한다.
                        do {
                            if (cashORcheck != '1' and cashORcheck != '2') {
                                cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
                            }
                            if (cashORcheck == 'C' or cashORcheck == 'c') {
                                state("ATM기를 종료합니다.");
                                goto selection;
                            }
                        } while (cashORcheck != '1' and cashORcheck != '2');

                        if (cashORcheck == '1') {
                            cout << "현금을 입금해주세요. " << ChosenATM.getPrimaryBank().getName() << "은행이 아니면 수수료 1000원이 부과됩니다." << endl;
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

                            if (moneyPage[0] + moneyPage[1] + moneyPage[2] + moneyPage[3] > 50) {
                                state("너무 많은 현금이 입금되었습니다. 입금 실패!!");
                                goto selection;
                            }
                            else {
                                userAccount->deposit(50000 * moneyPage[3] + 10000 * moneyPage[2] + 5000 * moneyPage[1] + 1000 * (moneyPage[0] - (int)isSub));
                                ChosenATM.deposit(moneyPage);
                            }
                        }
                        else {
                            string check;
                            int totalCheck = 0;
                            int checkNum = 0;
                            cout << "각 수표의 값을 입력해주세요. C가 입력되면 입금이 종료됩니다." << endl;
                            while (1) {
                                cin >> check;
                                if (check == "C" or check == "c") {
                                    break;
                                }
                                totalCheck += stoi(check);
                                checkNum++;
                            }

                            if (checkNum > 30) {
                                state("너무 많은 수표가 입금되었습니다. 입금 실패!!");
                                goto selection;
                            }
                            else {
                                userAccount->deposit(totalCheck - 1000 * (int)isSub);
                            }
                        }
                    }

                    // 출금 CASE
                    else if (operation == '2') {
                        // (REQ5.6) 해당 세션에서 3번 출금한 경우 출금 불가능
                        if (withdrawalNum >= 3) {
                            cout << "해당 세션에서 더 이상 출금이 불가능합니다." << endl << endl;
                            continue;
                        }

                        long long int drawalMoney;
                        cout << "출금할 금액을 입력해주세요 : " << endl;
                        cin >> drawalMoney;

                        // (REQ5.7) 500,000원 이상의 금액은 출금 불가능
                        if (drawalMoney > 500000) {
                            cout << "한번의 거래에서 500,000원 이상의 금액은 출금이 불가능합니다." << endl << endl;
                            continue;
                        }
                        else if (drawalMoney < 1000) {
                            cout << "1000원 이하의 금액은 출금이 불가능합니다." << endl << endl;
                            continue;
                        }
                        else if (drawalMoney % 1000 != 0) {
                            cout << "1000원 이하의 단위를 가진 금액은 출금이 불가능합니다." << endl << endl;
                            continue;
                        }
                        // (REQ5.5) ATM이 해당 금액을 출금할 경우의 수가 안될 경우 출금 불가능
                        else if (ChosenATM.calWithdrawal(drawalMoney)) {
                            cout << "ATM기가 현재 보유한 금액 이상의 출금이 불가능합니다." << endl << endl;
                            continue;
                        }
                        // (REQ5.2) 계좌에 돈이 충분하지 않으면 에러 출력
                        else if (userAccount->getBalance() < drawalMoney + 1000*(1+(int)isSub)) {
                            cout << "계좌에 보유한 금액 이상의 금액은 출금이 불가능합니다." << endl << endl;
                            continue;
                        }
                        else {
                            // (REQ5.4) 출금할 때 수수료 부과 (주은행이면 1000원 sub은행이면 2000원)
                            userAccount->withdrawal(drawalMoney + 1000*(1+(int)isSub));
                            ChosenATM.withdrawal(drawalMoney);
                        }
                    }

                    // 송금 CASE
                    else if (operation == '3') {

                    }

                    // 영수증 출력 CASE
                    else if (operation == '4') {

                    }
                }
            }
        }
    }
}