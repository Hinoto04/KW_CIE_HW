
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
class Stack {
private:
    Node<T>* m_Top;
public:
    Stack() {
        this->m_Top = NULL;
    }
    ~Stack() {
        for (Node<T>* cur = this->m_Top; this->m_Top; cur = this->m_Top) {
            m_Top = m_Top->getNext();
            delete cur;
        }
    }
    void push(T data) { //Push
        Node<T>* newNode = new Node<T>(data);
        newNode->setNext(this->m_Top);
        this->m_Top = newNode;
    }
    T pop() { //Pop
        if (this->m_Top != NULL) {
            Node<T>* target = this->m_Top;
            T data = target->getData();
            this->m_Top = this->m_Top->getNext();
            delete target;
            return data;
        }
        else return NULL;
    }
    T top() { //Top
        if (this->m_Top != NULL) return this->m_Top->getData();
        else return NULL;
    } 
    bool is_Empty() { //isEmpty
        return (this->m_Top == NULL);
    }
    void print() { //Print
        Node<T>* cur = this->m_Top;
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
    Stack<T> s;
    char temp[100];
    
    while (true) {
        //사용자 명령 입력
        cin >> temp;
        if (!strCmp(temp, "push")) { //Push [element]
            T t;
            cin >> t;
            s.push(t);
        }
        else if (!strCmp(temp, "pop")) { //Pop
            cout << s.pop() << endl;
        }
        else if (!strCmp(temp, "top")) { //Top
            cout << s.top() << endl;;
        }
        else if (!strCmp(temp, "isEmpty")) { //isEmpty
            cout << "is_Empty(0:false, 1:true) : " << s.is_Empty() << endl;
        }
        else if (!strCmp(temp, "print")) { //Print
            s.print();
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
