
#include <iostream>
#include <ctime>
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
	int seed = time(NULL);
	for (int i = 0; i < 5; i++)
	{
		int sum = 0;
		for (int j = 0; j < 10; j++)
		{
			seed = 2937845 * seed + 86745034;
			int temp = seed % 99 + 1;
			if (temp < 0)
			{
				temp *= -1;
			}
			sum += temp;
			cout.width(3);
			cout << temp << " ";
		}
		cout << "| ";
		cout.width(3);
		cout << sum << " | ";
		cout.width(2);
		cout << round((double)sum / 10) << endl;
	}
}

