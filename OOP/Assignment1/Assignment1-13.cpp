#include <iostream>
using namespace std;

int main()
{
    char str[101];
    cout << "Enter the string: ";
    cin.getline(str, 100);

    int i = 0;
    while (str[i] != '\0') {
        if (65 <= str[i] && str[i] <= 90) {
            str[i] += 32;
        }
        else if (97 <= str[i] && str[i] <= 122) {
            str[i] -= 32;
        }
        i++;
    }
    cout << "Result: " << str;
}