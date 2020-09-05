//
// Created by hu on 2020/8/16.
//
#include "tsMatrix.cpp"
#include <iostream>
using namespace  std;
using namespace SmartDongLib;
int main(){

    Array<triple<int>> array;
    int row =6,col =6;
    array.initArray(1,row * col);
    int tnum=8;
    array[0] =triple<int> (0,1,12);
    array[1] =triple<int> (0,2,9);
    array[2] =triple<int> (2,0,-3);
    array[3] =triple<int> (2,5,14);
    array[4] =triple<int> (3,2,24);
    array[5] =triple<int> (4,1,18);
    array[6] =triple<int> (5,0,15);
    array[7] =triple<int> (5,3,-7);
    tsMatrix<int> matrix(row,col,tnum,array);
    tsMatrix<int>a =matrix.transpose();
    cout<<"&array"<<&array<<endl;
    cout<<"&matrix"<<&matrix.data_<<endl;
    cout<<"&a"<<&a.data_<<endl;
    cout<<"------------------------"<<endl;
    cout<<a.rownum_<<a.colnum_<<a.tnum_<<endl;
    for (int i = 0; i < a.tnum_; ++i) {
        cout<<a.data_[i].rowindex<<" "<<a.data_[i].colindex<<" "<<a.data_[i].elem<<endl;
    }
    cout<<"-------------------------\n";
    Array<triple<int>> Marray;
    int Mrow =3,Mcol =4;
    Marray.initArray(1,Mrow * Mcol);
    int Mtnum=4;
    Marray[0] =triple<int> (0,0,3);
    Marray[1] =triple<int> (0,3,5);
    Marray[2] =triple<int> (1,1,-1);
    Marray[3] =triple<int> (2,0,2);
    tsMatrix<int> Mmatrix(Mrow,Mcol,Mtnum,Marray);
//------------------------------
    Array<triple<int>> Narray;
    int Nrow =4,Ncol =2;
    Narray.initArray(1,Nrow * Ncol);
    int Ntnum=4;
    Narray[0] =triple<int> (0,1,2);
    Narray[1] =triple<int> (1,0,1);
    Narray[2] =triple<int> (2,0,-2);
    Narray[3] =triple<int> (2,1,4);
    tsMatrix<int> Nmatrix(Nrow,Ncol,Ntnum,Narray);
    tsMatrix<int> Qmatrix = Mmatrix * Nmatrix;
    tsMatrix<int> QQmatrix ( Qmatrix*2) ;
    QQmatrix.data_[2].colindex=0;
    Qmatrix = Qmatrix + QQmatrix ;
    for (int i  = 0; i < Qmatrix.tnum_ ; ++i) {
        cout<<Qmatrix.data_[i].rowindex<<" "<<Qmatrix.data_[i].colindex<<" "<<Qmatrix.data_[i].elem<<endl;

    }

    cout<<"finish"<<endl;
}