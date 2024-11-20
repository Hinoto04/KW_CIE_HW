
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

    struct Node {
        T data;
        Node* next;
    };

private:
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    Node* getHead() {
        return this->head;
    }

    void append(T data) {
        Node* temp = new Node;
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
        Node* current = this->head;
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
        Node* start = this->head;
        while (start != NULL) {
            Node* max = start;
            Node* current = start;
            while (current != NULL) {
                if (current->data > max->data) {
                    max = current;
                }
                current = current->next;
            }
            int temp = max->data;
            max->data = start->data;
            start->data = temp;
            start = start->next;
        }
    }

    void dlt(int temp) {
        Node* current = this->head;
        while (current != NULL && current->data == temp) {
            if (current->data == temp) {
                this->head = current->next;
                delete current;
                current = this->head;
            }
        }
        Node* prev = NULL;
        if (current != NULL) {
            prev = current;
            current = current->next;
        }
        while (current != NULL) {
            if (current->data == temp) {
                Node* temp = current->next;
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

int strCmp(char* a, const char* b) {
    int i = 0;
    while (true) {
        if (a[i] != b[i]) return false;
        if (a[i] == NULL) return true;
        i++;
    }
}

int main()
{
    LinkedList<int> list;
    char input[101];
    while (true) {
        cin >> input;
        if (strCmp(input, "insert")) {
            int temp;
            cin >> temp;
            list.append(temp);
            list.sort();
            list.print();
        }
        else if (strCmp(input, "delete")) {
            int temp;
            cin >> temp;
            list.dlt(temp);
            list.print();
        }
    }
}
