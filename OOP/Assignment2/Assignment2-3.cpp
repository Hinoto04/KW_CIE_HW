
#include <iostream>
using namespace std;

void quicksort(int* arr, int left, int right) {
    if (left >= right) return;
    int pivot = left;
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (arr[i] <= arr[pivot]) {
            i++;
        }
        while (arr[j] >= arr[pivot] && j > left) {
            j--;
        }
        if (i > j) {
            int temp = arr[j];
            arr[j] = arr[pivot];
            arr[pivot] = temp;
        }
        else {
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
        quicksort(arr, left, j - 1);
        quicksort(arr, j + 1, right);
    }
}

int main()
{
    srand(time(NULL));

    int** matrix;
    matrix = new int*[10];
    for (int i = 0; i < 10; i++) {
        matrix[i] = new int[10];
    }
    int sum[10] = { 0, };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = rand() % 101;
            sum[i] += matrix[i][j];
        }
    }

    cout << "Original Matrix:" << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }

    for (int i = 0; i < 10; i++) {
        quicksort(matrix[i], 0, 9);
        for (int j = 0; j < 5; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][9 - j];
            matrix[i][9 - j] = temp;
        }
    }

    cout << endl << "Sort by Row (Descending Order):" << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << matrix[i][j] << '\t';
        }
        cout << "| Sum: ";
        cout.width(4);
        cout << sum[i];
        cout << endl;
    }

    cout << endl << "Sort by Sum (Ascending order):" << endl;
    for (int i = 0; i < 10; i++) {
        int min = i;
        for (int j = i; j < 10; j++) {
            if (sum[j] < sum[min]) {
                min = j;
            }
        }
        int temp = sum[i];
        sum[i] = sum[min];
        sum[min] = temp;
        int* ttemp = matrix[i];
        matrix[i] = matrix[min];
        matrix[min] = ttemp;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << matrix[i][j] << '\t';
        }
        cout << "| Sum: ";
        cout.width(4);
        cout << sum[i];
        cout << endl;
    }
    
}
