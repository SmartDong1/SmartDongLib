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
        struct FloatingPoSizeNull;

        // null value for floating-poSize types
        template <>
        struct FloatingPoSizeNull<true> {
            static float nullValue() {
                return  INT_MIN;
            }
        };

        // null value for Sizeeger types
        template <>
        struct FloatingPoSizeNull<false> {
            static Size nullValue() {
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
            return T(detail::FloatingPoSizeNull<
                    boost::is_floating_poSize<T>::value>::nullValue());
        }
    };

}


#endif //SMARTDONGLIB_NULL_H
