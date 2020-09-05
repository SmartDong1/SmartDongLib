//
// Created by hu on 2020/8/2.
//

#ifndef SMARTDONGLIB_CONST_H
#define SMARTDONGLIB_CONST_H

#include <limits.h>

namespace SmartDongLib{
    typedef int STATUS ;
    typedef int Size ;
    typedef int Integer;
    typedef double Real ;
    class SD_CONST{
    public:
        static const STATUS SD_FAIL = INT_MIN;
        static const STATUS SD_SUCCESS = INT_MAX;
    };
}
#endif //SMARTDONGLIB_CONST_H
