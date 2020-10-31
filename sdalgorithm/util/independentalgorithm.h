//
// Created by Administrator on 2020/10/31.
//

#ifndef SMARTDONGLIB_INDEPENDENTALGORITHM_H
#define SMARTDONGLIB_INDEPENDENTALGORITHM_H
#include "const.h"
#include <math.h>
#include <bits/concept_check.h>
#include <vector>
#include <iostream>
using std::vector;
namespace SmartDongLib{
    namespace SDmath{
        class DataTypeIllegalException: public std::runtime_error{
        public:
            DataTypeIllegalException():std::runtime_error("DataTypeIllegalException Exception"){}
            DataTypeIllegalException(const std::string& __arg):std::runtime_error("DataTypeIllegalException Exception:"+__arg){}

        };
        /**
         * <p> 最大公因数
         * @tparam Type 整数类型
         * @param x
         * @param y
         * @return
         */
        template<typename Type>
        Type greatestCommonDivisor(Type xx, Type yy){
            if (!   (typeid(Type) == typeid(short) ||
                    typeid(Type) == typeid(int) ||
                    typeid(Type) == typeid(long) ||
                    typeid(Type) == typeid(long long) )
               ) {
                throw DataTypeIllegalException("The Type can't be decimal");
            }
            long long x =xx;
            long long y= yy;

            if (y == 0)
                return x;
            else
                return  greatestCommonDivisor(y,x % y);

        }
        /**
         * <p>最小公倍数
         * @tparam Type 整数类型
         * @param x
         * @param y
         * @return
         */
        template<typename Type>
        Type leastCommonMultiple( Type x , Type y ){
            return x*y/greatestCommonDivisor(x,y);

        }
        /**
         * <p> 获取所有子集
         * @tparam ElemType  返回值类型
         * @tparam _InputIterator 线性表的迭代器类型
         * @param _first1      线性表的起始地址
         * @param _last1    线性表的结束地址
         * @param _null     用变量来指定返回值类型避免编译不过
         * @return  所有子集
         */
        template<class ElemType,typename _InputIterator>
        vector<vector<ElemType>> print_subset(_InputIterator _first1, _InputIterator _last1,ElemType _null ){
            int n = _last1 - _first1;
            vector<vector<ElemType>> ret;
            // 2的n次方   1<<n
            for(int s=0;s<(1<<n);s++) {
                vector<ElemType> subRet;
                for (int i = 0; i < n; i++) {
                    if (s & (1 << i)) //1左移i位，监测s的哪一位为1，为1的话输出
                    {
                        subRet.push_back(*(_first1 + i));
//                        std::cout<<i;
                    }
                }
                ret.push_back(subRet);
//                std::cout << std::endl;
            }
            return  ret;
        }



    }
}
#endif //SMARTDONGLIB_INDEPENDENTALGORITHM_H
