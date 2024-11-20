
#include <iostream>
using namespace std;

int main()
{
    cout << "Enter the number: ";
    int n;
    cin >> n;
    for (int j = 4; j >= 0; j--)
    {
        int start = 1;
        for (int i = 0; i < j; i++)
        {
            start *= 10;
        }
        int temp = n % (start*10);
        for (int i = start; i > 0; i /= 10)
        {
            cout << temp / i << "  ";
            temp -= temp / i * i;
        }
        cout << endl;
    }
    
}

