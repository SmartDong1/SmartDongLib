//
// Created by hu on 2020/8/12.
//无序数组

#ifndef SMARTDONGLIB_ARRAY_H
#define SMARTDONGLIB_ARRAY_H
#include "const.h"
#include <boost/shared_ptr.hpp>
#include<cstring>
#include <stdarg.h>
namespace SmartDongLib {
#define Max_ARRAY_DIM 8
    class ArrayIndexOutOfBoundsException: public std::out_of_range{
    public:
        ArrayIndexOutOfBoundsException():std::out_of_range("array out of range Exception"){}
        ArrayIndexOutOfBoundsException(const std::string& __arg):std::out_of_range("array overflow_error Exception:"+__arg){}

    };
    class ArrayStackOverflowException: public std::overflow_error{
    public:
        ArrayStackOverflowException():std::overflow_error("array overflow_error Exception"){}
        ArrayStackOverflowException(const std::string& __arg):std::overflow_error("array overflow_error Exception:"+__arg){}

    };
    template<class ElemType>
    class Array {
    public:

        Array<ElemType>(){
            elemtotal_=0;
            dim_=0;
        }
        Array(Size dim, ...);
        Array& operator =( Array && a)noexcept;

        Array (Array && a) noexcept;


        Array<ElemType>( const Array<ElemType> & a);            //拷贝构造函数
        Array<ElemType>& operator =(const Array<ElemType> & a); //拷贝赋值运算符
        ~Array(){
            destroyArray();
        }
        STATUS initArray(Size dim, ...);
        STATUS destroyArray();
        STATUS locate(va_list ap,Size &off);
        STATUS value(ElemType & e,...);
        STATUS assign(ElemType e,...);
        STATUS copy(Size start,Size end, Size strIndex);
        Size elemtotal(){return  elemtotal_;}
        ElemType &  operator [](Size i);
//        void operator ()( Array<ElemType> & a);

        Size getElemtotal() const;

    private:
        ElemType * base_;  //元素的基址
        Size dim_;          //维度
        Size * bounds_;     //维度基址 每个维度 的长度
        Size * constants_;   //锁定dim个纬度可以包含多少个元素
        Size elemtotal_;    //数组总元素个数
    };

}

#endif //SMARTDONGLIB_ARRAY_H
