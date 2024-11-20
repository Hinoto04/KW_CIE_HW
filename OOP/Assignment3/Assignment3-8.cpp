
#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
    Node* m_Next;
    T m_Data;
public:
    Node() {
        this->m_Next = NULL;
    }
    Node(T data) {
        this->m_Next = NULL;
        this->m_Data = data;
    }
    ~Node() {
        return;
    }
    T getData() { return m_Data; }
    Node* getNext() { return this->m_Next; }
    void setNext(Node* next) { this->m_Next = next; }
};

template <typename T>
class Queue {
private:
    Node<T>* m_Front;
    Node<T>* m_Back;
public:
    Queue() {
        this->m_Front = NULL;
        this->m_Back = NULL;
    }
    ~Queue() {
        for (Node<T>* cur = this->m_Front; this->m_Front; cur = this->m_Front) {
            m_Front = m_Front->getNext();
            delete cur;
        }
        this->m_Back = NULL;
    }
    void enqueue(T data) { //Push
        Node<T>* newNode = new Node<T>(data);
        if (this->m_Front == NULL) {
            this->m_Front = newNode;
            this->m_Back = newNode;
        }
        else {
            this->m_Back->setNext(newNode);
            this->m_Back = newNode;
        }
    }
    T dequeue() { //Pop
        if (this->m_Front != NULL) {
            Node<T>* target = this->m_Front;
            T data = target->getData();
            this->m_Front = this->m_Front->getNext();
            delete target;
            if (this->m_Front == NULL) this->m_Back = NULL;
            return data;
        }
        else {
            cout << "Queue is Empty.";
            return NULL;
        }
    }
    T front() { //Top
        if (this->m_Front != NULL) return this->m_Front->getData();
        else {
            cout << "Queue is Empty.";
            return NULL;
        }
    }
    bool is_Empty() { //isEmpty
        return (this->m_Front == NULL);
    }
    void print() { //Print
        Node<T>* cur = this->m_Front;
        cout << "[";
        if (cur != NULL) {
            cout << cur->getData();
            cur = cur->getNext();
        }
        while (cur != NULL) {
            cout << ", " << cur->getData();
            cur = cur->getNext();
        }
        cout << "]" << endl;
    }
};

bool strCmp(const char* a, const char* b) {
    int i = 0;
    while (true) {
        if (a[i] != b[i]) {
            return 1;
        }
        if (a[i] == NULL) {
            return 0;
        }
        i++;
    }
    return 0;
}

int main()
{
    typedef int T;
    Queue<T> q;
    char temp[100];

    while (true) {
        //사용자 명령 입력
        cin >> temp;
        if (!strCmp(temp, "enqueue")) { //Enqueue [element]
            T t;
            cin >> t;
            q.enqueue(t);
        }
        else if (!strCmp(temp, "dequeue")) { //Dequeue
            cout << q.dequeue() << endl;
        }
        else if (!strCmp(temp, "front")) { //Front
            cout << q.front() << endl;;
        }
        else if (!strCmp(temp, "isEmpty")) { //isEmpty
            cout << "is_Empty(0:false, 1:true) : " << q.is_Empty() << endl;
        }
        else if (!strCmp(temp, "print")) { //Print
            q.print();
        }
        else if (!strCmp(temp, "exit")) { //Exit
            cout << "Exit The Program." << endl;
            break;
        }
        else {
            cout << "Invalid Command." << endl;
        }
    }

    return 0;
}
