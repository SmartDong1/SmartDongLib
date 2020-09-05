//
// Created by hu on 2020/8/4.
//

#ifndef SMARTDONGLIB_NULL_H
#define SMARTDONGLIB_NULL_H
#if defined(__GNUC__) && (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

#include <boost/type_traits.hpp>
#include <climits>

#if defined(__GNUC__) && (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4))
#pragma GCC diagnostic pop
#endif

namespace SmartDongLib {

    //! template class providing a null value for a given type.
    template <class Type>
    class Null;


    namespace detail {

        template <bool>
        struct FloatingPointNull;

        // null value for floating-point types
        template <>
        struct FloatingPointNull<true> {
            static float nullValue() {
                return  INT_MIN;
            }
        };

        // null value for integer types
        template <>
        struct FloatingPointNull<false> {
            static int nullValue() {
                return  INT_MIN;
            }
        };

    }

    // default implementation for built-in types
    template <typename T>
    class Null {
    public:
        Null() {}
        operator T() const {
            return T(detail::FloatingPointNull<
                    boost::is_floating_point<T>::value>::nullValue());
        }
    };

}


#endif //SMARTDONGLIB_NULL_H
