
#include <iostream>
using namespace std;

int M_pat[2][2] = { {1, 1}, {1, -1} };

void printArray(int** array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout.width(3);
            cout << array[i][j];
        }
        cout << endl;
    }
}

int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

void Hadamard(int** result, int size) {
    if (size == 0) {
        result[0][0] = 1;
    }
    else {
        int e = power(2, size - 1);
        int** prevMat = new int* [e];
        for (int i = 0; i < e; i++) {
            prevMat[i] = new int[e];
        }
        //cout << e << endl;
        Hadamard(prevMat, size - 1);
        for (int b1 = 0; b1 < 2; b1++) {
            for (int b2 = 0; b2 < 2; b2++) {
                for (int i = 0; i < e; i++) {
                    for (int j = 0; j < e; j++) {
                        result[b1*e+i][b2*e+j] = prevMat[i][j]*M_pat[b1][b2];
                    }
                }
            }
        }
        //printArray(result, e);
    }
    return;
}

int main()
{
    cout << "Input Number : ";
    int input;
    cin >> input;

    int e = power(2, input);
    int** prevMat = new int* [e];
    for (int i = 0; i < e; i++) {
        prevMat[i] = new int[e];
    }
    Hadamard(prevMat, input);
    printArray(prevMat, power(2, input));
}
