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

Size main(){

    SmartDongLib::Array<Size> array{};
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
    cout<<e;
}