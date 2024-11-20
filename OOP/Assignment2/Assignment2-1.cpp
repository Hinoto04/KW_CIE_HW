
#include <iostream>
using namespace std;

int main()
{
    //rand함수의 동일 숫자 출력 방지
    srand(time(NULL));

    //배열 길이 설정
    int SoA = rand() % 16 + 5;
    cout << "Size of the array : " << SoA << endl;

    //배열 동적 할당
    int* a = new int(SoA);
    int* max = &a[0];
    int* min = &a[0];
    
    //난수 배열에 넣고, 최대/최소 검사
    cout << "Random numbers : ";
    for (int i = 0; i < SoA; i++) {
        a[i] = rand() % 101;
        cout << a[i] << " ";
        if (*max < a[i]) {
            max = &a[i];
        }
        if (*min > a[i]) {
            min = &a[i];
        }
    }
    cout << endl << endl;

    cout << "Maximum value: " << *max;
    cout << ", Address: " << max << endl;
    cout << "Minimum value: " << *min;
    cout << ", Address: " << min << endl;

}
