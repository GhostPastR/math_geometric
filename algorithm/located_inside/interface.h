#ifndef AGL_ALGORITHM_LOCATED_INSIDE_INTERFACE_H
#define AGL_ALGORITHM_LOCATED_INSIDE_INTERFACE_H

#include "implementation.h"

namespace agl::algorithm {

//
template<typename Object1, typename Object2>
inline constexpr auto located_inside(const Object1 &a, const Object2 &b){
    return geometry::located_inside<Object1, Object2>(a, b);
}

}

#endif // AGL_ALGORITHM_LOCATED_INSIDE_INTERFACE_H
