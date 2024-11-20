
#include <iostream>
using namespace std;

class Student {
private:
    char* name;
    char* studentId;
    double assignmentScore;
    double examScore;
    double attendance;
    double finalScore;

public:
    Student(char* name, char* id, double aScore, double eScore, double att) {
        this->name = name;
        this->studentId = id;
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
    }
    bool isNameCorrect(char* name) {
        int i = 0;
        while (true) {
            if (name[i] != this->name[i]) return false;
            if (name[i] == '\0') return true;
            i++;
        }
    }
    void changeScores(double aScore, double eScore, double att) {
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
    }
    void print() {
        cout << "Name : " << this->name << endl;
        cout << "Student ID : " << this->studentId << endl;
        cout << "Final Score : " << this->assignmentScore * 0.4
            + this->examScore * 0.5 + this->attendance * 0.1 << endl;
        cout << "--------------------" << endl;
    }
};

struct Node {
    Student* data;
    Node* next;
};

class LinkedList {
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

    void append(Student* data) {
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
        Node* current = this->head;
        while (current != NULL) {
            current->data->print();
            current = current->next;
        }
    }
};

int strcmp(char* a, const char* b) {
    int i = 0;
    while (true) {
        if (a[i] != b[i]) return false;
        if (a[i] == NULL) return true;
        i++;
    }
}

Node* find(LinkedList l) {
    char name[101];
    cin >> name;
    Node* current;
    current = l.getHead();
    while (current != NULL) {
        if (current->data->isNameCorrect(name)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


int main()
{
    LinkedList l;
    
    while (true) {
        char input[101];

        cin >> input;
        if (strcmp(input, "insert")) {
            char *name = new char[101];
            char *id = new char[101];
            double aScore;
            double eScore;
            double att;
            cin >> name;
            cin >> id;
            cin >> aScore;
            cin >> eScore;
            cin >> att;
            Student* s = new Student(name, id, aScore, eScore, att);
            l.append(s);
        }
        else if (strcmp(input, "find")) {
            cout << "=====find=====" << endl;
            Node* result = find(l);
            if (result != NULL) {
                result->data->print();
            }
            else {
                cout << "not found" << endl;
            }
        }
        else if(strcmp(input, "change")) {

            Node* target = find(l);

            double aScore;
            double eScore;
            double att;
            cin >> aScore;
            cin >> eScore;
            cin >> att;
            
            target->data->changeScores(aScore, eScore, att);
        }
        else if (strcmp(input, "print")) {
            cout << "=====print=====" << endl;
            l.print();
        }
        else if (strcmp(input, "exit")) {
            cout << "Exit the program";
            return 0;
        }
        else {
            cout << "지정되지 않은 명령입니다." << endl;
        }
    }
}
