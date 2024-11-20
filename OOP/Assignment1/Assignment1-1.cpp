
#include <iostream>
using namespace std;

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

int main()
{
    int l[5] = { 0, };
	int sum = 0;
	cout << "Enter the five numbers : ";
	for (int i = 0; i < 5; i++)
	{
		cin >> l[i];
		sum += l[i];
	}
	int min = l[0];
	int max = l[0];
	for (int i = 0; i < 5; i++)
	{
		if (min > l[i]) {
			min = l[i];
		}
		if (max < l[i]) {
			max = l[i];
		}
	}
	cout << "MIN: " << min << endl;
	cout << "MAX: " << max << endl;
	cout << "AVG: " << round((double)sum / 5) << endl;
}

