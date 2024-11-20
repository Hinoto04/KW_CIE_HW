
#include <iostream>
using namespace std;

int Fibonacci_iter(int n) {
    if (n == 0) return 0;
    int prevprev = 0;
    int prev = 1;
    int now = 1;
    for (int i = 0; i < n-1; i++)
    {
        now = prevprev + prev;
        prevprev = prev;
        prev = now;
    }
    return now;
}

int Fibonacci_rec(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return Fibonacci_rec(n-1) + Fibonacci_rec(n - 2);
}

int main()
{
    cout << "Enter the number: ";
    int a;
    cin >> a;
    cout << "Fibonacci_iter(" << a << "): " << Fibonacci_iter(a) << endl;
    cout << "Fibonacci_rec(" << a << "): " << Fibonacci_rec(a) << endl;
}
