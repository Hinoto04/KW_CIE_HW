
#include <iostream>
#define MAX_LENGTH 256
using namespace std;

template <typename T>
class stack {
private :
    T data[MAX_LENGTH];
    int _top;

public:
    stack() {
        _top = -1;
    }
    void push(T input) {
        data[_top + 1] = input;
        _top += 1;
    }
    T pop() {
        T result = data[_top];
        _top -= 1;
        return result;
    }
    int size() {
        return _top + 1;
    }
    bool empty() {
        if (size() == 0) return 1;
        else return 0;
    }
    T top() {
        T result = data[_top];
        return result;
    }
    void print() {
        if (_top != -1) {
            //cout << "[";
            for (int i = 0; i < _top; i++) {
                //cout << data[i] << ", ";
            }
            //cout << data[_top] << "]" << endl;
        }
        else {
            //cout << "[ ]" << endl;
        }
        
    }
};

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void removeBlank(char* str) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            int j = 0;
            while (str[i + j] != '\0') {
                str[i + j] = str[i + j + 1];
                j++;
            }
        }
        i++;
    }
    return;
}

void postfix(char* str, char** result) {
    stack<char> oper;
    int i = 0;
    int idx = -1;
    int numberPtr = 0;
    while (str[i] != '\0') {
        if ('0' <= str[i] && str[i] <= '9') {
            if (numberPtr == 0) idx++;
            result[idx][numberPtr] = str[i];
            numberPtr++;
            //cout << "Number : " << str[i] << endl;
        }
        else {
            numberPtr = 0;
            if (oper.empty() || str[i] == '(') {
                oper.push(str[i]);
            }
            else if (str[i] == ')') {
                while (oper.top() != '(') {
                    idx++;
                    result[idx][0] = oper.top();
                    oper.pop();
                }
                oper.pop();
            }
            else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*') {
                numberPtr = 0;
                if (priority(oper.top()) < priority(str[i])) {
                    oper.push(str[i]);
                }
                else {
                    while (!oper.empty() && priority(oper.top()) >= priority(str[i])) {
                        idx++;
                        result[idx][0] = oper.top();
                        oper.pop();
                    }
                    oper.push(str[i]);
                }
            }
            //cout << "Oper : " << str[i] << endl;
        }
        i++;
    }
    while (!oper.empty()) {
        idx++;
        result[idx][0] = oper.top();
        oper.pop();
    }
    return;
}

int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

int strToint(char* str) {

    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    int result = 0;
    for (int i = 0; i < length; i++) {
        result += (str[i] - '0') * power(10, length - i - 1);
    }
    return result;
}

double execute(char** postfixed) {
    stack<int> numbers;

    int i = 0;
    while (postfixed [i] [0] != NULL) {
        numbers.print();
        if ('0' <= postfixed[i][0] && postfixed[i][0] <= '9') {
            numbers.push((int)strToint(postfixed[i]));
        }
        else {
            int a = numbers.pop();
            int b = numbers.pop();
            if (postfixed[i][0] == '+') {
                numbers.push(b + a);
            }
            else if (postfixed[i][0] == '-') {
                numbers.push(b - a);
            }
            else if (postfixed[i][0] == '*') {
                numbers.push(b * a);
            }
            else if (postfixed[i][0] == '/') {
                numbers.push(b / a);
            }
        }
        i++;
    }
    return numbers.pop();
}

int main()
{
    cout << "Enter the formula : ";
    char input[MAX_LENGTH];
    cin.getline(input, MAX_LENGTH);

    removeBlank(input);
    //cout << input;

    char** result = new char* [MAX_LENGTH];
    for (int i = 0; i < MAX_LENGTH; i++) {
        result[i] = new char[4];
        for (int j = 0; j < 4; j++) {
            result[i][j] = NULL;
        }
    }

    postfix(input, result);

    /*
    int i = 0;
    while (result[i][0] != NULL) {
        cout << result[i] << " ";
        i++;
    }
    cout << endl;
    */
    cout << "Result : ";
    cout << execute(result);

    return 0;
}
