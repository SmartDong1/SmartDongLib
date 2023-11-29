//
// Created by hu on 2020/8/2.
//

#ifndef SMARTDONGLIB_CONST_H
#define SMARTDONGLIB_CONST_H

#include <climits>
#include <cfloat>
#include <stdexcept>

namespace SmartDongLib{
    typedef int STATUS ;
    typedef int Size ;
    typedef int Integer;
    typedef double Real ;
    class SD_CONST{
    public:
        static const STATUS SD_FAIL = INT_MIN;
        static const STATUS SD_SUCCESS = INT_MAX;
        constexpr static const Real SD_MAXDOUBLE = DBL_MAX;
        constexpr static const Real SD_MINDOUBLE = DBL_MIN;

    };

    template<class  T>
    bool close(T a, T b){
        if ( a == b)
            return true;
        else if(a > b){
            return a-b <=DBL_EPSILON ;
        } else {
            return b-a <=DBL_EPSILON;
        }
    }
}
#endif //SMARTDONGLIB_CONST_H
