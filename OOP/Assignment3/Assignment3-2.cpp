
#include <iostream>
using namespace std;

//행렬 클래스 구현
class Matrix {
private:
    double data[4][4];
public:
    Matrix() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->data[i][j] = 0;
            }
        }
    };
    ~Matrix() {};

    //값 할당, 값이 사라지지 않도록 값을 복사하여 넣는 방식으로 진행
    void setValue(double arr[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = arr[i][j];
            }
        }
    }

    void display() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << this->data[i][j] << " ";
            }
            cout << endl;
        }
    }

    //행렬 끼리 연산
    Matrix operator+(Matrix& mtx) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dt[i][j] = this->data[i][j] + mtx.data[i][j];
            }
        }
        result.setValue(dt);
        return result;
    }

    Matrix operator-(Matrix& mtx) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dt[i][j] = this->data[i][j] - mtx.data[i][j];
            }
        }
        result.setValue(dt);
        return result;
    }

    Matrix operator*(Matrix& mtx) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                double s = 0;
                for (int k = 0; k < 4; k++) { //행렬 곱 계산법
                    s += this->data[i][k] * mtx.data[k][j];
                    //각 위치에서 한쪽은 행 이동, 반대는 열 이동
                }
                dt[i][j] = s;
            }
        }
        result.setValue(dt);
        return result;
    }

    //스칼라와의 연산
    Matrix operator+(int Scalar) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dt[i][j] = this->data[i][j] + Scalar;
            }
        }
        result.setValue(dt);
        return result;
    }

    Matrix operator-(int Scalar) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dt[i][j] = this->data[i][j] - Scalar;
            }
        }
        result.setValue(dt);
        return result;
    }

    Matrix operator*(int Scalar) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dt[i][j] = this->data[i][j] * Scalar;
            }
        }
        result.setValue(dt);
        return result;
    }

    Matrix operator/(int Scalar) {
        Matrix result = Matrix();
        double dt[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dt[i][j] = this->data[i][j] / Scalar;
            }
        }
        result.setValue(dt);
        return result;
    }

};

int main()
{
    Matrix mat1, mat2;

    double arr1[4][4] = {
        {0,0,0,0},
        {1,1,1,1},
        {2,2,2,2},
        {3,3,3,3}
    };
    double arr2[4][4] = {
        {0,1,2,3},
        {0,1,2,3},
        {0,1,2,3},
        {0,1,2,3}
    };

    int scalar = 3;

    mat1.setValue(arr1);
    mat2.setValue(arr2);

    Matrix mat3 = mat1 * scalar;

    cout << "Mat1 : " << endl;
    mat1.display();

    /*cout << "Mat2 : " << endl;
    mat2.display();*/

    cout << "Mat3 : " << endl;
    mat3.display();
}
