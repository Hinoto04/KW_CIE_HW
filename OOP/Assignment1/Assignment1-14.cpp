
#include <iostream>
using namespace std;

void measures(int n) {
	int nn[100] = { 0, };
	int idx = 0;
	for (int i = 1; i <= n / 2; i++)
	{
		if (n % i == 0) {
			nn[idx] = i;
			idx++;
		}
	}
	for (int i = 0; i < idx-1; i++) {
		cout << nn[i] << " + ";
	}
	cout << nn[idx-1];
	return;
}

bool Perfect(int n) {
	int sum = 0;
	for (int i = 1; i <= n/2; i++)
	{
		if(n%i==0) {
			sum += i;
		}
	}
	if (n == sum) return 1;
	else return 0;
}

int main()
{
	cout << "Perfect numbers between 1 and 100000: " << endl;
	for (int i = 1; i <= 100000; i++) {
		if (Perfect(i)) {
			cout << i << " = ";
			measures(i);
			cout << endl;
		}
	}
}
