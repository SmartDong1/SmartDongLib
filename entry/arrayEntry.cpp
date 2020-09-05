//
// Created by hu on 2020/8/12.
//

#include <iostream>
#include "sdstructure/linearlist/Array.cpp"
using namespace std;
using namespace SmartDongLib;
void show(int dim,...){
    va_list ap;
    va_start(ap,dim);
    for (int i = 0; i < dim ; ++i) {
        cout<<i<<":"<<(char)va_arg(ap,int )<<endl;
    }
    va_end(ap);
}

int main(){

    SmartDongLib::Array<int> array{};
    int status=array.initArray(3,4,4,3);
    array.assign(8,2,3,1);
    array.assign(9,0,0,0);
    int e;
    array.value(e,2,3,1);
    cout<<e;
    array.value(e,0,0,0);
    cout<<e;
    cout<<array [ 0];
    array[2]=4;
    array.value(e,0,0,2);
    cout<<e;
}