
#include <iostream>
using namespace std;

//배열을 출력하는 함수
void printArray(int* arr, int size) {
    for (int i = 0; i < size-1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[size - 1];
    cout << endl;
}

//병합 정렬의 병합을 담당하는 함수
void merge(int* arr, int left, int right) {
    int mid = (left + right) / 2;
    int lL = mid - left + 1;
    int rL = right - mid;
    int* temp1 = new int[lL];
    int* temp2 = new int[rL];

    for (int i = 0; i < lL; i++) {
        temp1[i] = arr[left + i];
    }
    for (int j = 0; j < rL; j++) {
        temp2[j] = arr[mid + 1 + j];
    }

    int i1 = 0, i2 = 0, iArr = left;
    
    //병합하는 두 문제는 각각의 안에서 정렬되어 있다.
    while (i1 < lL && i2 < rL) {
        if (temp1[i1] <= temp2[i2]) {
            arr[iArr] = temp1[i1];
            i1++;
        }
        else {
            arr[iArr] = temp2[i2];
            i2++;
        }
        iArr++;
    }

    while (i1 < lL) {
        arr[iArr] = temp1[i1];
        i1++;
        iArr++;
    }
    
    while (i2 < rL) {
        arr[iArr] = temp2[i2];
        i2++;
        iArr++;
    }

    //cout << "l : " << left << ", r : " << right << endl;
    //printArray(arr, 10);
   
}

//병합 정렬의 분할을 담당하는 함수
void mergesort(int* arr, int left, int right) {
    if (left < right) { //문제의 크기가 0이 되면 실행하지 않음
        int mid = (left + right) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, right);
    }
}

//퀵 정렬을 담당하는 함수
void quicksort(int* arr, int left, int right) {
    if (left >= right) return;
    int pivot = left; //피벗 지정
    int i = left + 1;
    int j = right;

    //피벗이 꼬일 때까지 반복
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

//이진 탐색 함수
int binarysearch(int target, int* arr, int left, int right) {
    int mid = (left + right) / 2;
    if (left > right) return -1;
    if (arr[mid] == target) {
        return mid;
    }
    if (arr[mid] > target) {
        return binarysearch(target, arr, left, mid - 1);
    }
    return binarysearch(target, arr, mid + 1, right);
}

int main()
{
    srand(time(NULL));
    //난수 도출
    cout << "Random values : ";
    int l[10] = { 0, };
    for (int i = 0; i < 10; i++) {
        l[i] = rand() % 101;
        cout << l[i] << " ";
    }
    cout << endl;
    //정렬 방법 선택
    cout << "Select sorting method (1: Quick Sort, 2: Merge Sort) : ";
    int method;
    cin >> method;
    if (method == 1) {
        cout << "Sorting numbers (Quick Sort) : ";
        quicksort(l, 0, 9);
        printArray(l, 10);
    }
    else {
        cout << "Sorting numbers (Merge Sort) : ";
        mergesort(l, 0, 9);
        printArray(l, 10);
    }
    //이진 탐색에서 탐색할 수
    cout << "Enter a value to search : ";
    int input;
    cin >> input;
    int result = binarysearch(input, l, 0, 9);
    if (result != -1) {
        cout << "Searched number index : " << result << endl;
        return 0;
    }
    int newl[11];
    int i = 0;
    while (l[i] < input && i < 10) {
        newl[i] = l[i];
        i++;
    }
    newl[i] = input;
    while (i < 11) {
        newl[i + 1] = l[i];
        i++;
    }
    cout << "Update numbers : ";
    printArray(newl, 11);
}
