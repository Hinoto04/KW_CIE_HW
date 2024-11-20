
#include <iostream>
#include <string>
#define MAX_LENGTH 1001
using namespace std;

template <typename T>
class Node {
private:
    Node* m_left;
    Node* m_right;
    T m_Data;
    int depth;
public:
    Node() {
        this->m_left = NULL;
        this->m_right = NULL;
        this->depth = 0;
    }
    Node(T data, int d) {
        this->m_left = NULL;
        this->m_right = NULL;
        this->m_Data = data;
        this->depth = d;
    }
    ~Node() {
        delete this->m_left;
        delete this->m_right;
    }
    T getData() { return this->m_Data; }
    int getDepth() { return this->depth; }
    Node* getLeft() { return this->m_left; }
    Node* getRight() { return this->m_right; }
    void setLeft(Node* next) { this->m_left = next; }
    void setRight(Node* next) { this->m_right = next; }
    void build(T arr[], int start, int end) {
        //if (start > end) return;
        /*cout << "Data : " << this->m_Data;
        cout << " Depth : " << this->depth;
        cout << " Built In" << endl;*/
        int mid = (start + end) / 2;
        int midmid1 = (start + mid - 1) / 2;
        int midmid2 = (mid + 1 + end) / 2;
        if (start <= mid - 1) {
            this->m_left = new Node<T>(midmid1, this->depth + 1);
            this->m_left->m_Data = arr[midmid1];
            this->m_left->build(arr, start, mid - 1);
        }
        if (mid + 1 <= end) {
            this->m_right = new Node<T>(midmid2, this->depth + 1);
            this->m_right->m_Data = arr[midmid2];
            this->m_right->build(arr, mid + 1, end);
        }
        return;
    }
    void print(int d) {
        if (d > this->depth) {
            if (this->m_right != NULL) this->m_right->print(d);
            else cout << endl;
            for (int i = 0; i < this->depth*5; i++) {
                cout << " ";
            }
            cout << this->m_Data << endl;
            if (this->m_left != NULL) this->m_left->print(d);
            else cout << endl;
        }
        else {
            for (int i = 0; i < this->depth * 5; i++) {
                cout << " ";
            }
            cout << this->m_Data << endl;
        }
    }
};

int power(int base, int exp) {
    int r = 1;
    for (int i = 0; i < exp; i++) r *= base;
    return r;
}

template <typename T>
class BST {
private:
    Node<T>* m_root;
    int depth;
public:
    BST() { 
        this->m_root = NULL;
        this->depth = 0;
    }
    ~BST() { delete this->m_root; }
    void build(T arr[], int start, int end) {
        int r = 0;
        int i = 0;
        while (true) {
            r += power(2, i);
            if (r > (end - start + 1)) {
                break;
            }
            i++;
        }
        this->depth = i;
        //cout << this->depth;
        this->m_root->build(arr, start, end);
    }
    void insert(T n, int depth) {
        this->m_root = new Node<T>(n, depth);
    }
    void printTree() {
        this->m_root->print(this->depth);
    }
};

int main()
{
    cout << "input array = ";
    char str[MAX_LENGTH];
    char* context;
    int l[MAX_LENGTH];
    cin.getline(str, MAX_LENGTH);
    int idx = 0;
    char* ptr = strtok_s(str, " ", &context);
    while (true) {
        if (ptr == NULL) break;
        //cout << ptr;
        l[idx] = stoi(ptr, nullptr, 10);
        ptr = strtok_s(NULL, " ", &context);
        idx++;
    }
    idx--;
    //int l[10] = { 12, 21, 37, 46, 59, 65, 74, 83, 89, 94 };
    /*cout << idx << endl;
    for (int i = 0; i < idx; i++) {
        cout << l[i] << " ";
    }
    cout << endl;*/

    BST<int> bst;
    int mid = (0 + idx) / 2;
    bst.insert(l[mid], 0);
    bst.build(l, 0, idx);
    bst.printTree();
}