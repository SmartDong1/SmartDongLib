//
// Created by Administrator on 2020/12/6.
//


#include<iostream>
#include "sdstructure/linearlist/Matrix.cpp"
#include <ctime>
#include <malloc.h>
#include<algorithm>
using namespace std;
using namespace SmartDongLib;

template<class T>
void print(Matrix<T> a){
    for (int i = 0; i < a.getTheRows(); ++i) {
        for (int j = 0; j < a.getTheCols(); ++j) {
            cout<< a(i,j)<<" ";
        }
        cout << endl;
    }
}
int main() {
    Matrix<int> matrix1(2,1);
    Matrix<int> matrix2(1,3);
    matrix1(0,0)=1;
    matrix1(1,0)=2;
    matrix2(0,0)=11;
    matrix2(0,1)=24;
    matrix2(0,2)=36;
    Matrix<int> plusIntergerMatrix(matrix1);
    plusIntergerMatrix= matrix1 - 3;
//    print(plusIntergerMatrix) ;
    Matrix<int> plusMatrix(2,1);
    plusMatrix = plusIntergerMatrix - matrix1;
    plusIntergerMatrix +=matrix1;
//    print(plusMatrix) ;
    Matrix<int> multiMatrix(2,3);
    multiMatrix = matrix1 * matrix2;
    multiMatrix=multiMatrix.transposition();
    multiMatrix.rowSwap(0,1);
//    print(multiMatrix);

    Matrix<double> A(3,6);
    A(0,0) =1;A(0,1) =1;A(0,2) =1;A(0,3) =1;
    A(1,0) =1;A(1,1) =1;A(1,4) =1;
    A(2,1) =1;A(2,2) =1;A(2,5) =1;
    UnitMatrix<double> a(3);
    print(A.simplyTransform());
    cout<<"-----------------------\n";
    print(A.divideMatrix(0,3,0,3).rightJoin(A.divideMatrix(0,3,3,6)));
    cout<<"-----------------------\n";
    Matrix<double> B(3, 3);
    B(0,0) =1;B(0,1) =1;B(0,2) =1;
    B(1,0) =1;B(1,1) =1;
    B(2,1) =1;B(2,2) =1;
    DiagonalMatrix<double> diagonalMatrix3(3);
    diagonalMatrix3(0,0)=1; diagonalMatrix3(1,1)=2; diagonalMatrix3(2,2)=3;
    Matrix<double> Binverse=B.inverse();
    print(     Binverse * diagonalMatrix3);
}