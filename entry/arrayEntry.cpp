//
// Created by hu on 2020/8/12.
//

#include <iostream>
#include "sdstructure/linearlist/Array.cpp"
using namespace std;
using namespace SmartDongLib;
void show(Size dim,...){
    va_list ap;
    va_start(ap,dim);
    for (Size i = 0; i < dim ; ++i) {
        cout<<i<<":"<<(char)va_arg(ap,Size )<<endl;
    }
    va_end(ap);
}
void print(Array<Integer> &array){
    cout<<"size:"<<array.elemtotal()<<endl;
    for (int i = 0; i < array.elemtotal(); ++i) {
        cout<< array[i]<<" ";
    }
    cout<<endl;
}
Integer main(){

    SmartDongLib::Array<Integer> array{};
    Size status=array.initArray(3,4,4,3);
    array.assign(8,2,3,1);
    array.assign(9,0,0,0);
    Size e;
    array.value(e,2,3,1);
    cout<<e;
    array.value(e,0,0,0);
    cout<<e;
    cout<<array [ 0];
    array[2]=4;
    array.value(e,0,0,2);
    SmartDongLib::Array<Integer> array2;
    array2.initArray(1,12);
    for (int i = 0; i < array2.elemtotal()/3; ++i) {
        array2[i]=i;
    }
    print(array2);
    array2.copy(1,3,5);
    print(array2);
    cout<<e;
}