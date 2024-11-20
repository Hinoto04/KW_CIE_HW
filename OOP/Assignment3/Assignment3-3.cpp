
#include <iostream>
#include <string>
#include <fstream>
#define MAX_LENGTH 1001
using namespace std;

//주어진 Member 구조체를 연결 리스트로 사용하도록
typedef struct Member {
    //멤버 추가 무관, 아이디 비번의 크기는 변경불가, 최소 10자, 최대 20자
    char id[20];
    char password[20];
    struct Member* next;
} Member;

//암호화
void encrypt(char* str) {
    for (int i = 0; str[i] != NULL && i < 20; i++) {
        if ('a' <= str[i] && str[i] <= 'z') {
            str[i] += 3;
            if (str[i] > 'z') {
                str[i] -= ('z' - 'a');
            }
        }
    }
    return;
}

//복호화
void decrypt(char* str) {
    for (int i = 0; str[i] != NULL && i < 20; i++) {
        if ('a' <= str[i] && str[i] <= 'z') {
            str[i] -= 3;
            if (str[i] < 'a') {
                str[i] += ('z' - 'a');
            }
        }
    }
    return;
}

//연결 리스트 출력
void printList(Member* head) {
    Member* cur = head;
    while (cur != NULL) {
        cout << cur->id << " / " << cur->password << ", ";
        cur = cur->next;
    }
    cout << endl;
}

//문자열 복사
void strCpy(char* destination, const char* source) {
    for (int i = 0; source[i] != NULL && i < 20; i++) {
        destination[i] = source[i];
    }
}

//문자열 비교 (같을 경우 0 출력)
int strCmp(const char* a, const char* b) {
    for (int i = 0; i < 20; i++) {
        if (a[i] != b[i]) return 1;
        if (a[i] == NULL) return 0;
    }
    return 0;
}

int main()
{
    //연결 리스트 시작점
    Member* members = NULL;

    //저장 데이터 불러오기
    ifstream ifs;
    ifs.open("members.txt");
    char temp[50];

    if (!ifs.fail()) {
        while (!ifs.eof()) {
            Member* newMember = new Member();
            ifs >> newMember->id;
            ifs >> newMember->password;
            newMember->next = NULL;
            decrypt(newMember->password);
            if (members == NULL) {
                members = newMember;
            }
            else {
                Member* cur = members;
                while (cur->next != NULL) {
                    cur = cur->next;
                }
                cur->next = newMember;
            }
        }
    }

    //파일 입력 정상 확인용
    /*cout << "MemberList" << endl;
    printList(members);
    cout << "-------------------" << endl;*/

    int option;
    //탈퇴 작업을 위한 prev와 현재 로그인 계정 기록
    Member* prev = NULL;
    Member* loggedIn = NULL;

    //사용자 입력 구간
    while (true) {
        cout << "=====================" << endl;
        if (loggedIn != NULL) {
            cout << "Logged in user : (" << loggedIn->id << ")" << endl;
        }
        cout << "Menu." << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Exit" << endl;
        cout << " : ";

        cin >> option;
        cout << "---------------------" << endl;
        if (option == 1) { // Login
            if (loggedIn) continue; //(로그인 상태에서 회원가입은 유효한 입력이 아님)
            char id[21];
            cout << "User id: ";
            cin >> id;
            char pw[21];
            cout << "password: ";
            cin >> pw;
            cout << "---------------------" << endl;
            Member* cur = members;
            //id유저 찾기
            while (cur != NULL) {
                if (strCmp(cur->id, id) == 0) {
                    break;
                }
                prev = cur;
                cur = cur->next;
            }
            if (cur == NULL || strCmp(cur->password, pw) != 0) {
                cout << "Login failed. Invalid User id or password." << endl;
                continue;
            }
            loggedIn = cur;
        }
        else if (option == 2) { //Register 
            if (loggedIn) continue; //(로그인 상태에서 회원가입은 유효한 입력이 아님)
            string id;
            string pw;
            cout << "User id: ";
            cin >> id;
            cout << "password: ";
            cin >> pw;
            cout << "---------------------" << endl;
            //ID 중복 체크 과정
            Member* cur = members;
            while (cur != NULL) {
                if (strCmp(cur->id, id.c_str()) == 0) {
                    break;
                }
                prev = cur;
                cur = cur->next;
            }
            if (cur != NULL) { //이미 존재하는 ID입니다.
                cout << "User ID is Already Exist." << endl;
                continue;
            }
            //PW 체크 과정
            string special = "!@#$%^&*()";
            bool valid[4] = { 0,0,0,1 };
            for (int i = 0; pw[i] != NULL && i < 20; i++) {
                if ('a' <= pw[i] && pw[i] < 'z') {
                    valid[0] = true; //소문자 한 개 이상 포함;;
                }
                else if ('0' <= pw[i] && pw[i] <= '9') {
                    valid[1] = true; // 숫자 한 개 이상 포함;
                }
                else if (special.find(pw[i]) != string::npos) {
                    valid[2] = true; //특수문자 한 개 이상 포함;
                }
                else {
                    valid[3] = false;
                }
            }
            //문자열 길이 체크
            if (pw.length() < 10 || pw.length() > 20) {
                cout << "password is Invalid." << endl;
                continue;
            }
            if (!(valid[0] && valid[1] && valid[2] && valid[3])) {
                //cout << valid[0] << valid[1] << valid[2] << valid[3] << endl;
                cout << "password is Invalid." << endl;
                continue;
            }
            Member* new_member = new Member();
            strCpy(new_member->id, id.c_str());
            strCpy(new_member->password, pw.c_str());
            if (members == NULL) {
                members = new_member;
            }
            else {
                prev->next = new_member;
            }
        }
        else if (option == 3) { //Withdraw
            if (loggedIn == NULL) { //Login 상태가 아닐 경우
                cout << "Invalid." << endl;
                continue;
            }
            if (prev) { //head가 아닐 경우
                prev->next = loggedIn->next;
                delete loggedIn;
                loggedIn = NULL;
            }
            else { //head일 경우
                members = loggedIn->next;
                delete loggedIn;
                loggedIn = NULL;
            }
        }
        else if (option == 4) { //Exit
            cout << "Exit The Program." << endl;
            break;
        }
        else { //e.t.c.
            cout << "Invalid Option." << endl;
        }
    }

    //저장 절차
    ofstream ofs;
    ofs.open("members.txt");

    // id/encryted_pw 순으로 저장
    Member* cur = members;
    while (cur != NULL) {
        encrypt(cur->password);
        ofs << cur->id << " " << cur->password << endl;
        cur = cur->next;
    }
    ofs.close();
}
