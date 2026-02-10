#ifndef AGL_ALGORITHM_DIRECTION_INTERFACE_H
#define AGL_ALGORITHM_DIRECTION_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

template<typename ObjectOut, typename Object1, typename Object2>
inline constexpr auto direction(const Object1 &a, const Object2 &b){
    return geometry::direction<Object1, Object2, ObjectOut>(a, b);
}

}


#endif // AGL_ALGORITHM_DIRECTION_INTERFACE_H
