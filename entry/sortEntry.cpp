//
// Created by Administrator on 2020/11/2.
//

#include<iostream>
#include "sdalgorithm/util/sort.h"
#include <cmath>

using namespace std;
using namespace SmartDongLib;
void print(int a[],int size){
    for (int i = 0; i < size; ++i) {
        cout<< a[i]<<"  ";
    }
    cout<<endl;
};
int main(){
    int a[10] ={9,34,24,56,31,24,66,3,45,98};
    Sort::insertionSort(a,a+10,[](int x,int y){return abs(x-24)<abs(y-24);});
    Sort::insertionSort(a,a+10);

    print(a,10);
}