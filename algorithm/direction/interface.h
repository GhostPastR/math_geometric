#ifndef AGL_ALGORITHM_DIRECTION_INTERFACE_H
#define AGL_ALGORITHM_DIRECTION_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

template<typename Object1, typename Object2, typename ObjectDirection = traits::type_coordinate<Object1>::type>
inline constexpr auto direction(const Object1 &a, const Object2 &b){
    return geometry::direction<Object1, Object2, ObjectDirection>(a, b);
}

}


#endif // AGL_ALGORITHM_DIRECTION_INTERFACE_H
