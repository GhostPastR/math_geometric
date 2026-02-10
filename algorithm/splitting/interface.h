#ifndef AGL_ALGORITHM_SPLITTING_INTERFACE_H
#define AGL_ALGORITHM_SPLITTING_INTERFACE_H

#include "implementation.h"
#include <iostream>

namespace agl::algorithm {

//
template<typename Object>
inline constexpr auto splitting(const Object &object, size_t count_point, algorithm::direct direct = algorithm::direct::RIGHT){
    return dispatch::splitting<Object>::get(object, count_point, direct);
}

template<typename Object, typename Type>
inline constexpr auto splitting(const Object &object, Type interval, Type &prior_remains, algorithm::direct direct = algorithm::direct::RIGHT){
    return dispatch::remains::splitting<Object, Type>::get(object, interval, prior_remains, direct);
}

}

#endif // AGL_ALGORITHM_SPLITTING_INTERFACE_H
