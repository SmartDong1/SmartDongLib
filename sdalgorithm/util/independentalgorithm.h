//
// Created by Administrator on 2020/10/31.
//

#ifndef SMARTDONGLIB_INDEPENDENTALGORITHM_H
#define SMARTDONGLIB_INDEPENDENTALGORITHM_H
#include "const.h"

#include <bits/concept_check.h>
#include <vector>
#include <iostream>
using std::vector;
namespace SmartDongLib{
    namespace SDmath{
        /**
         * <p> 最大公因数
         * @tparam Type 整数类型
         * @param x
         * @param y
         * @return
         */
        template<typename Type>
        Type greatestCommonDivisor(Type x, Type y){
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
        template<class ElemType,typename _InputIterator>
        vector<vector<ElemType>> print_subset(_InputIterator __first1, _InputIterator __last1,ElemType){
            __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
            int n = __last1 - __first1;
            vector<vector<ElemType>> ret;
            // 2的n次方   1<<n
            for(int s=0;s<(1<<n);s++) {
                vector<ElemType> subRet;
                for (int i = 0; i < n; i++) {
                    if (s & (1 << i)) //1左移i位，监测s的哪一位为1，为1的话输出
                    {
                        subRet.push_back(*(__first1 + i));
                        std::cout<<i;
                    }
                }
                ret.push_back(subRet);
                std::cout << std::endl;
            }
            return  ret;
        }






        template<typename _InputIterator1, typename _InputIterator2, typename _Tp>
        inline _Tp
        inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                      _InputIterator2 __first2, _Tp __init)
        {
            // concept requirements
            __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
            __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
            __glibcxx_requires_valid_range(__first1, __last1);

            for (; __first1 != __last1; ++__first1, ++__first2)
                __init = __init + (*__first1 * *__first2);
            return __init;
        }
    }
}
#endif //SMARTDONGLIB_INDEPENDENTALGORITHM_H
