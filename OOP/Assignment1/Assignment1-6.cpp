
#include <iostream>
using namespace std;

double ceil(double d) {
    if (d >= 0) {
        if (d - (int)d > 0) {
            return (int)d + 1;
        }
        return (int)d;
    }
    else {
        if (d - (int)d < 0) {
            return (int)d - 1;
        }
        return (int)d;
    }
}

double round(double d) {
    if (d >= 0) {
        if (d - (int)d >= 0.5) {
            return (int)d + 1;
        }
        return (int)d;
    }
    else {
        if (d - (int)d <= -0.5) {
            return (int)d - 1;
        }
        return (int)d;
    }
}

double floor(double d) {
    return (int)d;
}

int main()
{
    cout << "Enter the floating-point number: ";
    double n;
    cin >> n;
    cout << "Ceiling: " << ceil(n * 100) / 100 << endl;
    cout << "Floor: " << floor(n * 100) / 100 << endl;
    cout << "Rounding: " << round(n * 100) / 100 << endl;
}
