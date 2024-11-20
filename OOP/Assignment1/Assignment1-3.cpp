
#include <iostream>
using namespace std;

int main()
{
    char l[10];
	cout << "Enter ten characters: ";
	for (int i = 0; i < 10; i++) {
		cin >> l[i];
	}
	cout << "Input characters are:" << endl;
	for (int i = 0; i < 5; i++) {
		cout << l[i] << " " << l[9-i] << endl;
	}
}

