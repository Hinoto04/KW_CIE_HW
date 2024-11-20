
#include <iostream>
#define MAX_LENGTH 100
using namespace std;

class Student {
private:
    char* name;
    char* studentID;
    double Score;

public:
    Student() {
        this->name = NULL;
        this->studentID = NULL;
        this->Score = NULL;
    }
    Student(char* name, char* id, double score) {
        this->name = name;
        this->studentID = id;
        this->Score = score;
    }

    bool operator>(Student cmp) {
        return this->Score > cmp.Score;
    }

    bool operator< (Student cmp) {
        return this->Score < cmp.Score;
    }

    bool operator== (Student cmp) {
        return this->Score == cmp.Score;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Student ID : " << studentID << endl;
        cout << "Score : " << Score << endl;
        cout << "-----------------------" << endl;
    }

};

class School {
private:
    class Student* student_list;
    int size = 0;

public:
    School() {
        student_list = new Student[MAX_LENGTH];
    }

    void add(Student student) {
        student_list[size] = student;
        size++;
        return;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            student_list[i].print();
        }
        return;
    }

    void sort() {
        for (int i = 0; i < size; i++) {
            int min = i;
            for (int j = i; j < size; j++) {
                if (student_list[min] < student_list[j]) {
                    min = j;
                }
            }
            Student temp = student_list[i];
            student_list[i] = student_list[min];
            student_list[min] = temp;
        }
        return;
    }

    void Aclass() {
        sort();
        int cutline = this->size * 0.3;
        cout << "=====A Class=====" << endl;
        for (int i = 0; i < cutline; i++) {
            student_list[i].print();
        }
        return;
    }

    void Bclass() {
        sort();
        int aCutline = this->size * 0.3;
        int cutline = this->size * 0.7;
        cout << "======B Class======" << endl;
        for (int i = aCutline; i < cutline; i++) {
            student_list[i].print();
        }
        return;
    }
};

bool strCmp(const char* a, const char* b) {
    int i = 0;
    while (true) {
        if (a[i] != b[i]) return false;
        if (a[i] == '\0') return true;
        i++;
    }
}

int main()
{
    School school;
    char input[101];
    while (true) {
        cin >> input;
        if (strCmp(input, "new_student")) {
            char* name = new char[101];
            char* id = new char[101];
            double score;
            cin >> name;
            cin >> id;
            cin >> score;
            Student student = Student(name, id, score);
            school.add(student);
        }
        else if (strCmp(input, "sort_by_score")) {
            school.sort();
        }
        else if (strCmp(input, "print_all")) {
            cout << "=====print=====" << endl;
            school.print();
        }
        else if (strCmp(input, "print_A_grade")) {
            school.Aclass();
        }
        else if (strCmp(input, "print_B_grade")) {
            school.Bclass();
        }
        else if (strCmp(input, "exit")) {
            cout << "Exit the Program";
            return 0;
        }
        else {
            cout << "지정되지 않은 명령입니다." << endl;
        }
    }
}
