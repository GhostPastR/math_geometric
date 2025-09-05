#ifndef AGL_ALGORITHM_EQYATION_OF_LINE_INTERFACE_H
#define AGL_ALGORITHM_EQYATION_OF_LINE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

template<typename Type, std::size_t N>
auto normalized(const std::array<Type, N> &array);

template<typename Figure>
inline constexpr auto equation_of_line(const Figure &figure){
    return geometry::equation_of_line<Figure>(figure);
}

template<typename Object>
inline constexpr auto equation_of_line(const Object &a, const Object &b){
    return geometry::equation_of_line<Object>(a, b);
}

}

#endif // AGL_ALGORITHM_EQYATION_OF_LINE_INTERFACE_H
