//
// Created by hu on 2020/8/16.
//
#include "tsMatrix.cpp"
#include <iostream>
using namespace  std;
using namespace SmartDongLib;
Size main(){

    Array<triple<Size>> array;
    Size row =6,col =6;
    array.initArray(1,row * col);
    Size tnum=8;
    array[0] =triple<Size> (0,1,12);
    array[1] =triple<Size> (0,2,9);
    array[2] =triple<Size> (2,0,-3);
    array[3] =triple<Size> (2,5,14);
    array[4] =triple<Size> (3,2,24);
    array[5] =triple<Size> (4,1,18);
    array[6] =triple<Size> (5,0,15);
    array[7] =triple<Size> (5,3,-7);
    tsMatrix<Size> matrix(row,col,tnum,array);
    tsMatrix<Size>a =matrix.transpose();
    cout<<"&array"<<&array<<endl;
    cout<<"&matrix"<<&matrix.data_<<endl;
    cout<<"&a"<<&a.data_<<endl;
    cout<<"------------------------"<<endl;
    cout<<a.rownum_<<a.colnum_<<a.tnum_<<endl;
    for (Size i = 0; i < a.tnum_; ++i) {
        cout<<a.data_[i].rowindex<<" "<<a.data_[i].colindex<<" "<<a.data_[i].elem<<endl;
    }
    cout<<"-------------------------\n";
    Array<triple<Size>> Marray;
    Size Mrow =3,Mcol =4;
    Marray.initArray(1,Mrow * Mcol);
    Size Mtnum=4;
    Marray[0] =triple<Size> (0,0,3);
    Marray[1] =triple<Size> (0,3,5);
    Marray[2] =triple<Size> (1,1,-1);
    Marray[3] =triple<Size> (2,0,2);
    tsMatrix<Size> Mmatrix(Mrow,Mcol,Mtnum,Marray);
//------------------------------
    Array<triple<Size>> Narray;
    Size Nrow =4,Ncol =2;
    Narray.initArray(1,Nrow * Ncol);
    Size Ntnum=4;
    Narray[0] =triple<Size> (0,1,2);
    Narray[1] =triple<Size> (1,0,1);
    Narray[2] =triple<Size> (2,0,-2);
    Narray[3] =triple<Size> (2,1,4);
    tsMatrix<Size> Nmatrix(Nrow,Ncol,Ntnum,Narray);
    tsMatrix<Size> Qmatrix = Mmatrix * Nmatrix;
    tsMatrix<Size> QQmatrix ( Qmatrix*2) ;
    QQmatrix.data_[2].colindex=0;
    Qmatrix = Qmatrix + QQmatrix ;
    for (Size i  = 0; i < Qmatrix.tnum_ ; ++i) {
        cout<<Qmatrix.data_[i].rowindex<<" "<<Qmatrix.data_[i].colindex<<" "<<Qmatrix.data_[i].elem<<endl;

    }

    cout<<"finish"<<endl;
}