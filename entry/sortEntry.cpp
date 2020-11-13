//
// Created by Administrator on 2020/11/2.
//

#include<iostream>
#include "sdalgorithm/util/sort.h"
#include <ctime>
#include <malloc.h>
#include<cstring>
#include <cstdlib>
#include <typeinfo>
#include<algorithm>

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

    const int veclen =100000 ;
    int a[veclen] ;
//    a.resize(veclen);
//    int a[10] ={9,34,24,56,31,24,66,3,45,20};
//    Sort::sort(a.begin(),a+veclen,[](int x,int y){return abs(x-30)<=abs(y-30);},SmartDongLib::Sort::QuickSort);
//    print(a,10);
    unsigned  seed = time(0);
    srand(seed);
    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }
    clock_t startSelectionSort,endSelectionSort;
    startSelectionSort = clock();
    Sort::sort<int>(a,a+veclen,SmartDongLib::Sort::SelectionSort);
    endSelectionSort = clock();
    cout<<"1.SelectionSort:"<< (double)(endSelectionSort - startSelectionSort)
    <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;


    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }

    clock_t startBubbleSort,endBubbleSort;
    startBubbleSort = clock();
    Sort::sort<int>(a,a+veclen,SmartDongLib::Sort::BubbleSort);
    endBubbleSort = clock();
    cout<<"2.BubbleSort:"<< (double)(endBubbleSort - startBubbleSort)
            <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;;
    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }

    clock_t startInsertionSort,endInsertionSort;
    startInsertionSort = clock();
    Sort::sort<int>(a,a+veclen,SmartDongLib::Sort::InsertionSort);
    endInsertionSort = clock();
    cout<<"3.InsertionSort:"<< (double)(endInsertionSort - startInsertionSort)
            <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;

    ;
    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }
    clock_t startShellSort,endShellSort;
    startShellSort = clock();
    Sort::sort<int>(a,a+veclen,SmartDongLib::Sort::ShellSort);
    endShellSort = clock();
    cout<<"4.ShellSort:"<< (double)(endShellSort - startShellSort)
            <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;;

    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }
    clock_t startQuickSort,endQuickSort;
    startQuickSort = clock();
//    print(a, veclen);
    Sort::sort<int>(a,a+veclen,SmartDongLib::Sort::QuickSort);
//    print(a, veclen);
    endQuickSort = clock();
    cout<<"5.QuickSort:"<< (double)(endQuickSort - startQuickSort)
            <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;;

    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }
    clock_t startMergingSort,endMergingSort;
    startMergingSort = clock();
    Sort::sort<int>(a, a+veclen,Sort::MergingSort) ;
    endMergingSort = clock();
    cout<<"6.MergingSort:"<< (double)(endMergingSort - startMergingSort)
            <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;

    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }
//    int b[8] = {49,38,65,97,76,13,27,49};
    clock_t startHeapSort,endHeapSort;
    startHeapSort = clock();
    Sort::sort<int>(a, a+veclen,Sort::HeapSort) ;
    endHeapSort = clock();
    cout<<"7.HeapSort:"<< (double)(endHeapSort - startHeapSort)
        <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;
//    print(a,veclen);


    for (int i = 0; i < veclen; ++i) {
        a[i]=rand();
    }
    clock_t startSTLSort,endSTLSort;
    startSTLSort = clock();
    std::sort(a, a+veclen) ;
    endSTLSort = clock();
    cout<<"8.STLSort:"<< (double)(endSTLSort - startSTLSort)
        <<"\t isSort:"<<std::is_sorted(a,a+veclen)<<endl;

}







