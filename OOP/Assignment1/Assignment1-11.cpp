
#include <iostream>
using namespace std;

bool multiple(int a, int b) {
    if (a*b == 0) return false;
    if (b % a == 0) return true;
    else return false;
}

int main()
{
    cout << "Enter the 1st number: ";
    int a;
    cin >> a;
    cout << "Enter the 2nd number: ";
    int b;
    cin >> b;
    cout << "multiple(" << a << "," << b << "): ";
    cout << (multiple(a, b) ? "true" : "false");
    cout << endl;
}