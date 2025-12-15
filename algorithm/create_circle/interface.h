#ifndef AGL_ALGORITHM_CREATE_CIRCLE_INTERFACE_H
#define AGL_ALGORITHM_CREATE_CIRCLE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename CircleOut, typename Strategy, typename ...Args>
inline constexpr auto create_circle(Args ...args){
    return dispatch::create_circle<CircleOut,
                                   Strategy,
                                   Args...>::get(std::forward<Args>(args)...);

}

}

#endif // AGL_ALGORITHM_CREATE_CIRCLE_INTERFACE_H
