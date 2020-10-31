//
// Created by Administrator on 2020/10/28.
//
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include "sdalgorithm/util/independentalgorithm.h"
using namespace std;
using namespace SmartDongLib::SDmath;
void print(int a[],int size){
    for (int i = 0; i < size; ++i) {
        cout<< a[i]<<"  ";
    }
    cout<<endl;
};
int main(){
    int a[10] ={9,34,24,56,31,24,66,3,45,98};
//    std::sort(a,a+9,[](int x,int y){return y<x;});
    print(a,10);
    cout<< std::count(a,a+10,24)<<endl;
    //init - sum(arr2[i] / arr1[i])
    cout<< std::inner_product(a,a+1,a+1,0,minus<int>(),divides<int>())<<endl;
    cout<<std::atoi("13")+2<<endl;
    char s[5] ;
    itoa(10,s,10);
    cout<<s<<endl;
    cout<<std::is_sorted(a,a+9,[](int x,int y){return y<x;})<<endl;
    std::fill(a+9,a+10,24);
    int b[10] ={9,34,24,56,71,24,66,2,45,98};
    pair<int *, int *> pai=mismatch(a, a + 10, b,[](int x,int y){return y>=x;});
    cout<<"============"<<endl;
    for (int i = 0; i < 10; ++i) {
        cout<<*(pai.first+i)<<" notMatch "<<*(pai.second+i)<<endl;
    }

    cout<<"============"<<endl;
    cout<< std::count(a,a+10,24)<<endl;
    cout<<"============"<<endl;
    int aaaa[3]={78,22,31};
    vector<vector<int>>aaRet=print_subset(aaaa,aaaa+3,0);
    for (int j = 0; j < aaRet.size(); ++j) {
        cout<<"{";
        for (int i = 0; i < aaRet[j].size(); ++i) {
            cout<< aaRet[j][i] <<" ";
        }
        cout<<"}\n";
    }
}
