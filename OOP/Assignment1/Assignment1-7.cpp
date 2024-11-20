
#include <iostream>
using namespace std;

int power(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    if (exp == 1) {
        return base;
    }
    else {
        return base * power(base, exp - 1);
    }
}

int main()
{
    cout << "Enter the base: ";
    int b;
    cin >> b;
    int e;
    cout << "Enter the exponent: ";
    cin >> e;
    cout << "power(" << b << "," << e << "): "
        << power(b, e);
}
