
#include <iostream>
using namespace std;

int main()
{
    cout << "Enter the string : ";
    char input[101];
    cin >> input;
    cout << "Enter the delimiter : ";
    char delimiter[11];
    cin >> delimiter;

    int start = 0;
    int dStart = -1;

    int i = 0;
    while (delimiter[i] != '\0') {
        i++;
    }
    int dLength = i;
    
    i = 0;
    while (input[i]!='\0') {
        if (dStart == -1) {
            if (input[i] == delimiter[0]) {
                dStart = i;
            }
        }
        else {
            if (i - dStart == dLength) {
                for (int j = start; j < dStart; j++) {
                    cout << input[j];
                }
                cout << endl;
                start = i;
                dStart = -1;
            }
            if (input[i] != delimiter[i - dStart]) {
                dStart = -1;
            }
        }

        i++;
    }
    for (int j = start; input[j]!='\0'; j++) {
        cout << input[j];
    }
    cout << endl;
}
