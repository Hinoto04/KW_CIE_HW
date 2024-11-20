
#include <iostream>
#include <string>
#include <random>
#define LENGTH 10 //연결 리스트 크기
using namespace std;

//연결 리스트 노드
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
    ~Node() { 
        //cout << "Node Destruct" << endl;
        return; 
    }
};

//연결 리스트
template <typename T>
class LinkedList {
protected:
    Node<T>* head;
    int length = 0;
public:
    LinkedList() {
        this->head = NULL;
    }
    ~LinkedList() {
        //cout << "List Destruct" << endl;
        Node<T>* cur = this->head;
        for (int i = 0; i < this->length; i++) {
            cur = this->head;
            this->head = cur->next;
            delete cur;
        }
    }
    //연결 리스트 길이
    int getLength() { return this->length; }

    //연결 리스트 첫 노드 가져오기
    Node<T>* getHead() { return this->head; }

    //연결 리스트의 특정 인덱스 요소 가져오기
    Node<T>* getByIndex(int idx) {
        Node<T>* cur = this->head;
        for (int i = 0; i < idx; i++) {
            if (cur == NULL) break;
            cur = cur->next;
        }
        return cur;
    }

    //연결 리스트 연장
    Node<T>* append(T data) {
        if (this->head) {
            Node<T>* cur = head;
            while (cur->next != NULL) cur=cur->next;
            cur->next = new Node<T>(data);
            this->length++;
            return cur->next;
        }
        this->head = new Node<T>(data);
        this->length++;
        return this->head; 
    }

    //연결 리스트 초기화
    void init() {
        //노드 순회
        //cout << "List Destruct" << endl;
        Node<T>* cur = this->head;
        for (int i = 0; i < this->length; i++) {
            cur = this->head;
            this->head = cur->next;
            delete cur;
        }
        this->head = NULL;
        this->length = 0;
    }

    //연결 리스트 출력
    void print(ostream& os) {
        Node<T>* cur = this->head;
        for (int i = 0; i < this->length; i++) {
            os << cur->data << " ";
            cur = cur->next;
        }
        os << endl;
    }
};

int main()
{
    srand(time(NULL));

    LinkedList<int> cList;
    char temp[101];
    while (true) {
        cin >> temp;
        if (strcmp(temp, "initialize")==0) { //Initialize
            cList.init();
            for (int i = 0; i < LENGTH; i++) {
                int n;
                cin >> n;
                cList.append(n);
            }
            //cList.print(cout);
            Node<int>* cur = cList.getByIndex(LENGTH-1);
            cur->next = cList.getHead();
            //cout << cur->next->data;
        }
        else if (strcmp(temp, "transfer")==0) { //Transfer
            if (cList.getLength() != LENGTH) {
                cout << "원형 연결 리스트가 초기화되어 있지 않습니다." << endl;
            }
            int a, b;
            cin >> a;
            cin >> temp;
            cin >> b;
            if (a > b) {
                b += LENGTH;
            }
            Node<int>* cur = cList.getByIndex(a);
            int value = cur->data;
            for (int i = 0; i < b - a; i++) {
                int r = rand() % 10; //연결은 10% 확률로 끊어진다.
                if (r) {
                    cur = cur->next;
                }
                else {
                    cout << "Detected a disconnection between ";
                    cout << (a + i) % LENGTH;
                    cout << " and ";
                    cout << (a + i + 1) % LENGTH;
                    return 0;
                }
            }
            cur->data = value;
        }
        else if (strcmp(temp, "print")==0) { //Print
            if (cList.getLength() != LENGTH) {
                cout << "원형 연결 리스트가 초기화되어 있지 않습니다." << endl;
                continue;
            }
           /* for (int i = 0; i < cList.getLength(); i++) {
                Node<int>* cur = cList.getHead();
                cout << cur->data << endl;
                cur = cur->next;
            }*/
            cList.print(cout);
        }
        else if (strcmp(temp, "exit")==0) { //Exit
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << "존재하지 않는 명령입니다." << endl;
        }
    }
}
