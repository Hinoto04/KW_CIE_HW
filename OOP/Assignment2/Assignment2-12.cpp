
#include <iostream>
#include <fstream>
using namespace std;

//앞의 값과 뒤의 값의 차를 반환 (앞이 크면 양수, 앞이 작으면 음수)
//전부 같다가 앞의 값이 없다면 -1
//전부 같다가 뒤의 값이 없다면 1
int advStrCmp(const char* a, const char* b) {
    int i = 0;
    while (true) {
        char c1 = a[i] > 97 ? a[i] - 32 : a[i];
        char c2 = b[i] > 97 ? b[i] - 32 : b[i];
        if (c1 != c2) return c1 - c2;
        if (c1 == '\0') return -1;
        if (c2 == '\0') return 1;
        i++;
    }
}

template <typename T>
struct Node {
    T data = NULL;
    Node* next = NULL;
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    Node<T>* getHead() {
        return this->head;
    }

    void append(T data) {
        Node<T>* temp = new Node<T>;
        temp->data = data;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
    }

    void print() {
        cout << "Linked list : ";
        Node<T>* current = this->head;
        if (current == NULL) {
            cout << endl;
        }
        else {
            cout << current->data;
            current = current->next;
            while (current != NULL) {
                cout << " -> " << current->data;
                current = current->next;
            }
            cout << endl;
        }
    }

    void sort() {
        Node<T>* start = this->head;
        while (start != NULL) {
            Node<T>* min = start;
            Node<T>* current = start;
            while (current != NULL) {
                if (advStrCmp(current->data, min->data)<0) {
                    min = current;
                }
                current = current->next;
            }
            T temp = min->data;
            min->data = start->data;
            start->data = temp;
            start = start->next;
        }
    }

    void dlt(int temp) {
        Node<T>* current = this->head;
        while (current != NULL && current->data == temp) {
            if (current->data == temp) {
                this->head = current->next;
                delete current;
                current = this->head;
            }
        }
        Node<T>* prev = NULL;
        if (current != NULL) {
            prev = current;
            current = current->next;
        }
        while (current != NULL) {
            if (current->data == temp) {
                Node<T>* temp = current->next;
                delete current;
                prev->next = temp;
                current = temp;
            }
            else {
                prev = current;
                current = current->next;
            }

        }
    }
};

int main() {
    LinkedList<LinkedList<char*>*> l;
    for (char c = 'A'; c <= 'Z'; c++) {
        LinkedList<char*>* ll = new LinkedList<char*>;
        l.append(ll);
        char* cc = new char[2];
        cc[0] = c;
        cc[1] = NULL;
        ll->append(cc);
    }
    ifstream ifs;
    ifs.open("input.dat");
    char constInput[101];
    while (ifs.getline(constInput, 101)) {
        char* input = new char[101];
        int i = 0;
        while (constInput[i] != '\0') {
            input[i] = constInput[i];
            i++;
        }
        input[i] = NULL;
        //cout << input;
        Node<LinkedList<char*>*>* lAdr = l.getHead();
        while(lAdr != NULL) {
            if (input[0] == lAdr->data->getHead()->data[0] || input[0] - 32 == lAdr->data->getHead()->data[0]) {
                break;
            }
            lAdr = lAdr->next;
        }
        //cout << "starting alpha checked" << endl;
        lAdr->data->append(input);
        //cout << "appended" << endl;
        lAdr->data->sort();
        //cout << "sorted" << endl;
        //lAdr->data->print();
    }
    Node<LinkedList<char*>*>* lAdr = l.getHead();
    while (lAdr != NULL) {
        lAdr->data->print();
        lAdr = lAdr->next;
    }
}