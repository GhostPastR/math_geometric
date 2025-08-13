#ifndef AGL_ALGORITHM_DISTANCE_INTERFACE_H
#define AGL_ALGORITHM_DISTANCE_INTERFACE_H

#include "distance.h"

namespace agl::algorithm {

template<typename Object1, typename Object2>
inline constexpr auto distance(const Object1 &a, const Object2 &b){
    return geometry::distance<Object1, Object2>(a, b);
}

}


#endif // AGL_ALGORITHM_DISTANCE_INTERFACE_H
