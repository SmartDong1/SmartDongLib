//
// Created by Administrator on 2020/11/2.
//

#ifndef SMARTDONGLIB_SORT_H
#define SMARTDONGLIB_SORT_H
#include "const.h"
#include <vector>
#include<iostream>

//#include <math.h>
 namespace SmartDongLib{
    class Sort{
    public:
        enum sortMethod {

            SelectionSort =1,
            BubbleSort ,
            InsertionSort,
            ShellSort,
            QuickSort,
        };
        /**
         * <p>选择排序.每次选择最值放到最前面
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void selectionSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                _Compare _comp ){
            for (_RandomAccessIterator iter = _first ; iter < _last ;iter++){
                _RandomAccessIterator maxValue = iter;
                for (_RandomAccessIterator index= iter; index <  _last; ++index) {
                    if ( _comp (*index,*maxValue)  ){
                        maxValue=index;
                    }
                }
                iteratorSwap(maxValue,iter);
            }
        }
        template<class _RandomAccessIterator>
        static void selectionSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            for (_RandomAccessIterator iter = _first ; iter < _last ;iter++){
                _RandomAccessIterator maxValue = iter;
                for (_RandomAccessIterator index= iter; index <  _last; ++index) {
                    if (*index<*maxValue ){
                        maxValue=index;
                    }
                }
                iteratorSwap(maxValue,iter);
            }
        }
        /**
         * <p> 冒泡排序。每次双循环把最值交换到最前面
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void bubbleSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                                  _Compare _comp ){
            for (_RandomAccessIterator iter = _last ; iter > _first+1 ;iter--){
                for (_RandomAccessIterator index= _first; index <  iter -1; ++index) {
                    if ( _comp (*(index +1),*index)  ){
                        iteratorSwap(index,index +1);
                    }
                }

            }
        }
        template<class _RandomAccessIterator>
        static void bubbleSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            for (_RandomAccessIterator iter = _last ; iter > _first+1 ;iter--){
                for (_RandomAccessIterator index= _first; index <  iter -1; ++index) {
                    if ( *(index +1)<*index  ){
                        iteratorSwap(index,index +1);
                    }
                }

            }
        }
        /**
         * <p> 直接插入排序。每次双循环i次表示前 i-1 个数都已经排好序。
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void insertionSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                               _Compare _comp ){
            singleShellInsert(_first,_last,_comp,1);
        }
        template<class _RandomAccessIterator>
        static void insertionSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            singleShellInsert(_first,_last,1);
        }
        /**
         * <p> 希尔排序，有步长的插入排序
         * @tparam _RandomAccessIterator
         * @tparam _Compare
         * @param _first
         * @param _last
         * @param _comp
         */
        template<class _RandomAccessIterator, class _Compare>
        static void shellSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                              _Compare _comp){
            Size len =_last-_first;
            std::vector<Size> dlta;
//            int loopnum =(int)(log10(2*len+1) / log10(3) );
            for (int i = (len>>1); i >1; i=(i>>1) ){
                dlta.push_back(i);
            }
            dlta.push_back(1);
            for (int j = 0; j < dlta.size(); ++j) {
                singleShellInsert(_first,_last,_comp,dlta[j]);
            }
        }
        template<class _RandomAccessIterator>
        static void shellSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            Size len =_last-_first;
            std::vector<Size> dlta;
//            int loopnum =(int)(log10(2*len+1) / log10(3) );
            for (int i = (len>>1); i >1; i=(i>>1) ){
                dlta.push_back(i);
            }
            dlta.push_back(1);
            for (int j = 0; j < dlta.size(); ++j) {
                singleShellInsert(_first,_last,dlta[j]);
            }
        }

        /**
         * <p> 快速排序，每一次partitio确定一个元素对应的位置，左右两边序列递归
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void quickSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                              _Compare _comp){
            if (_first<_last){
               _RandomAccessIterator pivotloc = singlePartition(_first,_last,_comp);
               quickSort(_first,pivotloc-1,_comp);
               quickSort(pivotloc+1,_last,_comp);

           }
        }
        template<class _RandomAccessIterator>
        static void quickSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            if (_first<_last){
                _RandomAccessIterator pivotloc = singlePartition(_first,_last);
                quickSort(_first,pivotloc-1 );
                quickSort(pivotloc+1,_last );

            }
        }
        protected:

        template<class _RandomAccessIterator, class _Compare>
        static void singleShellInsert(_RandomAccessIterator _first, _RandomAccessIterator _last,
                                      _Compare _comp,Size dk){
            for (_RandomAccessIterator iter = _first+ dk ; iter < _last ;iter++){
                auto temp =  *iter;
                _RandomAccessIterator index = iter -dk;
                //假如前面 iter -1 个都已经排好序 ，现在插第 iter 个
                // 先把iter的值保存起来 到temp
                // 然后从  iter -1 开始 和 temp 开始比较,如果小则 index的值往后移
                // 当比较结果为大时结束循环,把 temp 放入到 当前比较位置的后一个
                for ( ;index >= _first && _comp(temp , *index); index-=dk) {
                    *(index +dk) = *(index);
                }
                *(index +dk) = (temp);
            }
        }
        template<class _RandomAccessIterator >
        static void singleShellInsert(_RandomAccessIterator _first, _RandomAccessIterator _last,
                                       Size dk){
            for (_RandomAccessIterator iter = _first+ dk ; iter < _last ;iter++){
                auto temp =  *iter;
                _RandomAccessIterator index = iter -dk;
                //假如前面 iter -1 个都已经排好序 ，现在插第 iter 个
                // 先把iter的值保存起来 到temp
                // 然后从  iter -1 开始 和 temp 开始比较,如果小则 index的值往后移
                // 当比较结果为大时结束循环,把 temp 放入到 当前比较位置的后一个
                for ( ;index >= _first && temp < *index; index-=dk) {
                    *(index +dk) = *(index);
                }
                *(index +dk) = (temp);
            }
        }

    public:
        template<class _RandomAccessIterator>
        static void iteratorSwap(_RandomAccessIterator _elem1, _RandomAccessIterator _elem2){
            auto temp = *_elem1;
            *_elem1 = *_elem2;
            *_elem2 = temp;
        }

        template<class _RandomAccessIterator, class _Compare>
        static _RandomAccessIterator singlePartition(_RandomAccessIterator _first, _RandomAccessIterator _last,
                               _Compare _comp ){


            auto temp = *_first;
            while(_first -_last <0){
                while (_first<_last && _comp(temp,*_last)){
                    --_last;
                }
                *_first=*_last;
                while (_first<_last && _comp(*_first,temp)){
                    ++_first;
                }
                *_last=*_first;
            }
            *_first=temp;
            return  _first;
        }
        template<class _RandomAccessIterator >
        static _RandomAccessIterator singlePartition(_RandomAccessIterator _first, _RandomAccessIterator _last){
            auto temp = *_first;
            while(_first -_last <0){
                while (_first<_last && temp<=*_last){
                    --_last;
                }
                *_first=*_last;
                while (_first<_last && *_first<=temp){
                    ++_first;
                }
                *_last=*_first;
            }
            *_first=temp;
            return  _first;
        }
    };
}
#endif //SMARTDONGLIB_SORT_H
