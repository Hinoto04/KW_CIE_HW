
#include <iostream>
using namespace std;

int gcd(int x, int y) {
    x = (x > 0) ? x : -x;
    y = (y > 0) ? y : -y;
    if (y == 0) {
        return x;
    }
    else {
        return gcd(y, x % y);
    }
}

int lcm(int x, int y) {
    return x * y / gcd(x, y);
}

int main()
{
    cout << "Enter the 1st number: ";
    int a;
    cin >> a;
    cout << "Enter the 2nd number: ";
    int b;
    cin >> b;
    cout << "lcm(" << a << "," << b << "): ";
    cout << lcm(a, b);
}