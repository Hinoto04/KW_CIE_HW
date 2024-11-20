
#include <iostream>
using namespace std;

long long reverse(long long n) {
    long long reversed = 0;
    long long p = 1;
    while (n / p > 0) {
        p *= 10;
    }
    long long i = 1;
    while (p > 1) {
        p /= 10;
        int j = n / p;
        n -= j * p;
        reversed += j * i;
        i *= 10;
    }

    return reversed;
}

int main()
{
    long long n;
    cout << "Enter the number: ";
    cin >> n;
    
    cout << "Reversed number: " << reverse(n) << endl;
}
