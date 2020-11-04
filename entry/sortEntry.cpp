//
// Created by Administrator on 2020/11/2.
//

#include<iostream>
#include "sdalgorithm/util/sort.h"
#include <cmath>
#include <vector>
using namespace std;
using namespace SmartDongLib;
void print(int a[],int size){
    for (int i = 0; i < size; ++i) {
        cout<< a[i]<<"  ";
    }
    cout<<endl;
};
class C1{
public:
    C1(int a){a_=a;}
    int a_;
};
int main(){
    int a[10] ={9,34,24,56,31,24,66,3,45,98};
    Sort::quickSort(a,a+9,[](int x,int y){return abs(x-24)<=abs(y-24);});
//    Sort::quickSort(a,a+9,[](int x,int y){return x<y;});

//        Sort::quickSort(a,a+9,[](int x,int y){return x>=y;});

//    auto aa=C1(2);
    Sort::quickSort(a, a + 9);

    print(a,10);
}