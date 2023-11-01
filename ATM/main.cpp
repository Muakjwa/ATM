#pragma once
#include <iostream>
#include <string>
#include "ATM.h"
#include "Bank.h"
#include "User.h"

using namespace std;

static int BankCnt = 0;
static int UserCnt = 0;
static int ATMCnt = 0;

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
        UserArr[UserCnt]->getUserName();
        UserCnt++;
    }
    cout << "*-------------------- User Initialization Finish --------------------*" << endl;


    // User Selection Page
    ATM* ATMArr[100];
    while (1)
    {
        char SelectMenu;
        cout << "실행 메뉴를 선택해주세요." << endl;
        cout << "1. ATM 생성" << endl;
        cout << "2. 계좌 생성" << endl;
        cout << "3. ATM 실행" << endl;
        cin >> SelectMenu;

        // 종료 코드
        if (SelectMenu == 'C' or SelectMenu == 'c')
            break;

        // ATM 생성 코드
        if (SelectMenu == '1')
        {
            int SerialNum;
            cout << "Serial Number를 입력해주세요 : ";
            cin >> SerialNum;
            cout << "연결되어 있는 Bank를 입력해주세요 (끝나면 C입력) : " << endl;
            string BankName;
            ATMArr[ATMCnt] = new ATM(SerialNum);

            // ATM이 Single인지 Multi인지 결정 (Bank들을 입력받는다)
            while (1)
            {
                if (BankName == "C" or BankName == "c")
                    break;
                else
                {
                    ATMArr[ATMCnt]->addBank(BankName);
                }
            }

            // Deposit 입력받는다.
            cout << "ATM이 소유한 deposit을 입력하시오." << endl;
            int moneyPage[4];
            cout << "50,000 : ";
            cin >> moneyPage[3];
            cout << "10,000 : ";
            cin >> moneyPage[2];
            cout << "5,000 : ";
            cin >> moneyPage[1];
            cout << "1,000 : ";
            cin >> moneyPage[0];

            ATMArr[ATMCnt]->setDeposit(moneyPage);
            ATMCnt++;
        }

        // 계좌 생성 코드
        if (SelectMenu == '2')
        {
            cout << "계좌를 생성하겠습니다." << endl;
            long long int AccountNum;
            string UserName;
            cout << "이름을 입력하세요 : ";
            cin >> UserName;
            int i = 0;

            //User loop를 돌면서 해당 이름과 동일한 사람이 없으면 오류 있으면 그 사람으로 계좌 생성

            cout << "사용하실 계좌번호를 입력하세요 : ";
            cin >> AccountNum;
            //위의 User loop에서 찾은 user에 계좌 생성
        }

        // ATM 실행 (카드 삽입)
        if (SelectMenu == '3')
        {
            char SelectLang;
            cout << "1. 한국어" << endl;
            cout << "2. English" << endl;

            do {
                cin >> SelectLang;
            } while (SelectLang == '1' or SelectLang == '0');

            if (SelectLang == '1') {
                cout << "카드번호를 입력해주세요 : " << endl;
            }
            else {
                //영어로 작성
            }
        }
    }
}