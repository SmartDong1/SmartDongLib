//
// Created by hu on 2020/8/12.
//

#include <cstdarg>
#include "Array.h"
#include <iostream>
namespace SmartDongLib {
    template<class ElemType>
    inline Array<ElemType>::Array(const Array<ElemType> &a) {
        elemtotal_=a.elemtotal_;
        dim_=a.dim_;
        base_ =(ElemType * )malloc(elemtotal_ * sizeof(ElemType));
        if (!base_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        bounds_=(int *)malloc(dim_ * sizeof(int));;
        if (!bounds_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        constants_= (int * ) malloc(dim_ * sizeof(int));
        if (!constants_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        for (int ecount = 0; ecount < elemtotal_; ++ecount) {
            *(base_+ecount) = *(a.base_ + ecount) ;
        }
        for (int d = 0; d < dim_; ++d) {
            *(bounds_+d) = *(a.bounds_ + d) ;
            *(constants_+d) = *(a.constants_ + d) ;
        }
    }

    template<class ElemType>
    STATUS Array<ElemType>::initArray(int dim, ...) {
        if (dim < 1 || dim >Max_ARRAY_DIM)
            return SD_CONST::SD_FAIL;
        dim_=dim;
        bounds_=(int *)malloc(dim * sizeof(int));
        if (!bounds_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        int elemtotal =1 ; //元素总数
        va_list ap;
        va_start(ap,dim);
        for (int i = 0; i < dim ; ++i) {
            bounds_[i] =va_arg(ap,int);
            if (bounds_[i] < 0 )
                return SD_CONST::SD_FAIL;//UNDERFLOW
            elemtotal *=bounds_[i];
        }
        elemtotal_=elemtotal;
        va_end(ap);
        base_ = (ElemType * )malloc(elemtotal * sizeof(ElemType));
        if (!base_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        constants_ = (int * ) malloc(dim * sizeof(int));
        if (!constants_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        constants_[dim_ -1] =1;
        //3维 constants_[2]= 1
        //constants[1] =3 ;
        //constants[0] =12
        for (int j =dim-2; j >=0 ; --j) {
            constants_[j]=bounds_[j+1] *constants_[j+1];
        }
        return SD_CONST::SD_SUCCESS;
    }

    template<class ElemType>
    STATUS Array<ElemType>::destroyArray() {
        std::cout<<"array:"<<this<<std::endl;
        if (base_){
            std::cout<<"base_:"<<base_<<std::endl;
            free(base_);
            base_=NULL;
        }
        if (bounds_){
            std::cout<<"bounds_:"<<bounds_<<std::endl;
            free(bounds_);
            bounds_=NULL;
        }
        if (constants_){
            std::cout<<"constants_:"<<constants_<<std::endl;
            free(constants_);
            constants_=NULL;
        }
        return SD_CONST::SD_SUCCESS;
    }
    /**
     * <p>确定 各个下标合法并求出相对地址
     * @tparam ElemType
     * @param ap
     * @return
     */
    template<class ElemType>
    STATUS Array<ElemType>::locate(va_list ap,int & off) {
        off=0;
        for (int i = 0; i < dim_; ++i) {
            //第 i 个数组下标
            int index = va_arg(ap,int);
            if (index < 0 || index > bounds_[i]){
                //越界异常
                throw ArrayIndexOutOfBoundsException();
            }
            off +=constants_[i] * index;
        }
        return 0;
    }
    /**
     * <p> 数组取值
     * @tparam ElemType  返回值类型
     * @param e  返回值
     * @param ...  数组下标
     * @return
     */
    template<class ElemType>
     STATUS Array<ElemType>::value(ElemType & e,...) {
        va_list ap;
        va_start(ap,e);
        int off=0;
        STATUS status=locate(ap,off);
        va_end(ap);
        if (status == SD_CONST::SD_FAIL){
            return status;
        }
        e = *(base_ + off);
        return SD_CONST::SD_SUCCESS;
    }
    /**
     * <p> 数组赋值
     * @tparam ElemType 数据类型
     * @param e   要赋的值
     * @param ... 数组下标
     * @return
     */
    template<class ElemType>
    STATUS Array<ElemType>::assign(ElemType e,...) {
        va_list ap;
        va_start(ap,e);
        int off=0;
        STATUS status=locate(ap,off);
        va_end(ap);
        if (status == SD_CONST::SD_FAIL){
            return status;
        }
        *(base_ + off) =e ;
        return SD_CONST::SD_SUCCESS;
    }

    template<class ElemType>
    ElemType &Array<ElemType>::operator[](int i) {
        int off =i;
        if ( i < elemtotal_)
            return *(base_ + off) ;
        else
            throw ArrayIndexOutOfBoundsException() ;
    }

    template<class ElemType>
    Array<ElemType>& Array<ElemType>::operator=(const Array<ElemType> &a) {
        elemtotal_=a.elemtotal_;
        dim_=a.dim_;
        base_ =(ElemType * )malloc(elemtotal_ * sizeof(ElemType));
        if (!base_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        bounds_=(int *)malloc(dim_ * sizeof(int));;
        if (!bounds_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        constants_= (int * ) malloc(dim_ * sizeof(int));
        if (!constants_){
            // 内存溢出
            throw ArrayStackOverflowException();
        }
        for (int ecount = 0; ecount < elemtotal_; ++ecount) {
            *(base_+ecount) = *(a.base_ + ecount) ;
        }
        for (int d = 0; d < dim_; ++d) {
            *(bounds_+d) = *(a.bounds_ + d) ;
            *(constants_+d) = *(a.constants_ + d) ;
        }
        return *this;
    }


}